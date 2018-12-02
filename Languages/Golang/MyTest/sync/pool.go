package main

import (
	"fmt"
	"sync"
)

func main() {
	p := &sync.Pool{
		New: func() interface{} {
			return 0
		},
	}

	i := p.New()
	fmt.Println("i = ", i)
	a := p.Get().(int)
	p.Put(1)
	b := p.Get().(int)
	fmt.Println(a, b)
}
