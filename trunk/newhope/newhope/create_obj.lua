if #arg ~= 1 then
    print('Usage: '..arg[-1]..' '..arg[0]..' Classname')
    os.exit()
end

s = (
[[local CLASSNAME = {}
CLASSNAME.__index = CLASSNAME

function CLASSNAME:new()
  local self = setmetatable({}, CLASSNAME)
  return self
end

-------------
-- PRIVATE --
-------------

function CLASSNAME:__tostring()
  return '[CLASSNAME]'
end

function CLASSNAME:type() return 'CLASSNAME' end

return CLASSNAME

-- vim: ts=4:sw=4:sts=4:expandtab]]):gsub('CLASSNAME', arg[1])

local f = io.open(arg[1]:lower()..'.lua', 'wb')
f:write(s)
f:close()

-- vim: ts=4:sw=4:sts=4:expandtab
