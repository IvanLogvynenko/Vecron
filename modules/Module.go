package modules

import (
	"github.com/IvanLogvynenko/vecron/command"
)

type Module struct {
	Functions []string
	Commands  []command.Command

	Init func()
}
