package wm

import (
	//"fmt"
	//"log"
	"math/rand"
	"voronoi"
)

type Worldmap struct {
	rnd      *rand.Rand
	Points   map[Point]PointInfo
	Polygons []Polygon
}

func CreateWorldMap(cfg *MapConfig) *Worldmap {
	m := &Worldmap{
		rnd:    rand.New(rand.NewSource(cfg.Seed)),
		Points: make(map[Point]PointInfo),
	}

	// setup basic map configuration
	m.createPolygonsVoronoi(cfg)

	return m
}

func (m *Worldmap) createPolygonsVoronoi(cfg *MapConfig) {
	var vertices voronoi.Vertices
	vor := voronoi.Voronoi{}
	// add border points

	// add random points
	for lat := 0.0; lat < 180.0; lat += (1.0 / cfg.PointDensity) {
		for lon := 0.0; lon < 360.0; lon += (1.0 / cfg.PointDensity) {
			o := m.rnd.Float64() * (1.0 / cfg.PointDensity)
			a := m.rnd.Float64() * (1.0 / cfg.PointDensity)
			if lon+o >= 360 {
				o = 0.0
			}
			if lat+a >= 180 {
				a = 0.0
			}
			vertices = append(vertices, &voronoi.Point{lon + o, lat + a})
		}
	}
	// calculate voronoi and add vertices
	for _, e := range vor.GetEdges(&vertices, 360, 180) {
		p1 := Point{Longitude: e.Start.X - 180.0, Latitude: e.Start.Y - 90.0}
		p2 := Point{Longitude: e.End.X - 180.0, Latitude: e.End.Y - 90.0}
		m.Points[p1] = PointInfo{}
		m.Points[p2] = PointInfo{}
		p := Polygon{Points: []*Point{&p1, &p2}}
		m.Polygons = append(m.Polygons, p)
	}
}

// vim: ts=4:sw=4:sts=4:noexpandtab
