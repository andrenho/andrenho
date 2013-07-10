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
