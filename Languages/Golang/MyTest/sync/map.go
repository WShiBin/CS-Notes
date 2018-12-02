package main

import (
	"fmt"
	"sync"
)

func main() {
	var m sync.Map
	//m.Store(key, val)  // 存储
	//m.Load(key) // 取,加载
	//m.LoadOrStore(key, val) // 存在就加载,不存在就存储
	//m.Delete(key) // 删除
	//m.Range(func(key, value interface{}) bool {
	//
	//	return true // 继续遍历
	//})

	m.Store(1, "C")
	m.Store(2, "C++")
	m.Store(3, "data structure")
	m.Store(4, "QT")
	m.Store(5, "Linux")
	m.Store(6, "Golang")
	m.Store(7, "go micro")

	fmt.Println(m.Load(6))
	fmt.Println(m.LoadOrStore(8, "GRPC"))
	fmt.Println(m.Load(8))

	fmt.Println("----------------")
	m.Range(func(key, val interface{}) bool {
		fmt.Println(key, val)
		return true
	})

	fmt.Println("----------------")

	m.Delete(7)
	m.Range(func(key, val interface{}) bool {
		fmt.Println(key, val)
		return true
	})

}
