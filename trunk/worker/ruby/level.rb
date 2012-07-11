$level = []
$level[0] = [
    "............",
    "1   X      .",
    ".          #",
    ".          .",
    ".          .",
    "............",
]

require 'object'
require 'structures'

class Level

    attr_reader :structures, :objects

    def initialize(n)
        raise 'Level does not exist.' if not $level[n]

        @structures = []
        $level[n].each_index do |y|
            x = 0
            $level[n][y].each_char do |c|
                case c
                when '.'
                    @structures << Wall.new(x, y)
                when '#'
                    @structures << Door.new(x, y)
                when '1'..'9'
                    @structures << Entrance.new(x, y, c.to_i, $right)
                when 'X'
                    @structures << BoxStartingPosition.new(x, y)
                when ' '
                else
                    raise "Invalid object #{c}."
                end
                x += 1
            end
        end

        reset!
    end


    def reset!
        @objects = []
    end

    
    def start!
        reset!
        @structures.each do |s|
            if s.class == Entrance
                @objects << Worker.new(s.x, s.y, s.dir)
            elsif s.class == BoxStartingPosition
                @objects << Box.new(s.x, s.y)
            end
        end
    end


    def step!
        @objects.select{ |o| o.class == Worker }.each do |w|
            #fx, fy = w.dir.next(w.x, w.y)
            w.move!
        end
    end

end
