package main

import "creator"
import "cart"

func main() {
	// create map
	wmap := creator.CreateWorldMap()

	// draw map
	cartconfig := cart.LoadCartographerConfig()
	projection := &cart.MercatorProjection{W: 800, H: 600}
	maptype := &cart.PoliticalMap{}
	maptype.Draw(wmap, projection, cartconfig)
}

// vim: ts=4:sw=4:sts=4:noexpandtab
