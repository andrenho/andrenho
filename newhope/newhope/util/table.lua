local table = setmetatable({}, { __index = table })

function table:find(el)
  for k,v in pairs(self) do
    if v == el then return k end
  end
  return nil
end

function table:shallow_copy()
  local t2 = {}
  for k,v in pairs(self) do
    t2[k] = v
  end
  return t2
end

return table

-- vim: ts=2:sw=2:sts=2:expandtab
