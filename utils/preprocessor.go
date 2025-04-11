package utils

import (
	"errors"
	"os"
	"regexp"
	"strings"

	"github.com/IvanLogvynenko/vecron/fs"
)

//Should be able to use passed variable to fill in gaps in the template to create unique projects
//It is really dumb as it only takes a variable from DataBase and sets it's value but I'm still dumber)

type EmptyVariable struct {
	Name      string
	FileNames string
	Lines     int
}

// preprocesses a directory with values loaded from a database. If a value is not found will be returned to caller in list
func PreprocessDir(path string) ([]EmptyVariable, error) {
	files := fs.ListFilesRecursive(path)
	failed := make([]EmptyVariable, 0)
	var errorList error = nil
	for _, filePath := range files {
		tmp, err := PreprocessFile(filePath)
		errorList = errors.Join(errorList, err)
		failed = append(failed, tmp...)
	}
	return failed, errorList
}

func PreprocessFile(path string) ([]EmptyVariable, error) {
	failed := make([]EmptyVariable, 0)
	file, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	data := string(file)
	re := regexp.MustCompile(`{{(.*?)}}`)
	db := GetDataBaseInstance()

	// for _, mappedRange := range indexes {
	// 	start, end := mappedRange[0], mappedRange[1]
	// 	varName := data[start+2 : end-2]
	// 	value := db.Get(varName)
	// 	// fmt.Println(varName, "->", value)
	// 	if value == "" {
	// 		failed = append(failed, EmptyVariable{varName, path, 0})
	// 	} else {
	// 		if value != "--skip" {
	// 			result = strings.Join([]string{data[:start], value, data[end:]}, "")
	// 		}
	// 	}
	// }
	processed := re.ReplaceAllStringFunc(data, func(match string) string {
		varName := strings.TrimSpace(match[2 : len(match)-2])
		value := db.Get(varName)
		if value == "" {
			failed = append(failed, EmptyVariable{varName, path, 0})
			return match // keep the placeholder in place
		}
		if value == "--skip" {
			return match // skip replacing
		}
		return value
	})
	return failed, os.WriteFile(path, []byte(processed), 0644)
}
