local string = setmetatable({}, { __index = string })

function string:wrap(columns)
   local breaking = { 10, 13 }
   local ret = {}
   local ini = 1
   self = self:gsub('\t','        ')
   for i = 1,#self do
      if table.find(breaking, self:byte(i)) or (self:byte(i) == 32 and i-ini >= columns) then
         ret[#ret+1] = self:sub(ini, i-1)
         ini = i + 1
      elseif i == #self then
         ret[#ret+1] = self:sub(ini)
      end
   end
   return ret
end

return string

-- vim: ts=3:sw=3:sts=3:expandtab
