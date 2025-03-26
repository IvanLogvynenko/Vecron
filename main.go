package main

import (
	"fmt"
	"os"
	"slices"

	"github.com/IvanLogvynenko/vecron/cfg"
	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/fs"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

func main() {
	args := os.Args[1:]
	configPath := ""
	if slices.Contains(args, "-c") {
		id := slices.Index(args, "-c")
		configPath = args[id+1]
		args = append(args[:id], args[id+2:]...)
	}
	dataBase := cfg.GetDataBaseInstance()
	dataBase.Set("configPath", configPath)

	targetPath := ""
	if slices.Contains(args, "-o") {
		id := slices.Index(args, "-o")
		targetPath = args[id+1]
		args = append(args[:id], args[id+2:]...)
	}
	dataBase.Set("targetPath", targetPath)
	inputQueue := inputqueue.MakeInputQueue(args)

	cli.Clear()
	cli.PrintLogo()
	input := inputQueue.GetLineFZF("Select command: ", []string{"new", "build", "push", "run"})
	switch input {
	case -1:
		fmt.Println("No input provided")
	case 0:
		fmt.Println("Building new project!")
		availableLanguages := fs.ListDirectories(fs.Home() + "/.config/vecron/templates")
		id := inputQueue.GetLineFZF("Select language: ", availableLanguages)
		fmt.Printf("Creating new project: %s\n", availableLanguages[id])
		projectName := inputQueue.GetLine("Project name: ")
		fs.CpDir(fs.Home()+"/.config/vecron/templates/"+availableLanguages[id], "./"+projectName)
	default:
		fmt.Printf("Creating new project: %d\n", input)
	}
}
