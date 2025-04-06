package command

import (
	"fmt"

	"github.com/IvanLogvynenko/vecron/cfg"
	"github.com/IvanLogvynenko/vecron/fs"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
)

var New = Command{
	"new",
	"Copy a template project from your template repository",
	func(inputQueue *inputqueue.InputQueue) error {
		fmt.Println("Building new project!")
		config, err := cfg.GetConfig()
		if err != nil {
			return err
		}

		selectedTemplate, err := inputQueue.GetLineFZF("Select language", config.GetAvailableTemplates())
		if err != nil {
			return err
		}
		fmt.Println("Creating new project: ", selectedTemplate)
		// As a folder for the project can't be created without project name this will be asked here
		projectName := inputQueue.GetLine("Project name")
		db := utils.GetDataBaseInstance()
		projectPath := fs.PWD() + projectName
		db.Set("ProjectName", projectName)
		fs.CpDir(config.GetTemplatePath()+selectedTemplate, projectPath)
		config.AddNewProject(projectPath)
		emptyVariables, err := utils.PreprocessDir(projectPath)
		if err != nil {
			return err
		}
		if len(emptyVariables) != 0 {
			fmt.Println("\nCouldn't find values for:")
			for _, v := range emptyVariables {
				fmt.Println(v)
			}
			fmt.Println("Please provide a value in .vecron/config.json")
			fmt.Println("If Vecron mistakenly parsed your code in {{}} please add them to .vecron/")
		}
		return nil
	},
}
