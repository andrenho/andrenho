function table.select(T, func)
   assert(type(T) == "table")
   local N = {}
   for k,v in pairs(T) do
      if func(v) then table.insert(N, T[k]) end
   end
   return N
end

function table.find_key(T, val)
   assert(type(T) == "table")
   for k,v in pairs(T) do
      if v == val then return k end
   end
   return nil
end
