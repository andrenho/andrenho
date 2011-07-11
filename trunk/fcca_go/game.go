package main

type Game struct {
	year int
	land *Land
	nations []*Nation
}

func newGame() *Game {
	game := Game { 
		year: -2000, 
		nations: make([]*Nation, 1), 
	}
	game.land = newLand(&game, 10, 10)
	// land
	for x := 3; x <= 5; x++ {
		for y := 3; y <= 5; y++ {
			game.land.tile(x,y).terrain = Ocean
		}
	}
	// nation
	game.nations[0] = newNation("Test")
	return &game
}
