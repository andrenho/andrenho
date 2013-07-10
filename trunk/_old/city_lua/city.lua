City = class()


function City:init()
  self.buildings = {}
  return self
end


function City:add_building(b, x, y)
  table.insert(self.buildings, { building=b, x=x, y=y })
  b.x = x
  b.y = y
end
