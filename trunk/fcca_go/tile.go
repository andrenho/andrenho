package main

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

func (tile *Tile) units() []*UnitInterface {
	units := make([]*UnitInterface, 0)
	game := tile.game
	for _, nation := range game.nations {
		for _, unit := range nation.units {
			if unit.x() == tile.x && unit.y() == tile.y {
				units = append(units, unit)
			}
		}
	}
	return units
}
