package cart

import (
	"bytes"
	"fmt"
	"wm"
)

type IMapType interface {
	Draw()
}

type MapType struct {
	m *wm.Worldmap
	proj Projection
	config *CartConfig
}

func (mt *MapType) SVG_Header() string {
	return "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n"
}

func (mt *MapType) SVG_Footer() string {
	return "</svg>"
}

func (mt *MapType) DrawPoints() string {
	var b bytes.Buffer
	for _, pt := range mt.m.Points {
		x, y := mt.proj.Convert(pt)
		b.WriteString(fmt.Sprintf(
			"\t<circle cx='%f' cy='%f' r='%f' fill='black' />\n",
			x, y, mt.config.GridPointSize))
	}
	return b.String()
}

// vim: ts=4:sw=4:sts=4:noexpandtab
