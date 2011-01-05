package.path = package.path .. ';./tilegame/?.lua;./game/?.lua'

require 'game'
require 'luasdl'
require 'tilegame'

-- 
-- Convert default surface to another color
--
local function convert(sf, fg, bg)
   local nsf = SDL.CreateRGBSurface(SDL.SWSURFACE, 128, 128, 8)
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
   game = Game:new { map_w = options.map_w, map_h = options.map_h }
   game:initialize()
   game:add_nation('Assyria')

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
      rx = 0,
      ry = 0,
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
         ocean = tile['~']['black_white'],
         [SOLDIER] = tile['S']['black_white'],
      }
   }
end


--
-- Draw map
--
local function draw()
   for x = 1,game.map_w do
      for y = 1,game.map_h do
         -- terrain
         tg.map[x][y] = { tileset[options.color][game.map[x][y].terrain] }
         
         -- units
         local units = game:units(x,y)
         if #units > 0 then
            table.insert(tg.map[x][y], assert(tileset[options.color][units[1].military]))
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
      e = tg:wait_event()
      if e.type == SDL.QUIT then
         running = false
      elseif e.type == SDL.KEYDOWN then
         if e.sym == SDL.q then
            running = false
         end
      end
   until not running
   SDL.Quit()
end

prepare()
gameloop()
