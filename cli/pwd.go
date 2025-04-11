package cli

import "os"

func PWD() string {
	tmp, err := os.Getwd()
	if err != nil {
		panic(err)
	}
	return tmp + "/"
}
