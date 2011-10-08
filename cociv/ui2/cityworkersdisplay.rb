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

    # calculate production
    pr = @city.production

    # box
    @scr.box 0, 0, @scr.w-1, @scr.h-2
    @scr.print (@scr.w/2 - @city.name.length/2), 0, '<title> '+@city.name+' '

    # buildings
    @scr.puts 1, 1, '<title>'+_('Buildings')
    max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    @scr.puts max_bd_len+8, 2, "#{_('Wks')}  #{_('Production')}"
    c = ?a
    @city.buildings.each do |building|
      # name
      @scr.x = 2
      @scr.print "<key>#{c}<default> - #{building.type.name}"
      
      # workers
      (0..(building.type.max_units-1)).each do |i|
        @scr.x = max_bd_len + 8 + i
        if building.workers[i]
          @scr.print "[unit #{building.workers[i].hash}]"
        else
          @scr.print '.'
        end
      end
      
      # production
      @scr.x = max_bd_len + 11
      good = building.type.good
      if good and pr[good].theorical > 0
        @scr.print "#{pr[good].theorical} #{good.name} [<surplus>#{pr[good].surplus}/<lacking}#{pr[good].lacking}]"
      end

      @scr.puts
      c = c.next
    end

    # farms
    x = @scr.w-32
    y = 4
    @scr.puts x, 1, '<title>'+_('Farms')
    @scr.puts x, 3, '<key>  7   8   9'
    @scr.puts x-1, 7, '<key>4             6'
    @scr.puts x, 11, '<key>  1   2   3'
    @scr.box x+4, y, 4, 6
    @scr.box x, y+2, 12, 2
    @scr.box x, y, 12, 6
    @scr.box x+4, y+2, 4, 2
      
    # outside the colony
    @scr.print 1, @scr.h-3, _('Outside: ')
    x = @scr.x; y = @scr.y
    c = ?A
    @scr.print x-1, y-1, '['
    @game[@city.x,@city.y].units.select{ |u| not u.is_worker? }.each do |unit|
      @scr.print x, y-1, "<key>#{c}"
      @scr.print x, y, "[unit #{unit.hash}]"
      x += 1; c = c.next
    end
    @scr.print @scr.x, @scr.y-1, ']'

  end

end
