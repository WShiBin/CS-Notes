package main

import (
	"fmt"
	"log"

	"github.com/nsqio/go-nsq"
)

func main() {
	nsqLookupAddr := "127.0.0.1:4150"
	producer, err := nsq.NewProducer(nsqLookupAddr, nsq.NewConfig())
	if err != nil {
		log.Println(err)
		return
	}

	if err = producer.Publish("topic2", []byte("ping22223334445556")); err != nil {
		fmt.Println(err)
	}
	fmt.Println("send success ")
}
