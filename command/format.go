package command

import (
	"fmt"

	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

var format = Command{
	"format",
	"Replaces all occurenses of {{var}} with their values\nView vecron config --help for more info",
	func(inputQueue *inputqueue.InputQueue) error {
		fmt.Println("NOT IMPLEMENTED YET")
		return nil
	},
}
