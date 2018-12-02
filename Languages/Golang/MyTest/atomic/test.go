package main

import (
	"sync/atomic"
	"testing"
	"time"
)

func TestName(t *testing.T) {
	ti := time.Now()
	//var count uint64 = 100000
	var count int64 = 100000

	for i := 0; i < 10000; i++ {
		go func() {
			//count++
			//atomic.AddInt64(&count, 1)
			atomic.AddInt64(&count, -1)
			//atomic.AddUint64(&count, -1)
			//atomic.AddUint64(&count, ^uint64(0))
			//^uint64(c-1)
		}()
	}
	//fmt.Println(time.Since(ti))
	t.Log(time.Since(ti))
}
