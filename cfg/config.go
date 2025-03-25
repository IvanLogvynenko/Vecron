package cfg

import (
	"os"

	"github.com/IvanLogvynenko/vecron/fs"
)

type Config struct {
	ConfigPath string `json:"ConfigPath"`
	dataBase   *DataBase
}

var instance *Config = nil

const configFileName = "cfg.json"

// will search for config path in all suitable places
// returns empty string is nothing found
func getConfigPath() string {
	if instance != nil {
		configPath, err := instance.dataBase.Get("configPath")
		if err == nil {
			return configPath
		}
	}
	_, err := os.Stat("./" + configFileName)
	if err == nil {
		return "./" + configFileName
	}
	_, err = os.Stat(fs.Home() + "/.config/vecron/" + configFileName)
	if err == nil {
		return fs.Home() + "/.config/vecron/" + configFileName
	}
	_, err = os.Stat(fs.Home() + "/.local/share/vecron" + configFileName)
	if err == nil {
		return fs.Home() + "/.local/share/vecron" + configFileName
	}
	return ""
}

func GetConfig() *Config {
	if instance == nil {
		instance = &Config{}
		instance.dataBase = GetDataBaseInstance()
		instance.ConfigPath = getConfigPath()
	}
	return instance
}

// Prefer this over getconfig as get* will create it from beginning
func LoadConfig() *Config {
	return nil
}
