package main

import ( 
	"flag"
	"log"
	"bufio"
	"io"
	"os"
)

var unbuffered bool

func main() {
	if infiles := parseFlags(); len(infiles) == 0 {
		catFile("-");
	} else {
		for _, file := range infiles {
			catFile(file)
		}
	}
}


func parseFlags() []string {
	flag.BoolVar(&unbuffered, "u", false, "write bytes without delay")
	flag.Parse()
	return flag.Args()
}


func openFile(file string) (*os.File, *bufio.Reader) {
	if file == "-" {
		return os.Stdin, bufio.NewReader(os.Stdin)
	}
	
	in, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}
	return in, bufio.NewReader(in)
}


func catFile(file string) {
	// open files
	out := os.Stdout
	in, r := openFile(file)
	defer in.Close()

	// copy bytes
	if unbuffered {
		catUnbuffered(r, out)
	} else {
		catBuffered(r, out)
	}
}


func catUnbuffered(r *bufio.Reader, out *os.File) {
	b, err := r.ReadByte()
	w := bufio.NewWriter(out)
	for err != io.EOF {
		if err != nil {
			log.Fatal(err)
		}
		e := w.WriteByte(b)
		if e != nil {
			log.Fatal(e)
		}
		e = w.Flush()
		if e != nil {
			log.Fatal(e)
		}
		b, err = r.ReadByte()
	}
}


func catBuffered(r *bufio.Reader, out *os.File) {
	b, err := r.ReadBytes('\n')
	for err != io.EOF {
		if err != nil {
			log.Fatal(err)
		}
		_, e := out.Write(b)
		if e != nil {
			log.Fatal(e)
		}
		b, err = r.ReadBytes('\n')
	}
}
