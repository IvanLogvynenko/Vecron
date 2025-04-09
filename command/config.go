package command

import (
	"fmt"

	"github.com/IvanLogvynenko/vecron/cfg"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

var config = Command{
	"config",
	"View configuration",
	func(inputQueue *inputqueue.InputQueue) error {
		config, err := cfg.GetConfig()
		if err != nil {
			return err
		}
		fmt.Println(string(config.ToJson()))
		return nil
	},
}
