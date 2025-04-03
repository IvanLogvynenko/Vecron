package cfg

import "github.com/IvanLogvynenko/vecron/utils"

// LocalConfig, to be used when Vecron is working with current project. Like formatting or assembling
type LocalConfig struct {
	ProjectPath string
	DataBase    *utils.DataBase
}
