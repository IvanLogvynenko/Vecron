package main

import "fmt"

func Init() {
	fmt.Println("Module initialization")
}

var Functions []string = []string{
	"Print",
}



func Print(input string) {
	fmt.Println("Safe module output: ", input)
}
