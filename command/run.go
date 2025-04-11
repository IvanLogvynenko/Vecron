package command

import (
	"os"
	"os/exec"

	"github.com/IvanLogvynenko/vecron/cfg"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

var run = Command{
	"run",
	"Runs current project",
	func(inputQueue *inputqueue.InputQueue) error {
		// cli.Clear()
		localConfig, err := cfg.LoadLocalConfig()
		if err != nil {
			return err
		}
		// fmt.Println("Running ", localConfig.ProjectPath)
		runner := exec.Command(localConfig.RunCmd)
		runner.Stdout = os.Stdout
		runner.Stderr = os.Stderr
		// fmt.Println(runner.String())
		err = runner.Run()
		if err != nil {
			return err
		}
		return nil
	},
}
