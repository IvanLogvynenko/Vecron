package utils

import (
	"fmt"
	"os"
	"regexp"
	"strings"
)

//Should be able to use passed variable to fill in gaps in the template to create unique projects
//It is really dumb as it only takes a variable from DataBase and sets it's value but I'm still dumber)
// re := regexp.MustCompile(`\d+`)
// indexes := re.FindAllStringIndex("abc123def456", -1)
// fmt.Println(indexes) // [[3 6] [9 12]]

// preprocesses a directory with values loaded from a database. If a value is not found will be returned to caller in list
func PreprocessDir(path string) ([]string, error) {
	return nil, nil
}

func PreprocessFile(path string) ([]string, error) {
	failed := make([]string, 0)
	file, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	data := string(file)
	re := regexp.MustCompile(`{{(.*?)}}`)
	indexes := re.FindAllStringIndex(data, -1)

	db := GetDataBaseInstance()
	db.Set("ProjectName", "Vecron")

	for _, mappedRange := range indexes {
		start, end := mappedRange[0], mappedRange[1]
		fmt.Println(data[start+2 : end-2])
		varName := data[start+2 : end-2]
		value, err := db.Get(varName)
		fmt.Println(varName, "->", value)
		if err != nil {
			failed = append(failed, varName)
		} else {
			data = strings.Join([]string{data[:start], value, data[end:]}, "")
		}
	}
	return failed, os.WriteFile(path, []byte(data), 0644)
}
