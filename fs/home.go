package fs

import "os"

func Home() string {
	home, err := os.UserHomeDir()
	if err != nil {
		panic(err)
	}
	return home
}
