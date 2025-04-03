package main

import (
	"os"

	gofzf "github.com/IvanLogvynenko/go-fzf"
	"github.com/IvanLogvynenko/vecron/cfg"
	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/command"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

func main() {
	args := os.Args[1:]
	dataBase := cfg.GetDataBaseInstance()
	rest := cli.LoadArgs(args, dataBase)
	inputQueue := inputqueue.MakeInputQueue(rest)
	dataBase.Print()

	cli.Clear()
	cli.PrintLogo()
	commands := make([]gofzf.Struct, len(command.Commands))
	for i, val := range command.Commands {
		commands[i] = val
	}
	input, err := inputQueue.GetLineFZFStruct("Select command", commands)
	if err != nil {
		panic(err)
	}
	selectedCommand := command.Commands[input]
	err = selectedCommand.Exec(&inputQueue)
	if err != nil {
		panic(err)
	}
}
