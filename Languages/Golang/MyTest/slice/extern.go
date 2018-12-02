package main

import "fmt"

func main() {
	sli := make([]int, 3, 5)

	//sli := []int{1, 2, 3, 4, 5, 6, 7}
	sli = addToFirst(sli, 11)
	sli = addToFirst(sli, 12)
	sli = addToFirst(sli, 13)
	sli = addToFirst(sli, 14)
	//sli = deleteByIndex(sli, 3)
	//sli = deleteByElm(sli, 5)
	fmt.Println(sli)
}

func deleteByElm(sli []int, elm int) []int {
	for index, val := range sli {
		if val == elm {
			sli = deleteByIndex(sli, index)
			return sli
		}
	}
	return sli
}

func deleteByIndex(sli []int, index int) []int {
	if index >= len(sli) {
		return sli
	}
	sli = append(sli[:index], sli[index+1:]...)
	return sli
}

func addToFirst(sli []int, elm int) []int {
	//sli = append(sli, sli[len(sli)-1])
	//
	//for i := len(sli) - 1; i > 0; i-- {
	//	sli[i] = sli[i-1]
	//}
	//sli[0] = elm

	sli = append([]int{elm}, sli...)
	return sli
}
