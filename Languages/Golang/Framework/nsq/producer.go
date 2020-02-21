package main

import (
	"fmt"
	"log"
	"math/rand"
	"time"

	"github.com/nsqio/go-nsq"
)

func main() {
	nsqProducerAddr := "127.0.0.1:4150"
	producer, err := nsq.NewProducer(nsqProducerAddr, nsq.NewConfig())
	if err != nil {
		log.Println(err)
		return
	}

	rand.Seed(time.Now().UTC().UnixNano())
	for {
		if err = producer.Publish("topic2", []byte("ping2222333444555678")); err != nil {
			fmt.Println(err)
		}
		// r := rand.Intn(2)

		time.Sleep(time.Second * 2)
		fmt.Println("send success ")
	}
}
