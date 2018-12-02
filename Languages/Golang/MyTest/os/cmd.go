package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os/exec"
)

func main() {

	//cmd := exec.Command("tr", "a-z", "A-Z")
	//cmd.Stdin = strings.NewReader("some input")
	//var out bytes.Buffer
	//cmd.Stdout = &out
	//err := cmd.Run()
	//if err != nil {
	//	log.Fatal(err)
	//}
	//fmt.Printf("in all caps: %q\n", out.String())

	//cmd := exec.Command("prog")
	cmd := exec.Command("ls", "-a", "-l")
	//cmd := exec.Command("pwd")
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		log.Fatal(err)
	}
	//cmd.Env = append(os.Environ(),
	//	"FOO=duplicate_value", // ignored
	//	"FOO=actual_value",    // this value is used
	//)
	//if err := cmd.Run(); err != nil {
	//	log.Fatal(err)
	//}
	//_ = cmd.Start()
	if err = cmd.Run(); err != nil {
		log.Fatal(err.Error())
	}
	cmd.Wait()
	//defer stdout.Close()
	if bytes, err := ioutil.ReadAll(stdout); err != nil {
		log.Fatal(err.Error())
	} else {
		fmt.Println(string(bytes))
	}
}
