require 'curses'

class UICurses

    include Curses

    attr_accessor :running, :level

    def initialize
        @running = false
        @y = @x = 0
        init_curses
    end


    def draw!
        raise if not @level

        clear

        @level.structures.each do |s|
            setpos s.y, s.x
            if s.class == Wall
                addch '.'
            elsif s.class == Door
                addch '#'
            elsif s.class == Entrance
                addch s.n.to_s if not @running
            elsif s.class == BoxStartingPosition
                addch 'X' if not @running
            end
        end

        if @running
            @level.objects.each do |o|
                setpos o.y, o.x
                if o.class == Worker
                    addch '@'
                elsif o.class == Box
                    addch 'X'
                end
            end
        end

        setpos @y, @x
        refresh
    end


    def step!
        getch
        @level.step!
    end


    def edit!
        case getch
        when Curses::Key::UP
            @y -= 1 unless @y == 0
            setpos @y, @x
        when Curses::Key::DOWN
            @y += 1 unless @y == (lines-1)
            setpos @y, @x
        when Curses::Key::LEFT
            @x -= 1 unless @x == 0
            setpos @y, @x
        when Curses::Key::RIGHT
            @x += 1 unless @x == (cols-1)
            setpos @y, @x
        when ?s
            @level.start!
            @running = true
        when ?q
            exit 0
        end
    end


private


    def init_curses
        begin
            Curses.ESCDELAY = 1
        rescue NotImplementedError
            ENV['ESCDELAY'] = '1'
        end
        init_screen
        raw
        cbreak
        noecho
        stdscr.keypad = 1
        if has_colors?
            start_color
            use_default_colors
        end
        curs_set 2
        setpos @y, @x
    end

end
