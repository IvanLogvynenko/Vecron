package command

import (
	"fmt"

	inputqueue "github.com/IvanLogvynenko/vecron/inputQueue"
	"github.com/IvanLogvynenko/vecron/utils"
)

var format = Command{
	"format",
	"Replaces all occurenses of {{var}} with their values\nView vecron config --help for more info",
	func(inputQueue *inputqueue.InputQueue) error {
		fmt.Println("EXPERIMENTAL IMPLEMENTATION")
		db := utils.GetDataBaseInstance()
		emptyVariables, err := utils.PreprocessDir(db.Get("targetPath"))
		if len(emptyVariables) != 0 {
			fmt.Println("\nCouldn't find values for:")
			for _, v := range emptyVariables {
				fmt.Println(v)
			}
			fmt.Println("Please provide a value in .vecron/db.json")
			fmt.Println("If Vecron mistakenly parsed your code in {{}} please add it to .vecron/db.json with value --skip")
		}
		return err
	},
}
