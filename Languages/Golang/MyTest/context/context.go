package main

import (
	"context"
	"fmt"
	"time"
)

func main() {
	//var ctx context.Context = context.Background()

	//ctx, cancel := context.WithCancel(context.Background())
	ctx, deadLine := context.WithDeadline(context.Background(), time.Now().Add(time.Second*3))
	valCtx := context.WithValue(ctx, "id", 12345)
	fmt.Println(valCtx.Value("id"))

	go func() {
		for {
			time.Sleep(time.Millisecond * 100)
			select {
			case <-valCtx.Done():
				fmt.Println(valCtx.Value("id"))
				fmt.Println("done")
			default:
				fmt.Println("default")
			}
		}
	}()

	go func() {
		for {
			time.Sleep(time.Millisecond * 100)
			select {
			case <-ctx.Done():
				fmt.Println("done --- ")
			default:
				fmt.Println("default ---")
			}
		}
	}()

	time.Sleep(time.Second)
	deadLine()
	time.Sleep(time.Millisecond * 100)
}
