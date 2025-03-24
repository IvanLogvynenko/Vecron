package fs

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func CopyFile(srcFile string, destFile string) error {
	src, err := os.Open(srcFile)
	if err != nil {
		return err
	}
	defer src.Close()

	dest, err := os.Create(destFile)
	if err != nil {
		return err
	}
	defer dest.Close()

	_, err = io.Copy(dest, src)
	if err != nil {
		return err
	}

	srcInfo, err := os.Stat(srcFile)
	if err != nil {
		return err
	}
	return os.Chmod(destFile, srcInfo.Mode())
}

// copies the contents of a directory into the destnation
func CpDir(src string, dst string) error {
	srcStat, err := os.Stat(src)
	if err != nil {
		return fmt.Errorf("source directory error: %w", err)
	}
	if !srcStat.IsDir() {
		return fmt.Errorf("source is not a directory")
	}

	err = os.MkdirAll(dst, srcStat.Mode())
	if err != nil {
		return fmt.Errorf("failed to create destination directory: %w", err)
	}

	return filepath.Walk(src, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}

		relPath, err := filepath.Rel(src, path)
		if err != nil {
			return err
		}
		destPath := filepath.Join(dst, relPath)

		if info.IsDir() {
			return os.MkdirAll(destPath, info.Mode())
		}

		return CopyFile(path, destPath)
	})
}
