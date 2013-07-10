package main

import "fmt"

func main() {
	game := newGame()
	game.draw()
}

func (game *Game) draw() {
	for y := 0; y < game.land.h; y++ {
		for x := 0; x < game.land.w; x++ {
			fmt.Printf("%c", game.char(x,y))
		}
		fmt.Printf("\n")
	}
}

func (game *Game) char(x, y int) byte {
	var c byte;
	
	switch game.land.tile(x,y).terrain {
	case Grassland: c = ' '
	case Ocean: c = '.'
	}

	units := game.land.tile(x,y).units()
	if len(units) > 0 {
		c = 'X'
	}

	return c
}
