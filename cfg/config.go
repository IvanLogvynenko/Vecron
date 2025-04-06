package cfg

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"

	"github.com/IvanLogvynenko/vecron/fs"
	"github.com/IvanLogvynenko/vecron/utils"
)

// LAZY LOADING OF CONFIG
// I
// WANT
// THIS
// TO
// FLY
// So don't waste time loading unnessesary data
// Lazy Loading means that only requested parts of data should be loaded
// as much data as possible should be saved thus saving time on file reading information

// Global config, to be loaded when Vecron has to manage projects in the system
type Config struct {
	UserHome     string
	VecronHome   string `json:"VecronHome"`
	ConfigPath   string
	TemplatePath string
	LicencePath  string

	GitUserName string
	EMail       string

	DevPath      string `json:"DevPath"`
	ProjectsHome string
	LibHome      string

	DefaultEditor string   `json:"DefaultEditor"`
	Projects      []string `json:"Projects"`

	DB                 *utils.DataBase
	availableLanguages []string
}

var instance *Config = nil

const configFileName = "config.json"

// will search for config path in all suitable places
// returns empty string is nothing found
func findConfigPath(config Config) string {
	_, err := os.Stat(config.UserHome + "/.config/vecron/")
	fmt.Println(config.UserHome + "/.config/vecron/")
	if err == nil {
		return config.UserHome + "/.config/vecron/"
	}
	_, err = os.Stat("./" + configFileName)
	if err == nil {
		return "./"
	}
	_, err = os.Stat(config.UserHome + "/.local/share/vecron")
	if err == nil {
		return config.UserHome + "/.local/share/vecron"
	}
	return ""
}

// Loads config if found. If not -> run vecron config
func GetConfig() (*Config, error) {
	if instance != nil {
		return instance, nil
	}

	// create new instance
	instance = &Config{}
	instance.UserHome = fs.Home()
	// search for config in db if not found try to search in fs
	db := utils.GetDataBaseInstance()
	instance.DB = db
	configPath, err := db.Get("configPath")

	if err == nil {
		instance.DB.Delete("configPath")
	} else {
		configPath = findConfigPath(*instance)
	}
	fmt.Println("Config: \"", configPath, "\"")
	if configPath == "" {
		return nil, errors.New("Couldn't find config. Run \"vecron config --clear\"")
	}

	file, err := os.ReadFile(configPath + configFileName)
	if err != nil {
		panic(err)
	}
	return FromJson(file)
}

func (cfg Config) ToJson() []byte {
	jsonBytes, err := json.Marshal(cfg)
	if err != nil {
		panic(err)
	}
	return jsonBytes
}

func (cfg Config) Save() {
	json := cfg.ToJson()
	os.WriteFile(cfg.ConfigPath, json, 0644)
}

func FromJson(jsonByte []byte) (*Config, error) {
	config := &Config{}
	return config, json.Unmarshal(jsonByte, config)
}
