module CityUI

  ESC = 27

  def city_update

    @buildings, @units_outside, @tiles = {}, {}, {}

    # top display
    city = @display
    clear
    s city.name, 0, cols-city.name.length, :title

    # buildings
    @max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    y = 2
    s 'Wks  Production', y, @max_bd_len + 6, :text
    c = 'a'
    y += 1
    city.buildings.each do |building|
      s c + ') ' + building.type.name, y, 1, :text
      x = 6
      building.workers.each do |worker|
        draw_unit(worker, @max_bd_len+x, y)
        x += 1
      end
      if building.production != []
        g, p = building.production
        s Building::Messages[:production] % [p, g.name], y, @max_bd_len+11, :text
      end
      @buildings[c] = building
      c = c.next
      y += 1
    end
    
    # fence
    s '#' * (cols - 2), (lines - 5), 1, :text

    # units outside the city
    c = 'A'
    x = 2
    units = @game[city.x, city.y].units
    if not units.empty?
      s '[', (lines-3), 1, :text
      units.each do |unit|
        s c, (lines-3), x, :text
        draw_unit(unit, x, (lines-2))
        @units_outside[c] = unit
        c = c.next
        x += 1
      end
      s ']', (lines-3), x, :text
    end

    # terrain
    sy, sx = 3, @max_bd_len + 35
    s '+--+--+--+', sy, sx, :text
    sy += 1
    i = 0
    (city.y-1).upto(city.y+1) do |y|
      s '|', sy, sx, :text
      sx += 1
      (city.x-1).upto(city.x+1) do |x|
        draw_terrain(x, y, sx, sy)
        draw_terrain(x, y, sx+1, sy)
        @tiles[['7','8','9','4','5','6','1','2','3'][i]] = @game[x,y]
        i += 1
        s '|', sy, sx+2, :text
        sx += 3
      end
      sx = @max_bd_len + 35
      s '+--+--+--+', sy+1, sx, :text
      sy += 2
    end
    
    show_last_message

    curs_set 0
    refresh
  end


  def city_event
    ch = getch
    if ch == ESC
      @display = :map
    elsif @units_outside.include? ch # unit outside the fence selected
      unit = @units_outside[ch]
      transfer_unit unit, ch
    elsif @buildings.include? ch # unit in a building
      if @buildings[ch].workers.length > 0
        transfer_unit @buildings[ch].workers[0], ch
      end
    end
  end


  def transfer_unit(unit, ch=nil)
    
    message City::Messages[:move_to] % unit.description

    # set cursor
    curs_set 1
    if @units_outside.include? ch
      setpos (lines-2), (ch.ord - 'A'.ord + 2) if ch
    elsif @buildings.include? ch
      setpos (ch.ord - 'a'.ord + 3), (@max_bd_len+6)
    end

    # get key
    to = getch
    if @buildings.include? to
      if @buildings[to].workers.include? unit # select next unit
        unit = @buildings[to].workers.next(unit)
        transfer_unit unit, ch
      elsif not @buildings[to].add_worker(unit) # put unit on building
        max = @buildings[to].type.max_units
        if max == 0
          message Building::Messages[:no_workers]
        else
          message Building::Messages[:too_many_workers] % max
        end
      else
        @last_message = nil
      end
    elsif to != ESC
      message _('Invalid key.')
    end
  end

end
