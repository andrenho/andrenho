package main

import "fmt"

type Tile struct {
	terrain *Terrain
	x, y int
	game* Game
}

func newTile(game *Game, x, y int) *Tile {
	return &Tile { 
		terrain: Grassland,
		x: x,
		y: y,
		game: game,
	}
}

func (tile *Tile) units() []UnitIF {
	units := make([]UnitIF, 0)
	return units
	game := tile.game
	for _, nation := range game.nations {
		for _, unit := range nation.units {
			x, y := unit.pos()
			if x == tile.x && y == tile.y {
				units = append(units, unit)
			}
		}
	}
	return units
}
