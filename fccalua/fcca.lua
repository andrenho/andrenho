#!/usr/bin/lua

options = {
   theme = 'curses',
	color = false,
   map_w = 10,
   map_h = 10,
}

require('theme/' .. options.theme)
