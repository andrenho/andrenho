Building = class()


function Building:init(w, h)
  self.w = w
  self.h = h
  return self
end


function Building:temp()
  print('b')
end


function Building:__tostring()
  return 'ha'
end


Farm = inheritsfrom(Building)
