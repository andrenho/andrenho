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


-- create char list
chars = { 'HLINE', 'VLINE', 'NE', 'NW', 'SE', 'SW', 'DHLINE', 'DVLINE', 'DNE', 'DNW', 'DSE', 'DSW', 'TEEW', 'TEEE', 'TEEN', 'TEES', 'DTEEW', 'DTEEE', 'DTEEN', 'DTEES', 'BLOCK1', 'BLOCK2', 'BLOCK3', 'CROSS', 'ARROW_N', 'ARROW_S', 'ARROW_E', 'ARROW_W', 'ARROW2_N', 'ARROW2_S', 'ARROW2_E', 'ARROW2_W', 'DARROW_H', 'ARROW_V', 'CHECKBOX_UNSET', 'CHECKBOX_SET', 'RADIO_UNSET', 'RADIO_SET', 'SUBP_NW', 'SUBP_NE', 'SUBP_N', 'SUBP_SE', 'SUBP_DIAG', 'SUBP_E', 'SUBP_SW', 'SMILY', 'SMILY_INV', 'HEART', 'DIAMOND', 'CLUB', 'SPADE', 'BULLET', 'BULLET_INV', 'MALE', 'FEMALE', 'NOTE', 'NOTE_DOUBLE', 'LIGHT', 'EXCLAM_DOUBLE', 'PILCROW', 'SECTION', 'POUND', 'MULTIPLICATION', 'FUNCTION', 'RESERVED', 'HALF', 'ONE_QUARTER', 'COPYRIGHT', 'CENT', 'YEN', 'CURRENCY', 'THREE_QUARTERS', 'DIVISION', 'GRADE', 'UMLAUT', 'POW1', 'POW3', 'POW2', 'BULLET_SQUARE' }
print('typedef struct { char name[30]; char c; UT_hash_handle hh; } CHAR;')
print('')
print('CHAR *chars = NULL;')
print('')
print('void init_chars()')
print('{')
print('\tCHAR *c;')

function add_char(s)
   print('\t')
   print('\t// ' .. s)
   print('\tc = malloc(sizeof(CHAR));')
   print('\tstrcpy(c->name, "' .. s:lower() .. '");')
   print('\tc->c = TCOD_CHAR_' .. s .. ';')
   print('\tHASH_ADD_STR(chars, name, c);')
end

for _,c in ipairs(chars) do add_char(c) end
print('}')

