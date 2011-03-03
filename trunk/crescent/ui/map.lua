map = {}

function map.draw()
end

function map.events()
   e = ch.wait_event()
   if e.type == 'key' then
      if e.char == 'q' then
         running = false
      end
   end
end
