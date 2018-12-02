package main

import (
	"fmt"
	"os"
)

func main() {
	args := os.Args[1:]
	fmt.Println(len(args))
	for index, val := range args {
		fmt.Println(index, val)
	}
}
