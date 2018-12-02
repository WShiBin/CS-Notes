package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"
	"syscall"
	"time"

	"github.com/nsqio/go-nsq"
)

// 消费者
type Consumer struct {
}

func (*Consumer) HandleMessage(message *nsq.Message) error {
	//panic("implement me")
	fmt.Println("client recive", message.NSQDAddress, string(message.Body))
	return nil
}

func main() {
	config := nsq.NewConfig()
	config.LookupdPollInterval = 15 * time.Second

	topic := "topic2"
	//chanStr := "test_chan1"
	//chanStr := "nsq_to_file"
	chanStr := "topic2_chan1"
	nsqLookupAddr := "127.0.0.1:4161"
	consumer, err := nsq.NewConsumer(topic, chanStr, config)
	if err != nil {
		log.Println(err.Error())
		return
	}
	con := &Consumer{}
	consumer.AddHandler(con)
	if err := consumer.ConnectToNSQLookupd(nsqLookupAddr); err != nil {
		fmt.Println(err.Error())
	}

	c := make(chan os.Signal)
	signal.Notify(c, syscall.SIGINT)
	<-c
}
