package main

import (
	"log"
)

type ProcessManager struct {
}

func NewProcessManager() *ProcessManager {
	log.Printf("Process manager initialized.\n")
	return &ProcessManager{}
}

func (pm *ProcessManager) RunProgram(pid int, path string, argv []string, 
				envp []string) {
	prog, err := fs.VirtualFile(path)
	if err != nil {
		panic("real files not supported")
	}
	prog.Run(argv, envp)
}
