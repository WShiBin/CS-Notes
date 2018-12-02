package main

import (
	"fmt"
	"sync"
	"time"
)

/**
 * wg.Wait() 都会收到信息
 */
func main() {
	var wg sync.WaitGroup

	wg.Add(1)

	go func() {
		wg.Wait()
		fmt.Println("func 1 exit")
	}()

	go func() {
		wg.Wait()
		fmt.Println("func 2 exit")
	}()

	go func() {
		wg.Wait()
		fmt.Println("func 3 exit")
	}()

	go func() {
		time.Sleep(time.Millisecond * 10)
		fmt.Println("done")
		wg.Done()
	}()

	wg.Wait()
	fmt.Println("main exit")
	time.Sleep(time.Millisecond * 10)
}
