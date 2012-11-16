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

