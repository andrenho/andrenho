package main

import (
	"log"
)

type NonVirtualError float64
func (v NonVirtualError) Error() string { return "not a virtual file" }

type Program interface {
	Run(args []string, envp []string) int
}

type VirtualFile struct {
	path string
	program Program
}

type FSServer struct {
	virtualFiles []VirtualFile
}

func NewFSServer() *FSServer {
	log.Printf("Filesystem server initialized.\n")
	fs := &FSServer{}
	fs.virtualFiles = []VirtualFile{
		{ "/sbin/init", Init{} },
	}
	return fs
}

func (fs *FSServer) VirtualFile(path string) (Program, error) {
	for _, vf := range fs.virtualFiles {
		if vf.path == path {
			return vf.program, nil
		}
	}
	return nil, NonVirtualError(0)
}
