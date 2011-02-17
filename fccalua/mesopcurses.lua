package.path = package.path .. ';./tilegame/?.lua;./game/?.lua'

require 'game'
require 'luasdl'
require 'tilegame'

options = {
   map_w = 80,
   map_h = 50,
   color = false,
}

--
-- Write text on the screen
--
local function write(text, x, y, color)
   assert(x >= 1 and y >= 1)
   color = color or 'black_white'
   local k = 0
   for v in text:gmatch('.') do
      tg.map[x+k][y] = { tile[v][color] }
      k = k + 1
   end
end

-- 
-- Convert default surface to another color
--
local function convert(sf, fg, bg)
   local nsf = SDL.CreateRGBSurface(SDL.SWSURFACE, 128, 128, 8)
   if bg == 'transparent' then
      bg = { 255, 0, 255 }
      nsf:SetColorKey(SDL.SRCCOLORKEY+SDL.RLEACCEL, 0)
   end
   nsf:SetPalette(SDL.LOGPAL+SDL.PHYSPAL, {bg, fg}, 0)
   for x=0,127 do
      for y=0,127 do
         nsf.pixels:set((y*nsf.w)+x, sf.pixels:get((y*nsf.w)+x))
      end
   end
   return nsf
end

--
-- Prepare execution
--
local function prepare()
   -- initialize game
   assert(options)
   game = Game:new { 
      map_w = options.map_w, 
      map_h = options.map_h,
      year = -2000,
      ui = ui,
      options = {
         auto_end_turn = true,
      }
   }
   game:initialize()
   player = game:add_nation('Assyria')

   dump(game)

   -- initialize SDL
   SDL.Init()
   scr = SDL.SetVideoMode(400, 300)
   if not scr then
      print('Could not open screen: ' .. SDL.GetError())
      os.exit(1)
   end
   white = scr.format:MapRGB(255, 255, 255)
   scr:FillRect(nil, white)
   scr:Flip()

   -- load images
   img = SDL.IMG_Load('images/terminal.png')
   if not img then
      print('Could not open terminal.png.')
      os.exit(1)
   end

   -- create tileset
   assert(options)
   tg = TileGame:new { 
      tile_w = 8, 
      tile_h = 8,
      map_w = game.map_w,
      map_h = game.map_h,
      rx = 1,
      ry = 1,
      scr = scr
   }
   tg:initialize()

   -- create tiles images
   if options.color then
      tiles_imgs = {
         black_white = img,
         yellow_green = convert(img, {255,255,128}, {0,192,0}),
         yellow_blue = convert(img, {255,255,128}, {0,64,128}),
         yellow_red = convert(img, {196,196,128}, {192,0,0}),
         white_red = convert(img, {255,255,255}, {192,0,0}),
      }
   else
      tiles_imgs = {
         black_white = img,
         black_tp = convert(img, {0,0,0}, 'transparent'),
         green_tp = convert(img, {0,255,0}, 'transparent')
      }
   end
   
   -- create tiles
   tile = {}
   local x, y = 0, 0
   for c=0,255 do
      tile[c] = {}
      tile[string.format('%c', c)] = tile[c]
      for color,image in pairs(tiles_imgs) do
         tile[c][color] = tg:tile(image, x, y, 1)
      end
      y = y + 8
      if y >= 128 then
         y = 0
         x = x + 8
      end
   end
   tg.blank = tile[' ']['black_white']

   -- map tileset
   tileset = {
      [true] = {
         [plains] = tile[' ']['yellow_green'],
         [sea] = tile[' ']['yellow_blue'],
         [warrior] = tile['w']['white_red'],
         city = tile['C']['yellow_red'],
      },
      [false] = {
         [sea] = tile[176]['black_white'],
         [warrior] = tile['w']['black_tp'],
         focus = tile[224]['green_tp'],
         city = tile['C']['black_tp'],
      }
   }
end


--
-- Draw map
--
local function draw(all)
   local all = all or false

   -- draw map
   for x = 1,game.map_w do
      for y = 1,game.map_h do
         if game.map[x][y].dirty or all == true then
            -- terrain
            tg.map[x][y] = { tileset[options.color][game.map[x][y].terrain] }

            -- city
            local city = game:city(x,y)
            if city then
               table.insert(tg.map[x][y], tileset[options.color]['city'])
            end
      
            -- units
            if player.focused and player.focused.x == x and player.focused.y == y then
               table.insert(tg.map[x][y], assert(tileset[options.color][player.focused.military]))
               table.insert(tg.map[x][y], tileset[options.color]['focus'])
            else
               local units = game:units(x,y)
               if #units > 0 then
                  table.insert(tg.map[x][y], assert(tileset[options.color][units[1].military]))
               end
            end
            game.map[x][y].dirty = false
         end
      end
   end

   local ly = math.floor(scr.h / 8)
   write(string.format('%d', game.year), 1, ly-1)
   if player.focused then
      local f = player.focused
      write(string.format('%s   M:%d', f.military.name, f.moves), 1, ly)
   end
   
   -- update screen
   tg:blit_map()
   scr:Flip()
end


-- 
-- Runs cityloop
--
local function cityloop(city)
   -- draw city
   tg:clear_map()
   write(string.format('%s', city.name), 1, 1)

   -- draw buildings
   local y = 3
   for _,b in ipairs(city.buildings) do
      write(b.name, 3, y)
      y = y + 3
   end

   -- other info
   write('Building:', 30, 8)
   if not city.building_now.building then
      write('Nothing', 31, 9)
   else
      write(string.format('%s (%d)', city.building_now.building.name, city.building_now.hammers), 31, 9)
   end

   -- goods
   write('Goods:', 30, 11)
   for k,g in ipairs(goods) do
      if g.can_buy and city.nation.prices[g].buy then
         write(string.format('%-10s  %d  %d/%d', g.name, city.storage[g], city.nation.prices[g].buy, city.nation.prices[g].sell), 31, 11+k)
      end
   end

   tg:blit_map()
   scr:Flip()

   -- events
   local e = tg:wait_event()
   if e.type == SDL.KEYDOWN then
      if e.sym == SDL.ESCAPE or e.sym == SDL.q then
         tg:clear_map()
         return
      end
   end
   cityloop(city)
end


--
-- Runs main loop
--
local function gameloop()
   local running = true
   repeat
      draw()
      local e = tg:wait_event()
      if e.type == SDL.QUIT then
         running = false
      elseif e.type == SDL.KEYDOWN then
         if e.sym == SDL.q then -- quit
            running = false
         elseif e.sym == SDL.w then -- wait
            player:next_unit()
         elseif e.sym == SDL.SPACE then -- end turn
            player:end_turn()
         elseif e.sym == SDL.t then -- test
            ui:question('After a discussion on this topic in the mailing list, I made my own function... I took, unknowingly, a way similar to the function above, except I use gfind to iterate, and I see the single matches at beginning and end of string as empty fields.', { 'abc', 'def' })
         elseif player.focused then
            fx,fy = nil,nil
            if     e.sym == SDL.KP1 or e.sym == SDL.j  then fx,fy = -1, 1 -- move
            elseif e.sym == SDL.KP2 or e.sym == SDL.k  then fx,fy =  0, 1
            elseif e.sym == SDL.KP3 or e.sym == SDL.l  then fx,fy =  1, 1
            elseif e.sym == SDL.KP4 or e.sym == SDL.u  then fx,fy = -1, 0
            elseif e.sym == SDL.KP6 or e.sym == SDL.o  then fx,fy =  1, 0
            elseif e.sym == SDL.KP7 or e.sym == SDL.N7 then fx,fy = -1,-1
            elseif e.sym == SDL.KP8 or e.sym == SDL.N8 then fx,fy =  0,-1
            elseif e.sym == SDL.KP9 or e.sym == SDL.N9 then fx,fy =  1,-1
            elseif e.sym == SDL.b then -- build city
               local city_name = ui:input('What is the name of the city?')
               if city_name then
                  c = player.focused:build_city(city_name)
                  cityloop(c)
               end
            end
            -- move unit
            if fx then 
               local f = player.focused
               local x, y = f.x, f.y
               if f:move(fx,fy) then
                  local tiles = { tileset[options.color][f.military], tileset[options.color]['focus'] }
                  tg:move(tiles, x, y, fx, fy)
               end
            end
         end
      end
   until not running
   SDL.Quit()
end


--
-- GUI
--
ui = {}
function ui:message(text)
   t = '--- Press SPACE ---'
   local last = 0
   for i,s in ipairs(string.wrap(text, math.floor(scr.w / 8) - 3):split("\n")) do
      write(s, 1, i)
      last = i
   end
   write(t, math.floor(scr.w / 8) - #t - 1, last + 1)
   tg:blit_map()
   scr:Flip()

   repeat
      local e = tg:wait_event()
   until e.type == SDL.KEYDOWN and e.sym == SDL.SPACE

   draw(true)
end

function ui:question(text, options, default)
   local default = default or 1
   local ss
   local keys = {}
   if options then
      ss = string.wrap(text, math.floor(scr.w/8) - 3):split("\n")
      table.insert(ss, '')
      for i,option in ipairs(options) do
         keys[SDL.KP0+i], keys[SDL.N0+i] = i, i
         if i == default then 
            keys[SDL.KP_ENTER], keys[SDL.RETURN] = i, i 
            option = option .. ' (*)'
         end
         table.insert(ss, ' [' .. i .. '] ' .. option)
      end
   else
      local opt
      if default == 1 then
         opt = ' [Y/n]'
         keys[SDL.KP_ENTER], keys[SDL.RETURN] = true, true
      elseif default == 2 then
         opt = ' [y/N]'
         keys[SDL.KP_ENTER], keys[SDL.RETURN] = false, false
      else
         assert(false)
      end
      keys[SDL.y] = true
      keys[SDL.n] = false
      ss = string.wrap(text .. opt, math.floor(scr.w/8) - 3):split("\n")
   end
   for i,s in ipairs(ss) do
      write(s, 1, i)
   end
   tg:blit_map()
   scr:Flip()

   local e
   repeat
      e = tg:wait_event()
   until e.type == SDL.KEYDOWN and keys[e.sym] ~= nil

   draw(true)
   return keys[e.sym]
end

function ui:input(text, default)
   return default or 'Test'
end

prepare()
gameloop()
