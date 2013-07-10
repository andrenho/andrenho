local function military(...)
   assert(#arg == 3, "Wrong number of arguments for military.")
   return {
      name = arg[1],
      ship = arg[2],
      moves = arg[3],
   }
end

--                 Name          Ship?  Moves
---------------------------------------------
SOLDIER = military('Soldier',    false, 4)
CARAVEL = military('Caravel',    true , 2)
