class Position

  attr_accessor :x, :y, :w, :h

  def initialize(x=nil, y=nil, w=nil, h=nil)
    @x, @y, @w, @h = x, y, w, h
  end

  def x2
    return @x + @w
  end

  def y2
    return @y + @h
  end

  def inside?(xx, yy)
    return (xx >= @x and xx < x2 and yy >= @y and yy < y2)
  end

  alias :x1 :x
  alias :y1 :y

end
