package main

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

	// run servers
	go ss.Run()

	// run init
	ss.Exec(0, "/sbin/init", []string{}, []string{})

	// wait finish
	ss.Wait()
}
