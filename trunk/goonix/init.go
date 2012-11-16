package main

import ("fmt")

type Init struct {
}

func (init Init) Run(args []string, envp []string) int {
	fmt.Printf("Hello World!\n")
	return 0
}
