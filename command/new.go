package command

import (
	"fmt"
	"strings"

	gofzf "github.com/IvanLogvynenko/go-fzf"
	"github.com/IvanLogvynenko/vecron/cfg"
	"github.com/IvanLogvynenko/vecron/cli"
	"github.com/IvanLogvynenko/vecron/fs"
	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
)

var new = Command{
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
		projectPath := cli.PWD() + projectName + "/"
		config.DB.Set("ProjectName", projectName)
		fmt.Println("Project path: ", projectPath)
		fs.CpDir(config.GetTemplatePath()+selectedTemplate, projectPath)
		config.AddNewProject(projectPath)
		license, err := config.DB.Get("license")
		if err == nil {
			if license == "fzf" || strings.Contains("select", license) {
				licenses := fs.ListFiles(config.GetLicensesPath())
				licenses, err = gofzf.FzfPrompt(licenses,
					gofzf.Cycle(),
					gofzf.Reverse(),
					gofzf.Height(30),
					gofzf.Binds(),
					gofzf.Style(gofzf.Full))
				if err != nil {
					panic(err)
				}
				if len(licenses) != 1 && len(licenses) != 0 {
					panic("How did you manage to select multiple in fzf???")
				}
				fs.CopyFile(config.GetLicensesPath()+licenses[0], projectPath+"LICENSE")
			}
		}
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
