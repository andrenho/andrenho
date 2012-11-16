package main

import (
	"log"
)

type DeviceManager struct {
}

func NewDeviceManager() *DeviceManager {
	log.Printf("Device manager initialized.\n")
	return &DeviceManager{}
}
