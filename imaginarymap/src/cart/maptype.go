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
	for pt, _ := range mt.m.Points {
		x, y := mt.proj.Convert(pt)
		b.WriteString(fmt.Sprintf("<!-- %f %f -->\n", pt.Longitude, pt.Latitude))
		b.WriteString(fmt.Sprintf(
			"\t<circle cx='%f' cy='%f' r='%f' fill='black' />\n",
			x, y, mt.config.GridPointSize))
	}
	for _, po := range mt.m.Polygons {
		b.WriteString(fmt.Sprintf("\t<polygon points='"))
		for _, pt := range po.Points {
			x, y := mt.proj.Convert(*pt)
			b.WriteString(fmt.Sprintf("%f,%f ", x, y))
		}
		b.WriteString(fmt.Sprintf("' style='stroke:black;stroke-width:%f'/>\n",
			mt.config.GridLineWidth))
	}
	return b.String()
}

// vim: ts=4:sw=4:sts=4:noexpandtab
