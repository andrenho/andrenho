-- 
-- Translation
--
function _(s)
   return s
end

--
-- Helper functions
-- 

-- ordered next
function inext(T, i)
   if i == nil then return T[1] end
   idx = -1
   for k,v in ipairs(T) do
      if v == i then idx = k end
   end
   if idx == -1 then error 'Key not found' end
   return T[idx+1]
end

-- circular next
function cnext(T, i)
   idx = -1
   for k,v in ipairs(T) do
      if v == i then idx = k end
   end
   if T[idx+1] then
      return T[idx+1]
   else
      return T[1]
   end
end
   

--
-- Serialization
--
function global_name(value)
   for k,v in pairs(_G) do
      if v == value then
         return k
      end
   end
   return nil
end

function basicSerialize(o)
   if type(o) == 'string' then
      return string.format("%q", o)
   else    -- assume it is a string
      return tostring(o)
   end
end

function dump(name, value, saved)
   function has_value(T, val)
      for _,v in ipairs(T) do
         if v == val then
            return true
         end
      end
      return false
   end

   saved = saved or {}
   if type(value) == 'function' then return end
      io.write(name, ' = ')
   if type(value) == "number" or type(value) == "string" 
   or type(value) == "boolean" then
      io.write(basicSerialize(value), "\n")
   elseif type(value) == 'string' then
      io.write(string.format('%q', value))
   elseif type(value) == 'table' then
      if saved[value] then
         io.write(saved[value], '\n')
      elseif has_value(static, value) then
         io.write(global_name(value) .. '\n')
      else
         saved[value] = name
         if value.dump_create then
            io.write(value.dump_create() .. '\n')
         else
            io.write('{}\n')
         end
         for k,v in pairs(value) do
            local fieldname = string.format('%s[%s]', name,
                                                            basicSerialize(k))
            dump(fieldname, v, saved)
         end
      end
   else
      error('cannot save a ' .. type(value))
   end
end
