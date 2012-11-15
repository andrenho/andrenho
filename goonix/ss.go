package main

import (
	"log"
)

type SyscallServer struct {
}

func (*SyscallServer) Init() {
	log.Printf("Syscall server initialized.\n");
}
