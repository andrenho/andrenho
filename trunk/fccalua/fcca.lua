#!/usr/bin/lua

options = {
   theme = 'curses',
   color = true,
   map_w = 20,
   map_h = 20,
}

require('theme/' .. options.theme)
