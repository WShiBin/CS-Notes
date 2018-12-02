package main

import (
	"fmt"
	"sync"
)

func main() {
	var w sync.WaitGroup

	//w.Add(delta) //添加多少个任务
	//w.Done() // 完成多少个任务
	//w.Wait() // 收到delta个done就会结束,否则阻塞

	w.Add(200)

	for i := 0; i < 200; i++ {
		go func(i int) {
			fmt.Println(i)
			w.Done()
		}(i)
	}

	w.Wait()
	fmt.Println("finished")
}
