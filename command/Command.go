package command

import inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"

type Command struct {
	Name        string
	Description string
	Exec        func(inputQueue *inputqueue.InputQueue) error
}

func (command Command) Execute(inputQueue *inputqueue.InputQueue) error {
	return command.Exec(inputQueue)
}

var Commands = []Command{
	New, 
}