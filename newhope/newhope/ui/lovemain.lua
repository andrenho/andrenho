local game = nil

function love.load()
end

function love.update(dt)
end

function love.draw()
   love.graphics.setColor(72, 160, 14)
   love.graphics.polygon('fill', phys.objects[1].body:getWorldPoints(
      phys.objects[1].shape:getPoints()))
end

function love.mousepressed(x, y, button)
end

function love.mousereleased(x, y, button)
end

function love.keypressed(key, unicode)
end

function love.keyreleased(key, unicode)
end

function love.focus(f)
end

function love.quit()
end

-- vim: ts=3:sw=3:sts=3:expandtab
