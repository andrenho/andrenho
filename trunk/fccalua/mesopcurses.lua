package.path = package.path .. ';./tilegame/?.lua;./game/?.lua'

require 'game'
require 'luasdl'
require 'tilegame'

options = {
   map_w = 20,
   map_h = 20,
   color = false,
}

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
      year = -1000,
   }
   game:initialize()
   player = game:add_nation('Assyria')

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
   img = SDL.IMG_Load('theme/curses/terminal.png')
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
   x, y = 0, 0
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
         grassland = tile[' ']['yellow_green'],
         ocean = tile[' ']['yellow_blue'],
         [SOLDIER] = tile['S']['white_red'],
      },
      [false] = {
         ocean = tile[176]['black_white'],
         [SOLDIER] = tile['S']['black_tp'],
         focus = tile[224]['green_tp'],
      }
   }
end


--
-- Draw map
--
local function draw()
   scr:FillRect(nil, white)
   for x = 1,game.map_w do
      for y = 1,game.map_h do
         -- terrain
         tg.map[x][y] = { tileset[options.color][game.map[x][y].terrain] }
         
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
      end
   end
   tg:blit_map()
   scr:Flip()
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

prepare()
gameloop()
