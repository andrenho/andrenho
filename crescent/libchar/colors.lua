-- create color list
local colors = { 
   'red', 'flame', 'orange', 'amber', 'yellow', 'lime', 'chartreuse', 'green', 
   'sea', 'turquoise', 'cyan', 'sky', 'azure', 'blue', 'han', 'violet', 
   'purple', 'fuchsia', 'magenta', 'pink', 'crimson', 'gray', 'sepia'
}

local indiv_colors = {
   'brass', 'copper', 'gold', 'silver', 'celadon', 'peach', 'black', 'white'
}

local intensities = {
   'desaturated', 'lightest', 'lighter', 'light', 'dark', 'darker', 'darkest'
}

print('#include <libtcod.h>')
print('#include <stdlib.h>')
print('#include "uthash.h"')
print('typedef struct { char name[50]; TCOD_color_t color; UT_hash_handle hh; } COLOR;')
print('')
print('COLOR *colors = NULL;')
print('')
print('void init_colors()')
print('{')
print('\tCOLOR *c;')

function add_color(s)
   print('\t')
   print('\t// ' .. s)
   print('\tc = malloc(sizeof(COLOR));')
   print('\tstrcpy(c->name, "' .. s .. '");')
   print('\tc->color = TCOD_' .. s .. ';')
   print('\tHASH_ADD_STR(colors, name, c);')
end

for _,c in ipairs(colors) do add_color(c) end
for _,c in ipairs(indiv_colors) do add_color(c) end
for _,c in ipairs(colors) do 
   for _,i in pairs(intensities) do
      if not (i == 'desaturated' and (c == 'gray' or c == 'sepia')) then
         add_color(i .. '_' .. c)
      end
   end
end

print('}')

