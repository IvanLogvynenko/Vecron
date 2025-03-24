package fs

import "os"

func Home() string {
	home, err := os.UserHomeDir()
	if err != nil {
		return ""
	}
	return home
}
