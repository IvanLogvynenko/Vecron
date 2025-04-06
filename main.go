package main

import (
	"fmt"
	"os"

	gofzf "github.com/IvanLogvynenko/go-fzf"
	"github.com/IvanLogvynenko/vecron/cfg"
	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/command"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
)

func handleError(err error) {
	if err != nil {
		fmt.Println("Caught error:", err.Error(), "\nPrining Help Message")
		cli.PrintHelp()
		os.Exit(1)
	}
}

func main() {
	args := os.Args[1:]
	dataBase := utils.GetDataBaseInstance()
	rest_args := cli.LoadArgs(args, dataBase)
	inputQueue := inputqueue.MakeInputQueue(rest_args)

	cli.Clear()
	cli.PrintLogo()
	commands := make([]gofzf.Struct, len(command.Commands))
	for i, val := range command.Commands {
		commands[i] = val
	}
	input, err := inputQueue.GetLineFZFStruct("Select command", commands)
	handleError(err)
	selectedCommand := command.Commands[input]
	err = selectedCommand.Exec(&inputQueue)
	handleError(err)
	cfg.SaveIfChanged()
}
