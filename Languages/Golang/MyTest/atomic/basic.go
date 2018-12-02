package main

import (
	"fmt"
	"sync"
	"sync/atomic"
	"time"
)

func main() {
	var count uint64 = 10000000
	var wg sync.WaitGroup
	wg.Add(1000000)
	t := time.Now()

	for i := 0; i < 1000000; i++ {
		go func() {
			//count++
			//atomic.AddInt64(&count, 1)
			//atomic.AddInt64(&count, -1)
			//atomic.AddUint64(&count, -1)
			atomic.AddUint64(&count, ^uint64(0))
			//^uint64(c-1)
			wg.Done()
		}()
	}
	wg.Wait()
	fmt.Println(time.Since(t))
	fmt.Println(count)

	// -------------------------------------------
	//var mutex sync.Mutex
	//
	//for i := 0; i < 1000000; i++ {
	//	go func() {
	//		mutex.Lock()
	//		count++
	//		mutex.Unlock()
	//		//atomic.AddInt64(&count, 1)
	//		//atomic.AddInt64(&count, -1)
	//		//atomic.AddUint64(&count, -1)
	//		//atomic.AddUint64(&count, ^uint64(0))
	//		//^uint64(c-1)
	//		wg.Done()
	//	}()
	//}
	//wg.Wait()
	//fmt.Println(time.Since(t))
	//fmt.Println(count)

}
