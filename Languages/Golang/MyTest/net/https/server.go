package main

import (
	"fmt"
	"net/http"
	"log"
)

func HelloServer(w http.ResponseWriter, req *http.Request) {
	//m := make(map[string]string)
	w.Header().Set("Content-Type", "text/plain")
	w.Write([]byte("This is an example server.\n"))
	// fmt.Fprintf(w, "This is an example server.\n")
	// io.WriteString(w, "This is an example server.\n")
}

func main() {
	//ch := make(chan int, 3)
	var ch interface{}
	ch = 12
	fmt.Println(ch)
	http.HandleFunc("/hello", HelloServer)
	//http.ListenAndServe()
	err := http.ListenAndServeTLS(":443", "server.crt", "server.key", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
