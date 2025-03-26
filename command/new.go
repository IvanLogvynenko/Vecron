package command

import inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"

var New = Command{
	"new",
	"",
	func(inputQueue *inputqueue.InputQueue) error {
		return nil
	},
}