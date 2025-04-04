package cfg

import "github.com/IvanLogvynenko/vecron/utils"

// LAZY LOADING OF CONFIG
// I 
// WANT
// THIS
// TO
// FLY
// So don't waste time loading unnessesary data

// LocalConfig, to be used when Vecron is working with current project. Like formatting or assembling
type LocalConfig struct {
	ProjectPath string
	DataBase    *utils.DataBase
}
