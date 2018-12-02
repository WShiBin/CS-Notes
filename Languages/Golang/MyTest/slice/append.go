package main

import "fmt"

func main() {
	sli := make([]int, 10)
	var l, c = len(sli), cap(sli)

	for i := 0; i < 5000; i++ {
		sli = append(sli, i)
		if c != cap(sli) {
			fmt.Println(l, c)
			l, c = len(sli), cap(sli)
		}
	}
	//sli2 := make([]int, 30)
	//var l, c int = len(sli), cap(sli)
	//
	//fmt.Println(len(sli), cap(sli))
	//fmt.Println("-------------")
	//for i := 0; i < 50; i++ {
	//	sli = append(sli, sli2...)
	//	l, c = len(sli), cap(sli)
	//	fmt.Println(l, c)
	//}
}
