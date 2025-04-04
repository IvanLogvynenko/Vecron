package fs

import "os"

func ListDirectories(path string) []string {
	entries, err := os.ReadDir(path)
	if err != nil {
		panic(err)
	}

	var dirs []string
	for _, entry := range entries {
		if entry.IsDir() {
			dirs = append(dirs, entry.Name())
		}
	}
	return dirs
}

func ListFiles(path string) []string {
	entries, err := os.ReadDir(path)
	if err != nil {
		panic(err)
	}

	var files []string
	for _, entry := range entries {
		if !entry.IsDir() {
			files = append(files, entry.Name())
		}
	}
	return files
}

func ListFilesRecursive(path string) []string {
	entries, err := os.ReadDir(path)
	if err != nil {
		panic(err)
	}

	var files []string
	for _, entry := range entries {
		if !entry.IsDir() {
			if path == "." || path == "./" {
				files = append(files, entry.Name())
			} else {
				files = append(files, path+"/"+entry.Name())
			}
		} else {
			files = append(files, ListFilesRecursive(path+"/"+entry.Name())...)
		}
	}
	return files
}
