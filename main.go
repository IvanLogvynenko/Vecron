package main

import (
	"fmt"

	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/fs"
)

// shoud be able to create new project
func main() {
	cli.Clear()
	cli.PrintLogo()
	input, error := cli.FzfSelect("Available commands:", []string{"new"})
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
		id, err := cli.FzfSelect("Available languages:", availableLanguages)
		if err != nil {
			fmt.Printf("Error: %v\n", err)
			return
		}
		fmt.Printf("Creating new project: %s\n", availableLanguages[id])
		fs.CpDir(fs.Home() + "/.config/vecron/templates/" + availableLanguages[id], ".")
	default:
		fmt.Printf("Creating new project: %d\n", input)
	}
}
