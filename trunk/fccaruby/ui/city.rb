module CityUI

  ESC = 27

  # 
  # update city screen
  #
  def city_update

    @buildings, @units_outside, @tiles = {}, {}, {}

    # top display
    city = @city = @display
    clear
    s city.name, 0, cols-city.name.length, :title

    # buildings
    s 'Buildings', 2, 0, :title
    @max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    y = 3
    s 'Wks  Production', y, @max_bd_len + 6, :text
    c = 'a'
    y += 1
    city.buildings.each do |building|
      s c, y, 1, :key
      s ') ' + building.type.name, y, 2, :text
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
    s '#' * (cols - 30), (lines - 5), 1, :text

    # units outside the city
    c = 'A'
    x = 2
    units = @game[city.x, city.y].units
    if not units.empty?
      s '[', (lines-3), 1, :text
      units.each do |unit|
        s c, (lines-3), x, :key
        draw_unit(unit, x, (lines-2))
        @units_outside[c] = unit
        c = c.next
        x += 1
      end
      s ']', (lines-3), x, :text
    end

    # terrain
    sy, sx = 5, @max_bd_len + 30
    s 'Plantations', sy-3, sx-2, :title
    s ' 7  8  9', sy-1, sx, :key
    s '.--------.', sy, sx, :text
    sy += 1
    i = 0
    (city.y-1).upto(city.y+1) do |y|
      s '|', sy, sx, :text
      sx += 1
      (city.x-1).upto(city.x+1) do |x|
        draw_terrain(x, y, sx, sy, true)
        draw_terrain(x, y, sx+1, sy, false, false)
        @tiles[['7','8','9','4','5','6','1','2','3'][i]] = @game[x,y]
        i += 1
        s '|', sy, sx+2, :text
        sx += 3
      end
      sx = @max_bd_len + 30
      s '|--+--+--|', sy+1, sx, :text
      s ' 1  2  3', sy+2, sx, :key
      sy += 2
    end
    s "'--------'", sy-1, sx, :text
    s '4', sy-4, sx-2, :key
    s '6', sy-4, sx+11, :key

    # terrain production
    sx += 13
    sy = 4
    s 'Production', sy, sx+3, :text
    (1..9).each do |n|
      next if n == 5
      sy += 1
      s n.to_s + '.', sy, sx, :text
    end
    
    show_last_message

    curs_set 0
    refresh
  end


  #
  # when the user presses a key
  #
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
    elsif [1,2,3,4,6,7,8,9].include? ch.to_i
      fx, fy = DIRECTIONS[ch.to_i]
      tile = @game[@city.x+fx, @city.y+fy]
      if tile.worker
        transfer_unit tile.worker, ch
      end
    end
  end


  # 
  # change a unit from one place to the other
  #
  def transfer_unit(unit, ch=nil)
    
    # display message
    message City::Messages[:move_to] % unit.description

    # set cursor
    curs_set 1
    if @units_outside.include? ch
      setpos (lines-2), (ch.ord - 'A'.ord + 2) if ch
    elsif @buildings.include? ch
      setpos (ch.ord - 'a'.ord + 3), (@max_bd_len+6)
    elsif '12346789'.include? ch
      sy, sx = 6, @max_bd_len + 39
      fx, fy = DIRECTIONS[ch.to_i]
      setpos sy + (fy*2), sx + (fx*3)
    end

    # get key
    to = getch
    if @buildings.include? to

      # unit in building, select next unit
      if @buildings[to].workers.include? unit
        unit = @buildings[to].workers.next(unit)
        transfer_unit unit, ch

      # put unit on building
      elsif not @buildings[to].add_worker(unit)
        max = @buildings[to].type.max_units
        if max == 0
          message Building::Messages[:no_workers]
        else
          message Building::Messages[:too_many_workers] % max
        end
  
      else
        @last_message = nil
      end

    # put unit on a tile
    elsif '12346789'.include? to
      fx, fy = DIRECTIONS[to.to_i]
      @game[@city.x+fx,@city.y+fy].worker = unit
      message ''

    # remove unit from city
    elsif to == '-'
      unit.abandon_job!
      message ''

    elsif to == ESC
      message ''

    else
      message _('Invalid key.')
    end
  end

end
