module CityStorage
protected
  
  def city_storage_update
    clear

    # draw goods
    s 'Goods', 1, 0, :title
    y = 3
    c = ?a
    max_good_len = Good.all.map{ |g| g.name.length }.max
    Good.all.select{ |g| g.can_buy }.each do |good|
      s c, y, 1, :key 
      s ") #{good.name}", y, 2, :text
      s ('[%3d]' % @city.warehouse[good]), y, max_good_len + 5, :text
      y += 1
      c = c.next
    end

    # draw units and their slots
    x = 30
    y = 3
    c = ?A
    s 'Units', 1, x, :title
    max_unit_len = @game[@city.x, @city.y].units.select{ |u| u.military.cargo > 0 }.map{ |u| u.military.name.length }.max
    @game[@city.x, @city.y].units.select{ |u| u.military.cargo > 0 }.each do |unit|
      s unit.military.name, y, x+3, :text
      (1..unit.military.cargo).each do |slot|
        s c, y, x, :key 
        s ')', y, x+1, :text
        s "[ ]", y, x+5+max_unit_len, :text
        y += 1
        c = c.next
      end
    end

    refresh
  end

  def city_storage_event
    ch = getch
    
    # return to units view
    if ch == '<'
      @city_view = :units

    end
  end

end
