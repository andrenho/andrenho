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

function string.wrap(str, limit, indent, indent1)
  indent = indent or ""
  indent1 = indent1 or indent
  limit = limit or 72
  local here = 1-#indent1
  return indent1..str:gsub("(%s+)()(%S+)()",
                          function(sp, st, word, fi)
                            if fi-here > limit then
                              here = st - #indent
                              return "\n"..indent..word
                            end
                          end)
end

function string:split(sep)
   local sep, fields = sep or ":", {}
   local pattern = string.format("([^%s]+)", sep)
   self:gsub(pattern, function(c) fields[#fields+1] = c end)
   return fields
end

function clone(t)            -- return a copy of the table t
  local new = {}             -- create a new table
  local i, v = next(t, nil)  -- i is an index of t, v = t[i]
  while i do
    new[i] = v
    i, v = next(t, i)        -- get next index
  end
  return new
end

function table.shallow_compare(t1, t2)
   for k,v in pairs(t1) do
      if t1[k] ~= t2[k] then return false end
   end
   for k,v in pairs(t2) do
      if t1[k] ~= t2[k] then return false end
   end
   return true
end

function dump(value, indent)
   local idt = indent or 0
   for i=1,idt do io.write('\t') end
   if value == nil then
      io.write('nil')
   elseif value == true then
      io.write('true')
   elseif value == false then
      io.write('false')
   elseif type(value) == 'table' then
      print('{')
      for k,v in pairs(value) do
         io.write('\t')
         if type(k) == 'string' then
            io.write(k)
         else
            io.write('[')
            dump(k, 0)
            io.write(']')
         end
         io.write(' = ')
         dump(v, 0)
         print(',')
      end
      for i=1,idt do io.write('\t') end
      io.write('}')
   elseif type(value) == 'string' then
      io.write("'" .. value .. "'")
   elseif type(value) == 'function' then
      io.write('function()')
   else
      io.write(value)
   end
   if not indent then print() end
end
