package cart

import "wm"

type Projection interface {
	Convert(p wm.Point) (x, y float64)
}

// vim: ts=4:sw=4:sts=4:noexpandtab
