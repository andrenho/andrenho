package main

type LandUnit struct {
	Unit
}

func newLandUnit(x, y int, military *Military) *LandUnit {
	return &LandUnit {
		Unit {
			x: x,
			y: y,
			military: military,
		},
	}
}

func (unit *LandUnit) Move(int dir) {
}

func (unit *LandUnit) x() { return unit.x }
func (unit *LandUnit) y() { return unit.y }
