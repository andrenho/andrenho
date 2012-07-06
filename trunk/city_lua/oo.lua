function class()

  local klass = {}
  klass.mt = { __index = klass }

  function klass.new()
      local new_inst = {}
      setmetatable( new_inst, klass.mt )
      return new_inst
  end

  return klass

end


function inheritsfrom( baseClass )

    local new_class = {}
    new_class.mt = { __index = new_class }

    function new_class.new()
        local newinst = {}
        setmetatable( newinst, new_class.mt )
        return newinst
    end

    if baseClass then
        setmetatable( new_class, { __index = baseClass } )
    end

    return new_class

end
