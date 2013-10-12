package main

import (
	"cart"
	"wm"
)

func main() {
	// create map
	mconfig := wm.LoadMapConfig()
	wmap := wm.CreateWorldMap(mconfig)

	// draw map
	cartconfig := cart.LoadCartographerConfig()
	projection := &cart.MercatorProjection{W: 1200, H: 600}
	maptype := cart.NewPoliticalMap(wmap, projection, cartconfig)
	maptype.Draw()
}

// vim: ts=4:sw=4:sts=4:noexpandtab
