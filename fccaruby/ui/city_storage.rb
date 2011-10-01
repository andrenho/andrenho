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
