package command

import (
	"fmt"

	"github.com/IvanLogvynenko/vecron/fs"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
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
		fmt.Println("Creating new project: ", selectedLanguage)
		// As a folder for the project can't be created without project name this will be asked here,
		projectName := inputQueue.GetLine("Project name")
		db := utils.GetDataBaseInstance()
		db.Set("ProjectName", projectName)
		fs.CpDir(fs.Home()+"/.config/vecron/templates/"+selectedLanguage, "./"+projectName)
		return nil
	},
}

var PreProc = Command{
	"preproc",
	"preproc",
	func(inputQueue *inputqueue.InputQueue) error {
		utils.PreprocessFile("./file.some")
		return nil
	},
}
