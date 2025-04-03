package inputqueue

import (
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
			gofzf.Height(20),
			gofzf.Binds(),
			gofzf.Style(gofzf.Full),
		)
		return inputs[0], err
	}
	line := InputQueue.inputList[0]
	InputQueue.inputList = InputQueue.inputList[1:]
	matches, err := gofzf.FzfPrompt(data, gofzf.Pattern(line))
	if len(matches) != 0 {
		match := matches[0]
		return match, err
	}
	return "", fmt.Errorf("how did we end up here")
}

// type Matchable interface {
// }

// type matchableSource struct {
// 	options []Matchable
// }

// func (ms matchableSource) String(i int) string {
// 	return ms.options[i]
// }

// // Well... you can pass whatever you want here, but you also pass
// func (InputQueue *InputQueue) GetLineFZFCustomStruct(msg string, options []Matchable,
// 	mapper func(item Matchable) string,
// 	description func(item Matchable) string) int {
// 	if len(InputQueue.inputList) == 0 {
// 		id, err := fuzzyfinder.Find(options,
// 			func(i int) string { return mapper(options[i]) },
// 			fuzzyfinder.WithPromptString(msg),
// 			fuzzyfinder.WithPreviewWindow(func(i int, width int, height int) string {
// 				return description(options[i])
// 			}),
// 		)
// 		if err != nil {
// 			panic(err)
// 		}
// 		return id
// 	}
// 	line := InputQueue.inputList[0]
// 	InputQueue.inputList = InputQueue.inputList[1:]
// 	matches := fuzzy.FindFrom(line, )
// 	if len(matches) != 0 {
// 		match := matches[0]
// 		return match.Index
// 	}
// 	return -1
// }
