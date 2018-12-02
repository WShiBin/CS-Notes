package main

import (
	"fmt"
	"sync"
)

func main() {
	ch := make(chan int, 3)
	wg := sync.WaitGroup{}
	wg.Add(10)

	go func() {
		for i := 0; i < 10; i++ {
			ch <- i
			wg.Done()
		}
		close(ch)
	}()

	go func() {
		for {
			select {
			case i := <-ch:
				fmt.Println("func1", i)
			default:
			}
		}
	}()
	go func() {
		for {
			select {
			case i := <-ch:
				fmt.Println("func2", i)
			default:
			}
		}
	}()
	wg.Wait()
}
