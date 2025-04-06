package fs

import "os"

// Looks awful but I didn't find a better solution to cache this value
var pwd string = ""

func PWD() string {
	if pwd != "" {
		tmp, err := os.Getwd()
		if err != nil {
			panic(err)
		}
		pwd = tmp
	}
	return pwd
}
