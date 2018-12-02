package main

import "fmt"


// ignore next cast exprees and execuate
func main() {

	var num int = 1

	switch num {
	case 1:
		fmt.Println("The integer was <= 4")
		fallthrough
	case 3:
		fmt.Println("The integer was <= 5")
		fallthrough
	case 4:
		fmt.Println("The integer was <= 6")
		//fallthrough
	case 5:
		fmt.Println("The integer was <= 7")
	case 6:
		fmt.Println("The integer was <= 8")
		//fallthrough
	default:
		fmt.Println("default case")
	}
}
