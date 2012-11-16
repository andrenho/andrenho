package main

import (
	"io"
	"fmt"
	"os"
)

//
// init
//
type Init struct {}
func (init Init) Run(args []string, envp []string) int { return 0 }
type VirtualExecutable interface { Run(args []string, envp []string) int }

//
// virtual HD
//
type FilePointer struct {
	data []byte
	exec VirtualExecutable
}

type VirtualHDFile struct {
	path string
	pointer FilePointer
}

var virtualHD = []VirtualHDFile {
	{ "/etc/inittab", FilePointer{ data: []byte { 1, 2, 3 } } },
	{ "/sbin/init", FilePointer{ exec: Init{} } },
}

//
// virtual FS
//
type VirtualFile struct {
	hdFile VirtualHDFile
	pos int
}

type File interface {
	Read(b []byte) (n int, err error)
}

func Open(name string) (file File, err error) {
	// TODO - path
	for _, hdFile := range virtualHD {
		if hdFile.path == name {
			return &VirtualFile { hdFile: hdFile, pos: 0 }, nil
		}
	}
	f, err := os.Open(name)
	return f, err
}

func (f *VirtualFile) Read(b []byte) (n int, err error) {
	if f.pos >= len(f.hdFile.pointer.data) {
		return 0, io.EOF
	}
	n := (f.pos+len(b))
	b = f.hdFile.pointer.data[f.pos:n]
	i := len(b)
	f.pos += i
	return i, nil
}

func main() {
	f, err := Open("/etc/inittab")
	fmt.Println(f, err)

	b := make([]byte, 10)
	n, err := f.Read(b)
	fmt.Println(n, err, b)
}
