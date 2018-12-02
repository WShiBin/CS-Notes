package main

import (
	"fmt"
	"runtime"
	"time"
)

func main() {
	runtime.GOMAXPROCS(1)

	fun := func(i int) {
		time.Sleep(time.Second)
		fmt.Println(i, time.Now().UnixNano())
		//resp, _ := http.Get("https://www.baidu.com")
		//fmt.Println(i, resp.StatusCode)
	}

	go fun(1)
	go fun(2)
	go fun(3)
	go fun(4)
	go fun(5)
	go fun(6)
	go fun(7)
	go fun(8)
	go fun(9)
	go fun(10)

	ticker := time.NewTicker(time.Second)
	timer := time.NewTimer(time.Second * 3)

	ok := true
	for ok {
		select {
		case <-ticker.C:
			fmt.Println("dida...")
		case <-timer.C:
			fmt.Println("done")
			ok = false
		}
	}
}
