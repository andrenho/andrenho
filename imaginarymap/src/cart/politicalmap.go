package cart

import (
	"bytes"
	"fmt"
	"wm"
)

type PoliticalMap struct {
	MapType
}

func NewPoliticalMap(m *wm.Worldmap, proj Projection,
	config *CartConfig) IMapType {
	return &PoliticalMap{MapType{m, proj, config}}
}

func (mt *PoliticalMap) Draw() {
	var b bytes.Buffer

	b.WriteString(mt.SVG_Header())

	// draw grid
	if mt.config.DrawGrid {
		b.WriteString(mt.DrawPoints())
	}

	b.WriteString(mt.SVG_Footer())

	fmt.Println(b.String())
}

// vim: ts=4:sw=4:sts=4:noexpandtab
