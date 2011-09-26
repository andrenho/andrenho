module Map

protected

  # 
  # update the map image on the screen
  #
  def map_update
    clear
    y = 1
    s @game.player.name, y, 0, :info
    y += 1
    s 'GOLD', y, 0, :status_txt
    s "#{@game.player.gold}", y, 15, :status_val, :right
    y += 1
    s 'YEAR', y, 0, :status_txt
    s "#{@game.year.abs} BC", y, 15, :status_val, :right
    y += 2
    if @driver.focused
      u = @driver.focused
      s u.tile.terrain.name, y, 0, :info
      y += 2
      s u.military.name, y, 0, :info
      y += 1
      s 'MOVES', y, 0, :status_txt
      s u.moves_left.to_s, y, 15, :status_val, :right
    end
    
    map_draw
  end


  def draw_unit(unit, sx, sy)
    s $chars[unit.military][0], sy, sx, $nations[unit.nation.color]
  end


  def draw_terrain(x, y, sx, sy, draw_worker=false, draw_city=true)
    if draw_worker and @game[x,y].worker
      draw_unit(@game[x,y].worker, sx, sy)
    else
      city_here = @game[x,y].city
      if city_here and draw_city
        s $chars[:city][0], sy, sx, $nations[city_here.nation.color]
      else
        c = $chars[@game[x,y].terrain]
        s c[0], sy, sx, c[1] if c
      end
    end
  end


  # 
  # draw map on the screen (called by UI#map_update)
  #
  def map_draw
    fx, fy = nil, nil
    (0..(@game.map_w-1)).each do |x|
      (0..(@game.map_h-1)).each do |y|
        u = @game[x,y].units
        sx, sy = x+16, y+1
        if not u.empty?
          unit = u[0]
          draw_unit(unit, sx, sy)
          fx, fy = sx, sy if u.include? @driver.focused
        else
          draw_terrain(x, y, sx, sy)
        end
      end
    end
    if fx # focused unit appears on screen
      curs_set 1
      setpos fy, fx
    else
      curs_set 0
    end
    refresh
  end

  # 
  # catch a event from the user
  #
  def map_event
    ch = getch
    case ch
    when '1', '2', '3', '4', '6', '7', '8', '9'
      @driver.move_unit(ch.to_i)
    when KEY_UP
      @driver.move_unit(8)
    when KEY_DOWN
      @driver.move_unit(2)
    when KEY_LEFT
      @driver.move_unit(4)
    when KEY_RIGHT
      @driver.move_unit(6)
    when 'w'
      @driver.select_next!
    when ' '
      @game.advance_round!
    when 'b'
      if @driver.focused.is_a? LandUnit and @driver.focused.tile.can_build_city?
        name = ask_s(City::Messages[:new_city])
        if name
          city = @driver.focused.build_city(name)
          @display = city
        end
      end
    when 'q'
      exit
    else
      p keyname(ch)
    end
  end

end
