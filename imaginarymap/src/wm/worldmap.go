package wm

import (
	//"fmt"
	//"log"
	"math"
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
	// TODO
	// add random points
	for lat := 1.0; lat < 170.0; lat += (1.0 / cfg.PointDensity) {
		for lon := 1.0; lon < 350.0; lon += (1.0 / cfg.PointDensity) {
			o := m.rnd.Float64() * (1.0 / cfg.PointDensity)
			a := m.rnd.Float64() * (1.0 / cfg.PointDensity)
			vertices = append(vertices, &voronoi.Point{lon + o, lat + a})
		}
	}
	// calculate voronoi and add vertices
	edges := vor.GetEdges(&vertices, 10000.0, 50000)
	edges_clear := &edges // cleanupVoronoi(&edges)
	for _, e := range *edges_clear {
		p1 := Point{Longitude: e.Start.X, Latitude: e.Start.Y}
		p2 := Point{Longitude: e.End.X, Latitude: e.End.Y}
		m.Points[p1] = PointInfo{}
		m.Points[p2] = PointInfo{}

		p := Polygon{Points: []*Point{&p1, &p2}}
		m.Polygons = append(m.Polygons, p)
	}
}

// remove all edges that contain invalid points
func cleanupVoronoi(edges *voronoi.Edges) *voronoi.Edges {
	var edges_new voronoi.Edges
	for _, edge := range *edges {
		remove := false
		if math.IsNaN(edge.Start.X) || math.IsNaN(edge.Start.Y) {
			remove = true
		}
		if math.IsNaN(edge.End.X) || math.IsNaN(edge.End.Y) {
			remove = true
		}
		if edge.Start.X <= 0.0 || edge.Start.X >= 360.0 ||
		    edge.Start.Y <= 0.0 || edge.Start.Y >= 180.0 ||
		    edge.End.X <= 0.0 || edge.End.X >= 360.0 ||
		    edge.End.Y <= 0.0 || edge.End.Y >= 180.0 {
			remove = true
		}
		if !remove {
			edges_new = append(edges_new, edge)
		} 
	}
	return &edges_new
}

// vim: ts=4:sw=4:sts=4:noexpandtab
