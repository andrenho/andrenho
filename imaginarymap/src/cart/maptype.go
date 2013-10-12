package cart

import "wm"

type MapType interface {
	Draw(m *wm.Worldmap, p Projection, c *CartConfig)
}

func SVG_Header() string {
	return "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
}

func SVG_Footer() string {
	return "</svg>"
}

// vim: ts=4:sw=4:sts=4:noexpandtab
