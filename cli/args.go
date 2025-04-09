package cli

import (
	"fmt"
	"slices"
	"strings"

	"github.com/IvanLogvynenko/vecron/utils"
)

func ParseArgs(args []string) (map[string]string, []string) {
	res := make(map[string]string)
	args, configPath := get(args, "-c")
	args, targetPath := get(args, "-o")
	args, license := getBool(args, "-l")
	res["configPath"] = configPath
	res["targetPath"] = targetPath
	if license {
		res["license"] = "select"
	}
	return res, args
}

func LoadArgs(args []string, db *utils.DataBase) []string {
	arg_map, args := ParseArgs(args)
	gen, args := genericSearch(args)
	for k, v := range arg_map {
		db.Set(k, v)
	}
	for k, v := range gen {
		db.Set(k, v)
	}
	return args
}

func get(args []string, opt string) ([]string, string) {
	result := ""
	if slices.Contains(args, opt) {
		id := slices.Index(args, opt)
		result = args[id+1]
		args = slices.Delete(args, id, id+2)
	}
	return args, result
}

func getBool(args []string, opt string) ([]string, bool) {
	if slices.Contains(args, opt) {
		id := slices.Index(args, opt)
		args = slices.Delete(args, id, id+1)
		return args, true
	}
	return args, false
}

func genericSearch(args []string) (map[string]string, []string) {
	res := make(map[string]string)
	new_args := make([]string, 0)
	for _, arg := range args {
		if strings.HasPrefix(arg, "--") {
			tmp := strings.SplitN(arg, "=", 2)
			argument, value := tmp[0], tmp[1]
			value = strings.Trim(value, " \"")
			argument = strings.Trim(argument, " -")
			// fmt.Println(argument, ":", value)
			res[argument] = value
			continue
		}
		if strings.HasPrefix(arg, "-") {
			panic(fmt.Errorf("Warning: Argument %v is not system argument, skipping...", arg))
		}
		new_args = append(new_args, arg)
	}
	return res, new_args
}
