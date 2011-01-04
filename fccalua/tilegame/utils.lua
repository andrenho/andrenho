function table.has_value(T, val)
   for _,v in pairs(T) do
      if v == val then return true end
   end
   return false
end


function table.remove_values(T, V)
   for k,v in pairs(T) do
      for _,v2 in pairs(T) do
         if v == v2 then T[k] = nil end
      end
   end
end
