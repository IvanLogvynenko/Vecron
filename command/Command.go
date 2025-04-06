package command

import (
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

type Command struct {
	Name        string
	Description string
	exec        func(inputQueue *inputqueue.InputQueue) error
}

func (c Command) ToString() string {
	return c.Name
}
func (c Command) Desc() string {
	return c.Description
}
func (c Command) Exec(inputQueue *inputqueue.InputQueue) error {
	return c.exec(inputQueue)
}

var Commands = []Command{
	New, Help, Config, Format,
}
