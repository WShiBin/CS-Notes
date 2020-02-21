## for expression

```go
package main

import "fmt"

func main() {
  // normal
	for index := 0; index < 3; index++ {
		fmt.Println("normal for")
	}

  // for range
	fmt.Println("-------------------------------------")
	for _, val := range "hehexixi" {
		fmt.Println(val)
	}

  // for like while
	fmt.Println("-------------------------------------")
	var f = 10
	for f < 13 {
		fmt.Println(f)
		f++
	}
}
```



## Switch

```go
package main

import (
	"fmt"
	"time"
)

func main() {

	// normal
	i := 2
	switch i {
	case 1:
		fmt.Println("11111111111111")
	case 2:
		fmt.Println("22222222222222")
	case 3:
		fmt.Println("33333333333333")
	}

	// multi case
	switch time.Now().Weekday() {
	case time.Sunday, time.Saturday:
		fmt.Println("it's the weekend")
	default:
		fmt.Println("it's a weekday")
	}

	// like if
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("it's before the noon")
	default:
		fmt.Println("it's after the noon")
	}

	// type
	whatAmI := func(n interface{}) {
		switch t := n.(type) {
		case int:
			fmt.Println("int type: ", t)
		case string:
			fmt.Println("string type: ", t)
		case int64:
			fmt.Println("int64 type: ", t)
		default:
			fmt.Println("unkown type")
		}
	}
	whatAmI(10)
	whatAmI("xixi")
	whatAmI(int64(80))
}
```





## Error

```go
package main

import (
	"errors"
	"fmt"
)

// built-in error
func f1(arg int) (int, error) {
	if arg == 42 {
		return -1, errors.New("arg == 42")
	}
	return arg, nil
}

// custom error
type argError struct {
	arg  int
	prob string
}

// override Error() 
// Note:notice the receiver type
func (err *argError) Error() string {
	return fmt.Sprintf("%s : %d", err.prob, err.arg)
}

func f2(arg int) (int, error) {
	if arg == 42 {
		return -1, &argError{arg: -1, prob: "error msg"}
	}
	return arg, nil
}

func main() {
	for _, i := range []int{7, 42} {
		if r, e := f1(i); e != nil {
			fmt.Println("f1 failed:", e)
		} else {
			fmt.Println("f1 worked:", r)
		}
	}

	// custom
	for _, i := range []int{7, 42} {
		if r, e := f2(i); e != nil {
			fmt.Println("f2 failed:", e)
		} else {
			fmt.Println("f2 worked:", r)
		}
	}

	_, e := f2(42)
	// e.(*argError): 这里*argError必须实现了Error interface
	if a, ok := e.(*argError); ok {
		fmt.Println(a.arg)
		fmt.Println(a.prob)
	}
}
```

