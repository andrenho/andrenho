package main

type UnitIF interface {
	pos() (int, int)
}

type Unit struct {
	x, y int
	military *Military
}

func (unit *Unit) pos() (int, int) { 
	return unit.x, unit.y 
}
