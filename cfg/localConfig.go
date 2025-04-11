package cfg

import (
	"encoding/json"
	"errors"
	"os"

	"github.com/IvanLogvynenko/vecron/utils"
)

// LAZY LOADING OF CONFIG
// I
// WANT
// THIS
// TO
// FLY
// So don't waste time loading unnessesary data

// LocalConfig, to be used when Vecron is working with current project. Like formatting or assembling
type LocalConfig struct {
	ProjectPath   string `json:"ProjectPath"`
	ProjectName   string `json:"ProjectName"`
	DefaultEditor string `json:"DefaultEditor"`

	InitBuilder     []string  `json:"InitBuilder"` //For languages that require such initialization
	Build           BuildType `json:"Build"`
	BuildReleaseCmd []string  `json:"BuildReleaseCmd"`
	BuildDebugCmd   []string  `json:"BuildDebugCmd"`

	RunCmd string `json:"BuildRunCmd"`
}

func LoadLocalConfig() (*LocalConfig, error) {
	localConfig := &LocalConfig{}
	db := utils.GetDataBaseInstance()
	data, err := os.ReadFile(db.Get("targetPath") + ".vecron/config.json")
	return localConfig, errors.Join(json.Unmarshal(data, localConfig), err)
}
