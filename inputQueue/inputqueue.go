package inputqueue

import (
	"errors"
	"fmt"
	"strings"

	gofzf "github.com/IvanLogvynenko/go-fzf"
	"github.com/IvanLogvynenko/vecron/cli"
)

type InputQueue struct {
	inputList []string
}

func MakeInputQueueFromString(input string) InputQueue {
	var inputQueue InputQueue = InputQueue{strings.Split(input, " ")}
	return inputQueue
}
func MakeInputQueueFromStringWithDelimiter(input string, delimiter string) InputQueue {
	var inputQueue InputQueue = InputQueue{strings.Split(input, delimiter)}
	return inputQueue
}
func MakeInputQueue(data []string) InputQueue {
	var inputQueue InputQueue = InputQueue{data}
	return inputQueue
}
func MakeInputQueueWithLength(length int) InputQueue {
	var inputQueue InputQueue = InputQueue{make([]string, length)}
	return inputQueue
}
func MakeEmptyInputQueue() InputQueue {
	var inputQueue InputQueue = InputQueue{make([]string, 0)}
	return inputQueue
}

func (InputQueue *InputQueue) pop() string {
	line := InputQueue.inputList[0]
	InputQueue.inputList = InputQueue.inputList[1:]
	return line
}

// Pass msg without ': '
func (inputQueue *InputQueue) GetLine(msg string) string {
	if len(inputQueue.inputList) == 0 {
		// Prompt user with a message, then load them in queue
		// as user can pass a list of arguments and pop first one
		inputQueue.inputList = MakeInputQueueFromString(cli.PromptErrorlessInput(msg + ": ")).inputList
	}
	line := inputQueue.inputList[0]
	inputQueue.inputList = inputQueue.inputList[1:]
	return line
}
func (InputQueue *InputQueue) GetLineFZF(prompt string, data []string) (string, error) {
	if len(InputQueue.inputList) == 0 {
		inputs, err := gofzf.FzfPrompt(
			data,
			gofzf.Header(prompt),
			gofzf.Cycle(),
			gofzf.Reverse(),
			gofzf.Height(30),
			gofzf.Binds(),
			gofzf.Style(gofzf.Full),
		)
		return inputs[0], err
	}
	line := InputQueue.pop()
	matches, err := gofzf.FzfPrompt(data, gofzf.Pattern(line))
	if len(matches) == 0 {
		return "", fmt.Errorf("none were selected")
	}
	if len(matches) != 1 {
		errorStr := "Found multiple command: "
		for _, value := range matches {
			errorStr += value
		}
		errorStr += "\nOnly one command can be provided"
		return "", errors.Join(err, fmt.Errorf("%v", errorStr))
	}
	return matches[0], nil
}
func (InputQueue *InputQueue) GetLineFZFStruct(prompt string, data []gofzf.Struct) (int, error) {
	if len(InputQueue.inputList) == 0 {
		inputs, err := gofzf.FzfPromptStruct(
			data,
			gofzf.Header(prompt),
			gofzf.Cycle(),
			gofzf.Reverse(),
			gofzf.Height(30),
			gofzf.Binds(),
			gofzf.Style(gofzf.Full),
			gofzf.Info(nil),
			gofzf.InfoPosition(gofzf.Down),
		)
		return inputs[0], err
	}
	line := InputQueue.pop()
	matches, err := gofzf.FzfPromptStruct(data, gofzf.Pattern(line))
	if len(matches) == 0 {
		return -1, fmt.Errorf("none were selected")
	}
	if len(matches) != 1 {
		errorStr := "Found multiple command: "
		for _, id := range matches {
			errorStr += data[id].ToString()
		}
		errorStr += "\nOnly one command can be provided"
		return -1, errors.Join(err, fmt.Errorf("%v", errorStr))
	}
	return matches[0], nil
}

// Checks whether interactive UI like fzf or prompting will be loaded or not
func (InputQueue *InputQueue) HasNext() bool {
	return len(InputQueue.inputList) != 0
}