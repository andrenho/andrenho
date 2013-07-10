package main

type Land struct {
	w, h int
	_tile []*Tile
	game *Game
}

func newLand(game *Game, w, h int) *Land {
	land := Land { 
		w:w, 
		h:h, 
		_tile:make([]*Tile, w*h), 
	}
	for i := 0; i < w*h; i++ {
		land._tile[i] = newTile(game, i % w, i / w)
	}
	return &land
}

func (land *Land) tile(x, y int) *Tile {
	return land._tile[(y * land.w) + x]
}
