package main

import (
	"fmt"
)

type ttype string

func (t ttype) get() {
	fmt.Println(t)
}
func (t ttype) set(str string) {
	t = ttype(str)
	fmt.Println(t)
}

func main() {
	var t ttype = "hehe"
	//ttype.get(t)
	ttype.set(t, "haha")
}
