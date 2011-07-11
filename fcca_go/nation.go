package main

type Nation struct {
	name string
	units []*UnitInterface
}

func newNation(name string) *Nation {
	nation := Nation { 
		name:name, 
		units:make([]*UnitInterface, 1),
	}
	nation.units[0] = newLandUnit(2, 2, Settler)
	return &nation
}
