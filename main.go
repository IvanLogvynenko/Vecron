package main

import (
	"fmt"
	"os"

	gofzf "github.com/IvanLogvynenko/go-fzf"
	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/command"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
)

func main() {
	args := os.Args[1:]
	args = append(args, "pre")
	dataBase := utils.GetDataBaseInstance()
	rest := cli.LoadArgs(args, dataBase)
	inputQueue := inputqueue.MakeInputQueue(rest)
	dataBase.Set("ProjectName", "Vecron")

	cli.Clear()
	cli.PrintLogo()
	commands := make([]gofzf.Struct, len(command.Commands))
	for i, val := range command.Commands {
		commands[i] = val
	}
	input, err := inputQueue.GetLineFZFStruct("Select command", commands)
	if err != nil {
		fmt.Println("Caught error: ", err.Error(), ". Prining Help Message")
		cli.PrintHelp()
		os.Exit(1)
	}
	selectedCommand := command.Commands[input]
	err = selectedCommand.Exec(&inputQueue)
	if err != nil {
		fmt.Println("Caught error: ", err.Error(), ". Prining Help Message")
		cli.PrintHelp()
		os.Exit(1)
	}
}
