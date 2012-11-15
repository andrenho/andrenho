package main

var ss *SyscallServer

func main() {
	// initialization
	ss = NewSyscallServer()

	// run servers
	go ss.Run()

	// wait finish
	ss.Wait()
}
