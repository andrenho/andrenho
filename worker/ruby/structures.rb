require 'dir'

class Structure

    attr_reader :x, :y

    def initialize(x, y)
        @x, @y = x, y
        raise if self.class == Structure # abstract
    end

end


class Door < Structure
end


class Entrance < Structure

    attr_reader :n, :dir

    def initialize(x, y, n, dir)
        super(x, y)
        @n = n
        @dir = dir
    end

end


class Wall < Structure
end


class BoxStartingPosition < Structure
end

