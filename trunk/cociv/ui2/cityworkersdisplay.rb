require 'display'

class CityWorkersDisplay < Display

  def initialize(driver, city, scr)
    super(driver, scr)
    @city = city
  end

  def key_list
    {
    }
  end

  def redraw
    super
    @scr.clear

    # These variables are used to store the position of things. Each key (letter)
    # stores a triple: [thing, x, y]
    @buildings = {}
    @outdoor_workers = {}
    @units_outside = {}

    # calculate production
    pr = @city.production

    # box
    @scr.box 0, 0, @scr.w-1, @scr.h-2
    @scr.print (@scr.w/2 - @city.name.length/2), 0, '<title> '+@city.name+' '

    # buildings
    @scr.puts 1, 1, '<title>'+_('Buildings')
    max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    @scr.puts max_bd_len+7, 2, "#{_('Wks')}  #{_('Production')}"
    c = ?a
    @city.buildings.each do |building|
      # name
      @scr.x = 2
      @buildings[c] = [building, max_bd_len+7, @scr.y]
      @scr.print "<key>#{c}<default> - #{building.type.name}"
      
      # workers
      (0..(building.type.max_units-1)).each do |i|
        @scr.x = max_bd_len + 7 + i
        if building.workers[i]
          @scr.print "[unit #{building.workers[i].hash}]"
        else
          @scr.print '.'
        end
      end
      
      # production
      @scr.x = max_bd_len + 12
      good = building.type.good
      if good and pr[good].theorical > 0
        @scr.print "#{pr[good].theorical} #{good.name} [<surplus>#{pr[good].surplus}/<lacking>#{pr[good].lacking}<default>]"
      end

      @scr.puts
      c = c.next
    end

    # outdoors
    x = @scr.w-32
    y = 4
    @scr.puts x, 1, '<title>'+_('Farms')
    @scr.puts x, 3, '<key> 7  8  9'
    @scr.puts x-1, 7, '<key>4          6'
    @scr.puts x, 11, '<key> 1  2  3'
    @scr.box x+3, y, 3, 6
    @scr.box x, y+2, 9, 2
    @scr.box x, y, 9, 6
    @scr.box x+3, y+2, 3, 2
    (-1..1).each do |px|
      (-1..1).each do |py|
        tx, ty = @city.x + px, @city.y + py
        @scr.x, @scr.y = (x+1+((px+1)*3)), (y+1+((py+1)*2))
        @outdoor_workers[DIRECTIONS_C.key([px,py]).to_s] = [@game[tx,ty], @scr.x, @scr.y]
        if [px,py] == [0,0]
          @scr.print "[city #{@city.hash}]"
        elsif @game[tx,ty].worker
          @scr.print "[unit #{@game[tx,ty].worker.hash}]"
        else
          @scr.print "[terrain #{tx} #{ty}]"
        end
        @scr.print "[terrain #{tx} #{ty}]"
      end
    end
      
    # outside the colony
    @scr.print 1, @scr.h-3, _('Outside: ')
    x = @scr.x; y = @scr.y
    c = ?A
    units_outside = @game[@city.x,@city.y].units.select{ |u| not u.worker? and u.military.work_in_colony }
    @scr.print x-1, y-1, '[' if not units_outside.empty?
    units_outside.each do |unit|
      @units_outside[c] = [unit, x, y]
      @scr.print x, y-1, "<key>#{c}"
      @scr.print x, y, "[unit #{unit.hash}]"
      x += 1; c = c.next
    end
    @scr.print @scr.x, y-1, ']' if not units_outside.empty?

    @scr.show_cursor = false
    @scr.refresh
  end

protected ################################

  #
  # One of the buildings or units was chosen
  #
  def input_other(ch, n=0)
    # discover what the user chose
    choice = (@buildings[ch] or @outdoor_workers[ch] or @units_outside[ch])
    if choice
      # find unit
      unit = choice[0] 
      unit = choice[0].workers[n] if choice[0].is_a? Building
      unit = choice[0].worker if choice[0].is_a? Tile
      if unit
        # display help
        show_help_move_unit(unit)
        # move focus
        @scr.x, @scr.y = choice[1]+n, choice[2]
        @scr.show_cursor = true

        # get new char
        nch = @scr.getch
        message '' ; @scr.show_cursor = false
        if nch == 27 # ESC
          return nil
        elsif nch == '-' and unit.worker?
          unit.abandon_job!
        elsif nch == '/' and unit.working_on.is_a? Tile
          change_job
        else
          nchoice = (@buildings[nch] or @outdoor_workers[nch])
          if nchoice
            if choice[0].is_a? Building and choice[0] == nchoice[0]
              # next unit on building
              input_other(ch, n+1)
            else
              move_unit(unit, nchoice[0]) if nchoice
            end
          end
        end

      end
    end
    nil
  end

  
  # Return to map screen
  def input_esc
    return MapDisplay.new(@driver, @scr)
  end


private ##################################

  def show_help_move_unit(unit)
    message _('Where do you want to move the unit to?')
    help = ''
    if unit.worker?
      help = '<key>-<default>: ' + _('Leave city')
      if unit.working_on.is_a? Tile
        help += '   <key>/<default>: ' + _('Change job')
      end
    end
    @scr.print 1, @scr.h-1, help
  end

  
  def change_job
    # TODO
  end


  def move_unit(unit, to)
    begin
      if to.is_a? Building
        to.employ(unit)
      elsif to.is_a? Tile
        to.worker = unit
      end
    rescue CocivMessage => e
      # TODO
      close_screen
      puts e.message
      exit 1
    end
  end

end
