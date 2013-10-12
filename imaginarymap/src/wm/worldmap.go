package wm

import (
	"math/rand"
)

type Worldmap struct {
	rnd      *rand.Rand
	Points   []Point
	Polygons []Polygon
}

func CreateWorldMap(cfg *MapConfig) *Worldmap {
	m := &Worldmap{
		rnd: rand.New(rand.NewSource(cfg.Seed)),
	}

	// initialize setup
	m.createPointGrid(cfg)

	return m
}

func (m *Worldmap) createPointGrid(cfg *MapConfig) {
	for lat := -90.0; lat < 90.0; lat += (1.0 / cfg.PointDensity) {
		for lon := -180.0; lon < 180.0; lon += (1.0 / cfg.PointDensity) {
			a := (m.rnd.Float64() - 0.5) * (0.5 / cfg.PointDensity)
			o := (m.rnd.Float64() - 0.5) * (0.5 / cfg.PointDensity)
			m.Points = append(m.Points, Point{lat+a, lon+o, 0})
		}
	}
}

// vim: ts=4:sw=4:sts=4:noexpandtab
