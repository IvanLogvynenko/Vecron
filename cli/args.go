package cli

import (
	"slices"

	"github.com/IvanLogvynenko/vecron/utils"
)

func ParseArgs(args []string) (map[string]string, []string) {
	res := make(map[string]string)
	args, configPath := get(args, "-c")
	args, targetPath := get(args, "-o")
	res["configPath"] = configPath
	res["targetPath"] = targetPath
	return res, args
}

func LoadArgs(args []string, db *utils.DataBase) []string {
	arg_map, args := ParseArgs(args)
	for k, v := range arg_map {
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
