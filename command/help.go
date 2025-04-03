package command

import (
	"github.com/IvanLogvynenko/vecron/cli"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

var Help = Command{
	"help",
	"Print help message",
	func(inputQueue *inputqueue.InputQueue) error {
		cli.PrintHelp()
		return nil
	},
}
