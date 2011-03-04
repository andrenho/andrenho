local function set_colors(t, char1, char2, color1, color2)
   t.char = { char1, char2 }
   if color2 then
     t.color = { color1, color2 }
  else
     t.color = { color1, color1 }
  end
end

set_colors(tundra,   '.', '.', 'cyan')
set_colors(desert,   '.', '.', 'light_amber')
set_colors(plains,   '.', '.', 'dark_green')
set_colors(prairie,  '.', '.', 'light_green')
set_colors(steppe,   '.', '.', 'light_orange')
set_colors(marsh,    '.', '.', 'dark_gray')

set_colors(boreal_f, '.', '*', 'cyan', 'darkest_green')
set_colors(scrub,    '.', 'dne', 'light_amber', 'green')
set_colors(mixed_f,  '.', '*', 'dark_green')
set_colors(savannah, '.', '*', 'light_green')
set_colors(woodland, '.', '*', 'light_orange')
set_colors(swamp,    '.', '*', 'dark_grey')

set_colors(arctic,   '.', '.', 'white')
set_colors(sea,      '~', '~', 'light_blue')
set_colors(ocean,    '~', '~', 'dark_blue')
set_colors(hills,    '.', 'arrow2_n', 'darker_red')
set_colors(mountain, '.', 'arrow2_n', 'dark_grey', 'white')
