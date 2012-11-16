package main

import (
	"bufio"
	"fmt"
)

var ss *SyscallServer
var fs *FSServer
var pm *ProcessManager
var dm *DeviceManager

func main() {
	// initialization
	ss = NewSyscallServer()
	fs = NewFSServer()
	pm = NewProcessManager()
	dm = NewDeviceManager()

	r := bufio.NewReader(fs)
	b, err := r.ReadByte()
	fmt.Println(b, err)

	// run servers
	go ss.Run()

	// wait finish
	ss.Wait()
}
