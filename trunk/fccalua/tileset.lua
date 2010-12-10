AbstractTileset = {

   cursor = { x = 0, y = 0 }

   print = function(layer, str, x, y)
      for i=1,str:len() do
         self.set_char(layer, str:byte(i), x, y)
         x = x+1
      end
   end

}

require 'libtileset'
