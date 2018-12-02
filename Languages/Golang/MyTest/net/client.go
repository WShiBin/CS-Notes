package main

import (
	"fmt"
	"net/http"
	"net/http/httputil"
	_ "net/http/pprof"
)

func main() {
	request, err := http.NewRequest(http.MethodGet, "http://www.zhenai.com/zhenghun/", nil)
	//request, err := http.NewRequest(http.MethodGet, "http://www.imooc.com", nil)
	if err != nil {
		panic(err.Error())
	}
	//request.Header.Add("User-Agent", "Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1")
	client := http.Client{
		CheckRedirect: func(req *http.Request, via []*http.Request) error {
			fmt.Println(req)
			return nil
		},
	}
	resp, err := client.Do(request)
	//resp, err := client.Get("http://www.imooc.com")
	//resp, err := http.DefaultClient.Get("http://www.imooc.com")
	if err != nil {
		panic(err.Error())
	}
	defer resp.Body.Close()

	bytes, e := httputil.DumpResponse(resp, true)
	if e != nil {
		panic(e.Error())
	}

	fmt.Println(string(bytes))
}
