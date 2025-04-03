package command

import (
	"fmt"

	"github.com/IvanLogvynenko/vecron/fs"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
)

var New = Command{
	"new",
	"Copy a template project from your template repository",
	func(inputQueue *inputqueue.InputQueue) error {
		fmt.Println("Building new project!")
		availableLanguages := fs.ListDirectories(fs.Home() + "/.config/vecron/templates")
		selectedLanguage, err := inputQueue.GetLineFZF("Select language", availableLanguages)
		if err != nil {
			return err
		}
		fmt.Printf("Creating new project: %v\n", selectedLanguage)
		projectName := inputQueue.GetLine("Project name")
		fs.CpDir(fs.Home()+"/.config/vecron/templates/"+selectedLanguage, "./"+projectName)
		return nil
	},
}
