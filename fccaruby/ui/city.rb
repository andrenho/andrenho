module CityUI

  def city_update

    # top display
    city = @display
    clear
    s city.name + (' ' * (cols - city.name.length)), 0, 0, :title

    # buildings
    max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    y = 2
    s 'Wks  Production', y, max_bd_len + 6, :text
    c = 'a'
    y += 1
    city.buildings.each do |building|
      s c + ') ' + building.type.name, y, 1, :text
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
        c = c.next
        x += 1
      end
      s ']', (lines-3), x, :text
    end

    # terrain
    sy, sx = 3, max_bd_len + 35
    (city.x-1).upto(city.x+1) do |x|
      (city.y-1).upto(city.y+1) do |y|
        draw_terrain(x, y, sx, sy)
        sy += 1
      end
      sy = 3
      sx += 1
    end

    refresh
  end

  def city_event
  end

end
