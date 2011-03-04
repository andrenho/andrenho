require 'ui/colors'

map = {
   rx = -1,
   ry = -1,
   redraw = true
}


function map.init()
   local function rnd()
      r = {}
      for i=1,9 do table.insert(r, math.random(1,2)) end
      return r
   end
   for x=1, game.w do
      for y=1, game.h do
         game.map[x][y].rnd = rnd()
      end
   end
end


function map.draw()

   if not map.redraw then return end

   ch.clear()

   local cx, cy = 0, 0
   local ix = math.max(map.rx, 1)
   local iy = math.max(map.ry, 1)
   for x=ix, ix+screen_w/3 do
      cx = cx + 1
      cy = 0
      for y=iy, iy+screen_h/3 do
         map.draw_tile(x, y)
         cy = cy + 1
         --map.draw_units(x, y)
         --map.draw_town(x, y)
      end
   end
   --print(map.rx, map.ry)

   --map.draw_interface()

   ch.flush()
   map.redraw = false

end


function map.draw_tile(x, y)
   assert(x >= 1 and y >= 1 and x <= game.w and y <= game.h)

	-- The edges of the terrain can be overlapped by other types of
	-- terrain. As such, the image of the terrain is:
	--
	-- 213
	-- 111
	-- 141
   
   -- get central color and char (1)
   local color = {}
   local char = {}
   color[1], char[1] = game.map[x][y].terrain.color, game.map[x][y].terrain.char
   for i=2,5 do color[i], char[i] = color[1], char[1] end

   -- find corners (BORING)
   if x > 1 and y > 1 
   and game.map[x-1][y].terrain.ovl < game.map[x][y].terrain.ovl 
   and game.map[x][y-1].terrain.ovl < game.map[x][y].terrain.ovl then
      color[2], char[2] = game.map[x-1][y].terrain.color, game.map[x-1][y].terrain.char
   end

   if x < game.w and y > 1 
   and game.map[x+1][y].terrain.ovl < game.map[x][y].terrain.ovl 
   and game.map[x][y-1].terrain.ovl < game.map[x][y].terrain.ovl then
      color[3], char[3] = game.map[x+1][y].terrain.color, game.map[x+1][y].terrain.char
   end

   if x > 1 and y < game.h 
   and game.map[x-1][y].terrain.ovl < game.map[x][y].terrain.ovl 
   and game.map[x][y+1].terrain.ovl < game.map[x][y].terrain.ovl then
      color[4], char[4] = game.map[x-1][y].terrain.color, game.map[x-1][y].terrain.char
   end

   if x < game.w and y < game.h 
   and game.map[x+1][y].terrain.ovl < game.map[x][y].terrain.ovl 
   and game.map[x][y+1].terrain.ovl < game.map[x][y].terrain.ovl then
      color[5], char[5] = game.map[x+1][y].terrain.color, game.map[x+1][y].terrain.char
   end

   if not colors then for i=1,5 do color[i] = { 'lightest_gray', 'lightest_gray' } end end

   -- draw
   for xx=0,2 do
      for yy=0,2 do

         local c=1
         if xx == 0 and yy == 0 then c = 2
         elseif xx == 2 and yy == 0 then c = 3
         elseif xx == 0 and yy == 2 then c = 4
         elseif xx == 2 and yy == 2 then c = 5
         end
         
         local n = game.map[x][y].rnd[xx+(yy*3)+1]
         ch.set(char[c][n], (x+map.rx)*3+xx+1, (y+map.ry)*3+yy+1, color[c][n])
      end
   end

   -- TODO - beaches

end


-----------------------------------------------------------------------


function map.events()
   local e = ch.wait_event()
   if e.type == 'key' then
      if e.ctrl then
         if e.key == 'up' then
            map.ry = map.ry - 1
            map.redraw = true
         elseif e.key == 'down' and map.ry < -1 then
            map.ry = map.ry + 1
            map.redraw = true
         elseif e.key == 'left' then
            map.rx = map.rx - 1
            map.redraw = true
         elseif e.key == 'right' and map.rx < -1 then
            map.rx = map.rx + 1
            map.redraw = true
         end
      else
         if e.char == 'q' then
            running = false
         end
      end
   end
   return running
end
