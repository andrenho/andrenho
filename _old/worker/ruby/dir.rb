class Direction

    def initialize(mx, my)
        @mx, @my = mx, my
    end

    def next(x, y)
        return [x+@mx, y+@my]
    end

end

$up = Direction.new(0, -1)
$down = Direction.new(0, 1)
$left = Direction.new(-1, 0)
$right = Direction.new(1, 0)
