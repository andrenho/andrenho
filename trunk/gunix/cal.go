package main

import (
	"flag"
	"fmt"
	"log"
	"strconv"
)

func main() {
	var month, year uint64
	var err error

	flag.Parse()
	if len(flag.Args()) > 0 { 
		month, err = strconv.ParseUint(flag.Args()[0], 10, 16) 
		if err != nil { log.Fatal(err) }
	} 
	if len(flag.Args()) == 2 { 
		year, err = strconv.ParseUint(flag.Args()[1], 10, 16) 
		if err != nil { log.Fatal(err) }
	}

	fmt.Println(month, year)
}
