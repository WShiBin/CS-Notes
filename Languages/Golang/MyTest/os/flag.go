package main

import (
	"flag"
	"fmt"
)

func main() {
	var path string
	//var op string
	//var opNum int

	flag.StringVar(&path, "path", "/test/path", "please enter path")
	i := flag.String("tt", "/test/tt", "please enter path")
	flag.Parse()

	fmt.Println(path)
	fmt.Println(*i)
}