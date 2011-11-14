class Array

  def next(item)
    raise if not self.include? item
    return self[0] if self.last == item
    return self[self.find_index(item)+1]
  end

  def sum
    0 if self.empty?
    self.inject{|sum,x| sum + x }
  end

  def join2(*a)
    if a.length == 1 or self.length < 2
      return self.join(a[0])
    elsif a.length == 2
      return self[0..(self.length-2)].join(a[0]) + a[1] + self[-1]
    else
      raise
    end
  end

end

# code by Allan Odgaard
class String

  def wrap(col=80)
    self.to_s.gsub(/(.{1,#{col}})( +|$\n?)|(.{1,#{col}})/, "\\1\\3\n") 
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

class CocivMessage < Exception
  def initialize(message)
    super(message)
  end
end
