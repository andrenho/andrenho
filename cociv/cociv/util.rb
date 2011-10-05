class Array

  def next(item)
    raise if not self.include? item
    return self[0] if self.last == item
    return self[self.find_index(item)+1]
  end

end

class AssertException < Exception
  def initialize(message)
    super(message)
  end
end

def assert(message='')
  raise AssertException.new(message) unless yield
end
