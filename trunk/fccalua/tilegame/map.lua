require 'raw'

TileGameMap = {}
TileGameMap.__index = TileGameRaw

function TileGameMap:new(tile_w, tile_h)
   o = TileGameRaw:new(tile_w, tile_h)
   setmetatable(o, self)
   return o
end


function TileGameMap:test()
   print 'hi'
end
