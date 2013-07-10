function voxel(v)
   
   local function setpx(sf, x, y, color)
      local p = (y * sf.pitch) + (x * sf.format.BytesPerPixel)
      for i=1,3 do
         sf.pixels:set(p+i-1, color[4-i])
      end
   end

   assert(v and v.map)
   local w = #v.map
   assert(w > 0)
   local h = #v.map[1]
   assert(h > 0)
   local inclination = v.inclination or 0
   local sf = assert(SDL.CreateRGBSurface(SDL.SWSURFACE, w+inclination+50, h+100, 32))
   sf:FillRect(nil, sf.format:MapRGB(255,255,255))

   for y=1,h do
      for x=1,w do
         local px = x+20 + math.floor(y / inclination)
         local py = y+40
         for i=v.map[x][y].h,1,-1 do
            setpx(sf, px, py+i, assert(v.map[x][y].middle))
         end
         setpx(sf, px, py, assert(v.map[x][y].top))
      end
   end

   return sf
end
