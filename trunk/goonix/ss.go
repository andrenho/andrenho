package main

import (
	"log"
)

type SyscallServer struct {
	wait chan int
}

func NewSyscallServer() *SyscallServer {
	log.Printf("Syscall server initialized.\n");
	return &SyscallServer { wait: make(chan int) }
}

func (ss *SyscallServer) Run() {
	ss.wait <- 1
	log.Printf("Syscall server running.\n");
	
}

func (ss *SyscallServer) Execve(pid int, path string, argv []string, 
				envp []string) error {
	log.Printf("execve PID %d\n", pid)
	go pm.RunProgram(pid, path, argv, envp)
	return nil
}

func (ss *SyscallServer) Wait() {
	<-ss.wait
	log.Printf("Syscall server finished.\n")
}
