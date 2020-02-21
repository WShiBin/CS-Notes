package main

import (
	"crypto/md5"
	"fmt"
	"hash/crc32"
	"io"
	"log"
	"os"
)

func main() {
	hostname, err := os.Hostname()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(hostname)
	h := md5.New()
	io.WriteString(h, "localhost")
	bytes := h.Sum(nil)
	fmt.Println(bytes)
	// h.Write([]byte("localhost"))
	defaultID := int64(crc32.ChecksumIEEE(h.Sum(nil)) % 1024)
	fmt.Println(defaultID)
}
