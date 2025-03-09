package cli

import (
	"fmt"

	"github.com/ktr0731/go-fuzzyfinder"
)

// If match found fully in input returns 1, value between 1 and 0 otherwise, the more the better match
// func purity_match(input string, match string) float64 {
// 	input = strings.ToLower(input)
// 	match = strings.ToLower(match)

// 	result := 0.0

// 	occurrences := []int{}
// 	for i, char := range input {
// 		if char == rune(match[0]) {
// 			occurrences = append(occurrences, i)
// 		}
// 	}

// 	if len(occurrences) == 0 {
// 		return 0.0
// 	}

// 	for _, pos := range occurrences {
// 		counter := 0
// 		for i, char := range match {
// 			if pos+i < len(input) && input[pos+i] == byte(char) { // if it doesn't match we still try to compare to fit in typos
// 				counter++
// 			}
// 		}
// 		if counter == len(match) {
// 			return 1
// 		}
// 		var tmp float64
// 		if len(match) > len(input) {
// 			tmp = float64(counter) * float64(counter) / float64(len(match)) / float64(len(input))
// 		} else {
// 			tmp = float64(counter) * float64(counter) / float64(len(match)) / float64(len(match))
// 		}
// 		result = max(result, tmp)
// 	}
// 	return result
// }

// func PromptSelection(msg string, options []string) (int, error) {
// 	Clear()
// 	PrintLogo()
// 	fmt.Println(msg)
// 	for i, option := range options {
// 		fmt.Printf("%d. %s\n", i+1, option)
// 	}
// 	var choiceStr string
// 	fmt.Print(">>> ")
// 	_, err := fmt.Scanln(&choiceStr) 
// 	if err != nil {
// 		return 0, err
// 	}
// 	choice := 0
// 	choice, err = strconv.Atoi(choiceStr)
// 	if err != nil { // Means User entered an option and not a number
// 		max := 0.0
// 		maxId := -1
// 		for i, option := range options {
// 			tmp := purity_match(option, choiceStr)
// 			if tmp > max {
// 				max = tmp
// 				maxId = i
// 			}
// 		}
// 		if maxId != -1 {
// 			return maxId, nil
// 		} else {
// 			return 0, fmt.Errorf("couldn't match user input. Try enterering a number... Sry")
// 		}
// 	}
// 	if choice < 1 || choice > len(options) {
// 		return 0, fmt.Errorf("invalid choice. Please choose between 1 and %d", len(options))
// 	}

// 	return choice, nil
// }

func FzfSelect(msg string, options []string) (int, error) {
	fmt.Println(msg)

	// Run fuzzy finder
	idx, err := fuzzyfinder.Find(
		options,
		func(i int) string { return options[i] },
	)
	return idx, err
}