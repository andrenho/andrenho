package main

type UnitIF interface {
	Move()
}

type Unit struct {
	x, y int
	military *Military
}

func (unit *Unit) x() { return unit.x }
func (unit *Unit) y() { return unit.y }
