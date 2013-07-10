module dcity;

import std.stdio;

import gui.gui;
import city.city;

void main(string[] args)
{
    City city = new City(15, 15);
    GUI gui = new GUI(city);
    gui.initialize(600, 300);
    gui.main();
}
