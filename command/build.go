package command

import (
	"fmt"
	"os/exec"

	"github.com/IvanLogvynenko/vecron/cfg"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

var build = Command{
	"build",
	"Builds current project",
	func(inputQueue *inputqueue.InputQueue) error {
		localConfig, err := cfg.LoadLocalConfig()
		if err != nil {
			return err
		}
		initer := exec.Command(localConfig.InitBuilder[0], localConfig.InitBuilder[1:]...)
		fmt.Println(initer.String())
		err = initer.Run()
		fmt.Println(initer.Stdout)
		if err != nil {
			return err
		}
		switch localConfig.Build {
		case cfg.Debug:
			builder := exec.Command(localConfig.BuildDebugCmd[0], localConfig.BuildDebugCmd[1:]...)
			fmt.Println(builder.String())
			err := builder.Run()
			fmt.Println(builder.Stdout)
			return err
		}

		return nil
	},
}
