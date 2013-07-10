package main

import (
	"flag"
	"fmt"
	"log"
	"strings"
)

func main() {

	// check flags
	flag.Parse()
	n_args := len(flag.Args())
	if n_args == 0 || n_args > 2 { log.Fatal("missing operand") }
	str := flag.Args()[0]
	suffix := ""
	if n_args == 2 { suffix = flag.Args()[1] }

	// case 2
	if strings.Count(str, "/") == len(str) { 
		fmt.Println("/")
		return
	}

	// case 3
	if strings.HasSuffix(str, "/") { 
		str = str[0:(len(str)-1)]
	} 

	// case 4
	lastSlashPos := strings.LastIndex(str, "/")
	if lastSlashPos == -1 { 
		fmt.Println(str)
		return
	}
	str = str[0:lastSlashPos]

	// case 5
	if suffix != "" && suffix != str && strings.HasSuffix(str, suffix) {
		lastPos := strings.LastIndex(str, suffix)
		str = str[0:lastPos-1]
	}

	fmt.Println(str)
}
