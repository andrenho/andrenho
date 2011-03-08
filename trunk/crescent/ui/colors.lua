local function set_colors(t, char1, char2, color1, color2)
   t.char = { char1, char2 }
   if color2 then
     t.color = { color1, color2 }
  else
     t.color = { color1, color1 }
  end
end

set_colors(tundra,   ',', ',', 'cyan', 'dark_cyan')
set_colors(desert,   '.', '.', 'light_amber', 'dark_yellow')
set_colors(plains,   ',', ',', 'darker_green', 'darkest_green')
set_colors(prairie,  ',', ',', 'dark_green', 'darker_green')
set_colors(steppe,   ';', ',', 'dark_amber', 'darker_amber')
set_colors(marsh,    ',', ',', 'dark_gray', 'darker_chartreuse')

set_colors(boreal_f, ',', '*', 'dark_cyan', 'darkest_green')
set_colors(scrub,    '.', 'teee', 'light_amber', 'darker_green')
set_colors(mixed_f,  '%', '*', 'darker_green', 'darkest_green')
set_colors(savannah, ';', '/', 'darker_amber', 'darker_yellow')
set_colors(woodland, ',', '*', 'darker_amber', 'darkest_green')
set_colors(swamp,    ',', '*', 'dark_gray', 'darkest_chartreuse')

set_colors(arctic,   '.', '.', 'white', 'lighter_gray')
set_colors(sea,      '~', '~', 'blue', 'dark_blue')
set_colors(ocean,    '~', '~', 'dark_blue', 'darker_blue')
set_colors(hills,    '.', 'arrow2_n', 'darkest_green', 'dark_orange')
set_colors(mountain, '.', 'arrow2_n', 'dark_gray', 'white')
