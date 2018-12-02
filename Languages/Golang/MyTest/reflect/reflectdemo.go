package main

import (
	"fmt"
	"reflect"
)

type User struct {
	Name  string
	Age   int
	Hight int
}

func (u User) Hi() {
	fmt.Println("hi!!")
}

func main() {
	u := User{Name: "shibin", Age: 18, Hight: 170}
	//ShowInfo(u)
	ShowInfo(&u) // error
}

func ShowInfo(u interface{}) {
	t := reflect.TypeOf(u)
	fmt.Printf("%+v\n", t)

	if k := t.Kind(); k != reflect.Struct {
		fmt.Println("yes")
		//return
	} else {
		t = t.Elem()
	}

	//t := reflect.TypeOf(u)
	fmt.Println("---------------value ... ")
	v := reflect.ValueOf(u)
	for i := 0; i < t.NumField(); i++ {
		fmt.Printf(t.Field(i).Name)
		fmt.Printf(":  %+v\n", v.Field(i))
	}

	fmt.Println("---------------field ... ")
	for i := 0; i < t.NumField(); i++ {
		fmt.Println(t.Field(i))
	}

	fmt.Println("---------------method ... ")
	for i := 0; i < t.NumMethod(); i++ {
		fmt.Println(t.Method(i))
	}

}
