package main

import (
	"fmt"
	"path"
	"runtime"
)

func test() {
	pc, str, line, ok := runtime.Caller(1)
	funcName := runtime.FuncForPC(pc).Name()
	fmt.Println(funcName)
	fileName := path.Base(str)
	fmt.Println(fileName)
	fmt.Println(pc, str, line, ok)
}

func main() {
	test()
}
