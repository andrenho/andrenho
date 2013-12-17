require('util.strict') -- doesn't allow globals to be declared inside functions

local loaded = {}
function my_require(module)
   if loaded[module] then
      package.loaded[module] = nil
   end
   loaded[module] = true
   return require(module)
end

-- modules
physics = my_require('physics')

-- classes
Game = my_require('game')

-- initialize game
world = nil -- TODO
phys = physics.Physics:new()
game = Game:new(world)

-- temporary (TODO)
phys:add_object(physics.PhysStaticObj:new(50, 50, 10, 10))

-- initialize UI
my_require('ui.lovemain')

-- vim: ts=3:sw=3:sts=3:expandtab
