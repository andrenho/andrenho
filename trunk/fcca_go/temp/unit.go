package main

type A struct {
	x int
}

type B struct {
	A
	y int
}

func main() {
	var m [2]A
	
	m[0] = B { A { 1 }, 2 }
	m[0].x = 0
	m[0].y = 0

	m[1] = A { 3 }
	m[1].x = 0
}
