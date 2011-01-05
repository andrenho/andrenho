local function military(...)
   assert(#arg == 2, "Wrong number of arguments for military.")
   return {
      name = arg[1],
      ship = arg[2],
   }
end

--                 Name          Ship?
---------------------------------------------
SOLDIER = military('Soldier',    false)
CARAVEL = military('Caravel',    true )
