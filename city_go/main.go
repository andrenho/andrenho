package main

func main() {
	city := &City{}
	ui := &UI{ city: city }

	ui.Init()
	for ui.Running() {
		ui.GetEvents()
		ui.Draw()
	}
	ui.Finish()
}
