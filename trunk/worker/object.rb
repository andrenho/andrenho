class LevelObject

    attr_reader :x, :y

    def initialize(x, y)
        @x, @y = x, y
    end

end


class Worker < LevelObject

    attr_reader :dir

    def initialize(x, y, dir)
        super(x, y)
        @dir = dir
    end

end


class Box < LevelObject
end

