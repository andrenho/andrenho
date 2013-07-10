package main

type UI struct {
	city *City
}

func (ui *UI) Init() {
}

func (ui *UI) Running() bool {
	return false
}

func (ui *UI) GetEvents() {
}

func (ui *UI) Draw() {
}

func (ui *UI) Finish() {
}
