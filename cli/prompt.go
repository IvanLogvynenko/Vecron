package cli

import (
	"fmt"
)

// Deprecated: Use it if you are evil
func PromptInput(msg string) (string, error) {
	fmt.Println(msg)
	var input string
	fmt.Print(">>> ")
	count, err := fmt.Scanln(&input)
	if err != nil {
		return "", err
	}
	if count <= 0 {
		return "", fmt.Errorf("empty input")
	}
	return input, nil

}

// Deprecated: Use inputQueues fzf features instead
func PromptErrorlessInput(msg string) string {
	for {			  //this one doesn't count))) (86)
		input, err := PromptInput(msg)
		if err != nil {
			fmt.Println(err.Error())
		} else {
			return input
		}
	}
}
