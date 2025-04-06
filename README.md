# Vecron

A project manager aimed to help you create projects and manage them with ease

# Requirements

- go
- fzf
- git
- gh (github-cli) !authorized!
- unix system `Linux :) or mac :(`

# Installation

Download `install.sh` and run it. It is advised installation as it will make full configuration for you. 

**OR you can go hardcore mode and install and configure everything yourself which might require undestanding ALL elegant dog shit I've coded here. I really wish you luck and if you DO I would ask you to**
- listen to this on repeat [this](https://www.youtube.com/watch?v=zZMg9ryeWOw&pp=ygUSZG9vbSByaXAgYW5kIHRlYXIg)
- reset next two variables
`hours spent until understood: 0h`
`hours spent and given up: 0h`


# Config Structure:

## Global config

Config stored in system. `tree $VecronHome`: (paths are given as they would be in linux)
``` bash
.
├── config.json
│   ├── VecronHome    ($HOME/.config/vecron)
│   ├── DevPath       (Path to dir where you store your projects default: $HOME/Dev)
│   ├── DefaultEditor (Your default editor, default: VSCode)
│   └── Projects	  (Path to ALL your projects that you have opened with vecron at least ones)
├── templates         (Default can be freely edited)
│   ├── cpp
│   ├── java
│   └── go
└── licences          (Default can be freely edited)
    ├── MIT
    └── GPL v3.0
```

## Local Config

Config created for every project
``` bash
.vecron
└── db.json
	├── DefaultEditor (Your default editor, default: VSCode)
	├── SubProjects	  (List of "sub"-projects e.g Microservice application)
	└── All {{vecron variables}} that are present in your project.
```
You should fill variables values in db.json and run `vecron format` for vecron to fill those placeholders and scan for new variables. If you want the warning about empty placeholder to disappear please set it to `--skip`, or run vecron format --skip={vars comma-separated}