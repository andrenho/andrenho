package main

import (
	"log"
	//"fmt"
)

//
// file types
//

//
// virtual filesystem
//
type File interface {
	Content() string
}

type Executable interface {
	Run(args []string, envp []string) int
}

type VirtualFile struct {
	path string
	fileType FileType
}

type VirtualExecutable struct {
	*VirtualFile
	executable Executable
}

func (vf *VirtualFile) Content() string {
	return "content"
}

//
// fileserver
//
type FSServer struct {
	virtualFiles []File
}

func NewFSServer() *FSServer {
	log.Printf("Filesystem server initialized.\n")
	fs := &FSServer{}
	fs.virtualFiles = []File{
		VirtualExecutable{ &VirtualFile{ "/sbin/init", FILE }, &Init{} },
	}
	return fs
}

/*
func (fs *FSServer) VirtualFile(path string) (Program, error) {
	for _, vf := range fs.virtualFiles {
		if vf.path == path {
			return vf.program, nil
		}
	}
	return nil, NonVirtualError(0)
}*/

//
// errors
//
type NonVirtualError float64
func (v NonVirtualError) Error() string { return "not a virtual file" }

// init
type Init struct {}
func (init Init) Run(args []string, envp []string) int { return 0 }


func main() {
	//vf := &VirtualExecutable{ &VirtualFile{ path:"/sbin/init" }, &Init{} }
	//fmt.Println(vf.Content())
	fs := NewFSServer()
	_ = fs
}

