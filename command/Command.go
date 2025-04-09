package command

import (
	"fmt"

	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
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
	new, help, config, format,
	// debug,
}

var debug = Command{
	"debug",
	"anything can happen)))",
	func(inputQueue *inputqueue.InputQueue) error {
		db := utils.GetDataBaseInstance()
		db.Print()
		val, _ := db.Get("some")
		fmt.Println(val)
		return nil
	},
}
