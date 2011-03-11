require 'ui/config'

map = {
   rx = 1,
   ry = 1,
   redraw = true,
   gold_tax_str = (_'Gold: $%d   Tax: %d%%%%'),
   blink_frames = 30,
   blink = 0,
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

   local blink = (((map.blink / map.blink_frames) % 2) < 1)
   if map.blink % map.blink_frames == 0 then map.redraw = true end
   map.blink = map.blink + 1

   if not map.redraw then return end

   ch.clear()

   local ix = math.max(map.rx, 1)
   local iy = math.max(map.ry, 1)
   for x=ix, math.min(game.w, ix+screen_w/3) do
      for y=iy, math.min(game.h, iy+screen_h/3) do
         map.draw_tile(x, y)
         map.draw_units(x, y, blink)
         --map.draw_town(x, y)
      end
   end

   map.draw_interface()

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
         ch.set(char[c][n], (x-map.rx)*3+xx+1, (y-map.ry)*3+yy+1, color[c][n])
      end
   end

   -- TODO - beaches

end


function map.draw_interface()
   local cl = {
      frame = 'white',
      year = 'lighter_purple',
      nation = 'gold',
   }
   if not colors then
      for k,v in pairs(cl) do cl[k] = 'lightest_gray' end
   end

   -- full frame
   ch.frame(0, 0, screen_w-1, screen_h-1, cl.frame)

   -- game/nation info
   ch.frame(0, 0, (#map.gold_tax_str)+2, 3, cl.frame, true)
   ch.print((_'Year: %d B.C.'):format(math.abs(game.year)), 1, 1, cl.year)
   ch.print(map.gold_tax_str:format(game.player.gold, game.player.tax), 1, 2, cl.nation)

   -- selected unit data
   -- TODO
end


local function select_unit(units)
   for _,u in ipairs(units) do
      if u == game.player.focused then return u end
   end
   return units[1]
end


function map.draw_units(x, y, blink)
   local units = game:units_in_tile(x,y)
   local u = select_unit(units)
   if u and not (u == game.player.focused and not blink) then
      assert(unit_chars[u.military])
      ch.double_frame((x-map.rx)*3+1, (y-map.ry)*3+1, 2, 2, u.nation.color, true)
      ch.set(unit_chars[u.military], (x-map.rx)*3+2, (y-map.ry)*3+2, u.nation.color)

      local state_char
      if u.state == 'normal' then
         state_char = 'bullet_square'
      else
         assert(false, 'Invalid unit state ' .. u.state .. '.')
      end
      ch.set(state_char, (x-map.rx)*3+1, (y-map.ry)*3+1, u.nation.color)
   end
end


-----------------------------------------------------------------------


function map.events()

   local function reset()
      map.redraw = true
      map.blink = 0
   end

   local e = ch.check_event()
   if not e then return running end

   if e.type == 'key' then
      if e.ctrl then
         if e.key == 'up' and map.ry > 1 then
            map.ry = map.ry - 1
            reset()
         elseif e.key == 'down' and map.ry+(screen_h/3) < game.h+1 then
            map.ry = map.ry + 1
            reset()
         elseif e.key == 'left' and map.rx > 1 then
            map.rx = map.rx - 1
            reset()
         elseif e.key == 'right' and map.rx+(screen_w/3) < game.w+1 then
            map.rx = map.rx + 1
            reset()
         end
      else
         if e.char == 'q' then
            running = false
         end
      end
   end
   return running
end
