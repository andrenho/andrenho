package main

import (
	"log"
)

type SyscallServer struct {
	wait chan int
}

func NewSyscallServer() *SyscallServer {
	return &SyscallServer { wait: make(chan int) }
}

func (ss *SyscallServer) Run() {
	ss.wait <- 1
	log.Printf("Syscall server running.\n");
	
}

func (ss *SyscallServer) Wait() {
	<-ss.wait
}
