package main

import (
	"log"
)

type Process struct {
	pid int
	children []*Process
	father *Process
}

type ProcessManager struct {
	init *Process
}

func NewProcessManager() *ProcessManager {
	log.Printf("Process manager initialized.\n")
	return &ProcessManager{ init: nil }
}

func (pm *ProcessManager) RunProgram(pid int, path string, argv []string, 
				envp []string) {
	// check for file type
	prog, err := fs.VirtualFile(path)
	if err != nil {
		panic("real files not supported")
	}

	// add to process control
	if pid == 0 {
		pm.init = &Process{ pid: 1 }
	} else {
		panic("TODO")
	}

	// run program
	prog.Run(argv, envp)

	// remove from process control
	// TODO
}
