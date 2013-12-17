local loaded = {}
function my_require(module)
    if loaded[module] then
        package.loaded[module] = nil
    end
    loaded[module] = true
    return require(module)
end

ui = my_require('ui.lovemain')

-- physics
PersonPhysics = my_require('physics.personphysics')

-- vim: ts=4:sw=4:sts=4:expandtab
