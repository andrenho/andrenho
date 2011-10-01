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
    s city.name, lines-1, cols-city.name.length, :title

    # buildings
    prod = @city.production
    s 'Buildings', 1, 0, :title
    @max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    y = 2
    s 'Wks  Production', y, @max_bd_len + 6, :text
    c = 'a'
    y += 1
    city.buildings.each do |building|
      if building.type.max_units > 0
        s c, y, 1, :key 
        s ')', y, 2, :text
      end
      s building.type.name, y, 4, :text
      x = 6
      s ('.' * building.type.max_units), y, @max_bd_len+x, :discrete
      building.workers.each do |worker|
        draw_unit(worker, @max_bd_len+x, y)
        x += 1
      end
      p = prod[building.type.good]
      if not building.workers.empty?
        ss = "#{building.type.good.name} [#{p.theorical}|"
        x = @max_bd_len+11
        s ss, y, x, :text
        x += ss.length
        s p.lacking.to_s, y, x, :lacking
        x += p.lacking.to_s.length
        s '|', y, x, :text
        s p.surplus.to_s, y, x+1, :surplus
        s ']', y, x+1+p.surplus.to_s.length, :text
      end
      @buildings[c] = building
      c = c.next
      y += 1
    end

    # under construction
    s City::Messages[:under_construction], y+1, 1, :text
    uc = @city.under_construction
    if 
      t = uc.name
    else
      t = City::Messages[:nothing]
    end
    s t, y+2, 4, :status_txt
    s '(', y+2, t.length+5, :text
    s '%', y+2, t.length+6, :key
    s ") [#{@city.hammers}/#{uc ? uc.cost : 0}]", y+2, t.length+7, :text


    # Raw goods production
    y = 13
    s 'Raw material production', y, 47, :title
    y += 2
    Good.all.select{ |g| g.raw }.each do |good|
      p = prod[good]
      if p.theorical > 0
        ss = "#{good.name} [#{p.theorical}|"
        x = @max_bd_len+35
        s ss, y, x, :text
        x += ss.length
        s p.lacking.to_s, y, x, :lacking
        x += p.lacking.to_s.length
        s '|', y, x, :text
        s p.surplus.to_s, y, x+1, :surplus
        s ']', y, x+1+p.surplus.to_s.length, :text
        y += 1
      end
    end
    
    # fence
    s '-' * (cols - 30), (lines - 3), 1, :text

    # units outside the city
    c = 'A'
    x = 2
    units = @game[city.x, city.y].units
    if not units.empty?
      s '[', (lines-2), 1, :text
      units.each do |unit|
        s c, (lines-2), x, :key
        draw_unit(unit, x, (lines-1))
        @units_outside[c] = unit
        c = c.next
        x += 1
      end
      s ']', (lines-2), x, :text
    end

    # terrain
    sy, sx = 4, @max_bd_len + 30
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
    sy = 2
    s 'Production', sy, sx+3, :text
    sy += 2
    (1..9).each do |n|
      fx, fy = DIRECTIONS_C[n]
      d = false
      @game[@city.x+fx,@city.y+fy].production.each do |production|
        if not d
          s "#{n}.", sy, sx, :text
          d = true
        end
        if production != []
          s "#{production[0].name} [#{production[1]}]", sy, sx+3, :text
          sy += 1
        end
      end
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

    # leave city view
    if ch == ESC 
      @display = :map

    # unit outside the fence selected
    elsif @units_outside.include? ch
      unit = @units_outside[ch]
      transfer_unit unit, ch

    # unit in a building
    elsif @buildings.include? ch
      if @buildings[ch].workers.length > 0
        transfer_unit @buildings[ch].workers[0], ch
      end

    # tile selected
    elsif [1,2,3,4,6,7,8,9].include? ch.to_i
      fx, fy = DIRECTIONS[ch.to_i]
      tile = @game[@city.x+fx, @city.y+fy]
      if tile.worker
        transfer_unit tile.worker, ch
      end

    # change building under construction
    elsif ch == '%'
      o = []
      @city.buildable.each { |bt| o << [bt, bt.name] }
      build = menu(City::Messages[:to_build], o)
      @city.under_construction = build if build
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
      setpos (ch.ord - 'a'.ord + 3), (@max_bd_len+6+(@buildings[ch].workers.find_index(unit)))
    elsif [1,2,3,4,6,7,8,9].include? ch.to_i
      sy, sx = 7, @max_bd_len + 34
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
    elsif [1,2,3,4,6,7,8,9].include? to.to_i
      fx, fy = DIRECTIONS[to.to_i]
      @game[@city.x+fx,@city.y+fy].worker = unit
      message ''

    # remove unit from city
    elsif to == '-'
      unit.abandon_job!
      message ''

    # change unit job
    elsif unit.working_on.is_a? Tile and to == 'p'
      production = @game[@city.x+fx,@city.y+fy].productivity_jobs(unit)
      options = []
      Job.all.select{ |j| j.raw }.each do |job|
        options << [job, "#{job.name} (#{production[job] or 0} lds)"]
      end
      job = menu(Tile::Messages[:produce] % unit.description, options)
      if job
        unit.job = job
      else
        message _('Invalid key.')
      end

    # nothing
    elsif to == ESC
      message ''

    # any other key
    else
      message _('Invalid key.')
    end
  end

end
