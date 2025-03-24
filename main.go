package main

import (
	"fmt"
	"os"

	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/fs"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

// shoud be able to create new project
func main() {
	inputQueue := inputqueue.MakeInputQueue(os.Args[1:])
	cli.Clear()
	cli.PrintLogo()
	input, error := inputQueue.GetLineFZF("Available commands:", []string{"new", "build", "push", "run"})
	if error != nil {
		fmt.Printf("Error: %v\n", error)
		return
	}
	switch input {
	case -1:
		fmt.Println("No input provided")
	case 0:
		fmt.Println("Building new project!")
		availableLanguages, err := fs.ListDirectories(fs.Home() + "/.config/vecron/templates")
		if err != nil {
			fmt.Printf("Error: %v\n", err)
			return
		}
		id, err := inputQueue.GetLineFZF("Available languages:", availableLanguages)
		if err != nil {
			fmt.Printf("Error: %v\n", err)
			return
		}
		fmt.Printf("Creating new project: %s\n", availableLanguages[id])
		projectName := inputQueue.GetLine("Project name: ")
		fs.CpDir(fs.Home()+"/.config/vecron/templates/"+availableLanguages[id], "./"+projectName)
	default:
		fmt.Printf("Creating new project: %d\n", input)
	}
}
