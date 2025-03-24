package inputqueue

import (
	"fmt"
	"strings"

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
func (inputQueue *InputQueue) GetLine(msg string) string {
	if len(inputQueue.inputList) == 0 {
		// Prompt user with a message, then load them in queue
		// as user can pass a list of arguments and pop first one
		inputQueue.inputList = MakeInputQueueFromString(cli.PromptErrorlessInput(msg)).inputList
	}
	line := inputQueue.inputList[0]
	inputQueue.inputList = inputQueue.inputList[1:]
	return line
}

func (InputQueue *InputQueue) GetLineFZF(msg string, options []string) (int, error) {
	if len(InputQueue.inputList) == 0 {
		id, err := cli.FzfSelect(msg, options)
		if err != nil {
			return -1, err
		}
		return id, nil
	}
	line := InputQueue.inputList[0]
	InputQueue.inputList = InputQueue.inputList[1:]
	for id, option := range options {
		if line == option {
			return id, nil
		}
	}
	return -1, fmt.Errorf("option not found")

}
