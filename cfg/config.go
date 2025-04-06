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
	userHome     string
	VecronHome   string `json:"VecronHome"`
	configPath   string
	templatePath string
	licencePath  string

	gitUserName string
	email       string

	DevPath      string `json:"DevPath"`
	projectsHome string
	libHome      string

	DefaultEditor string   `json:"DefaultEditor"`
	Projects      []string `json:"Projects"`

	DB                 *utils.DataBase
	availableTemplates []string
	changed            bool
}

var instance *Config = nil

const configFileName = "config.json"

// will search for config path in all suitable places
// returns empty string is nothing found
func findConfigPath(config Config) string {
	_, err := os.Stat(config.userHome + "/.config/vecron/")
	fmt.Println(config.userHome + "/.config/vecron/")
	if err == nil {
		return config.userHome + "/.config/vecron/"
	}
	_, err = os.Stat("./" + configFileName)
	if err == nil {
		return "./"
	}
	_, err = os.Stat(config.userHome + "/.local/share/vecron")
	if err == nil {
		return config.userHome + "/.local/share/vecron"
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
	instance.userHome = fs.Home()
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
	os.WriteFile(cfg.configPath, json, 0644)
}

func SaveIfChanged() {
	if instance != nil && instance.changed {
		instance.Save()
	}
}

func FromJson(jsonByte []byte) (*Config, error) {
	config := &Config{}
	return config, json.Unmarshal(jsonByte, config)
}

// LOADS AND LOADS of getters
func (cfg Config) GetVecronHome() string {
	if cfg.VecronHome == "" {
		// if this has been called you should be ashamed of how you keep your config
		cfg.VecronHome = findConfigPath(cfg)
	}
	return cfg.VecronHome
}

func (cfg Config) GetTemplatePath() string {
	if cfg.templatePath == "" {
		cfg.templatePath = cfg.GetVecronHome() + "/templates"
	}
	return cfg.templatePath
}

func (cfg Config) GetLicencesPath() string {
	if cfg.licencePath == "" {
		cfg.licencePath = cfg.GetVecronHome() + "/licences"
	}
	return cfg.licencePath
}

func (cfg Config) GetAvailableTemplates() []string {
	if cfg.availableTemplates == nil || len(cfg.availableTemplates) == 0 {
		cfg.availableTemplates = fs.ListDirectories(cfg.GetTemplatePath())
	}
	return cfg.availableTemplates
}

func (cfg Config) AddNewProject(path string) {
	cfg.Projects = append(cfg.Projects, path)
	cfg.changed = true
}
