package main

import (
	"log"
)

type FSServer struct {
}

func NewFSServer() *FSServer {
	log.Printf("Filesystem server initialized.\n")
	return &FSServer{}
}

func (*FSServer) Read(p []byte) (n int, err error) {
	p[0] = 65
	return 3, nil
}
