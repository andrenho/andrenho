package main

import "fmt"

type Unit struct {
	_x int
}

type LandUnit struct {
	Unit
}

type SeaUnit struct {
	Unit
}

type UnitIF interface {
	x() int
}

func (u Unit) x() int {
	return u._x
}

func main() {
	var m [2]UnitIF
	a := LandUnit{ Unit{ 1 }}
	b := SeaUnit{ Unit{ 1 }}

	m[0] = a
	m[1] = b

	fmt.Println(m[0])
	fmt.Println(m[1])
}
