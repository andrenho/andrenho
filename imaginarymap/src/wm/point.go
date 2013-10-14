package wm

type Point struct {
	Longitude, Latitude float64
}

func (p *Point) Correct() {
	if p.Longitude < -180 || p.Longitude > 180 {
		p.Longitude = 179.99
	}
	if p.Latitude < -90 || p.Latitude > 90 {
		p.Latitude = 89.99
	}
}

type PointInfo struct {
}

// vim: ts=4:sw=4:sts=4:noexpandtab
