require('util.strict') -- doesn't allow globals to be declared inside functions

local loaded = {}
function my_require(module)
    if loaded[module] then
        package.loaded[module] = nil
    end
    loaded[module] = true
    return require(module)
end

-- classes
Physics       = my_require('physics.physics')
PhysStaticObj = my_require('physics.physstaticobj')
Game          = my_require('game')

-- initialize game
world = nil -- TODO
physics = Physics:new()
game = Game:new(world)

-- temporary (TODO)
physics:add_object(PhysStaticObj:new(50, 50, 10, 10))

-- initialize UI
my_require('ui.lovemain')

-- vim: ts=4:sw=4:sts=4:expandtab
