package cart

import (
	"bytes"
	"fmt"
	"wm"
)

type PoliticalMap struct {
}

func (mt *PoliticalMap) Draw(m *wm.Worldmap, proj Projection, c *CartConfig) {
	var b bytes.Buffer

	b.WriteString(SVG_Header())
	for _, poly := range m.Polygons {
		b.WriteString("<polygon points=\"")
		for _, pt := range poly.Points {
			x, y := proj.Convert(*pt)
			b.WriteString(fmt.Sprintf("%f,%f ", x, y))
		}
		b.WriteString("\" style=\"fill:lime; stroke:black; stroke-width:1\" />")
	}
	b.WriteString(SVG_Footer())

	fmt.Println(b.String())
}

// vim: ts=4:sw=4:sts=4:noexpandtab
