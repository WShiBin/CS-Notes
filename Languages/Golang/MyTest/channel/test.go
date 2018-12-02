package main

import (
	"fmt"
	"runtime"
)

func main() {
	ch := make(chan int, 1)
	ch <- 1
	ch2 := make(chan int, 1)
	ch2 <- <-ch
	fmt.Println(<-ch2)
	runtime.GC()
}
