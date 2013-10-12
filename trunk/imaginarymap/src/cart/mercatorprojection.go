package cart

import (
	"math"
	"wm"
)

type MercatorProjection struct {
	W, H float64
}

func (mt *MercatorProjection) Convert(p wm.Point) (x, y float64) {
	x = math.Mod((mt.W * (180.0 + p.Longitude) / 360.0), (mt.W + (mt.W / 2.0)))
	latRad := p.Latitude * math.Pi / 180
	mercN := math.Log(math.Tan((math.Pi / 4) + (latRad / 2)))
	y = (mt.H / 2) - (mt.W * mercN / (2 * math.Pi))
	return
}

// vim: ts=4:sw=4:sts=4:noexpandtab
