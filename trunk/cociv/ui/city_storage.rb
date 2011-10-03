module CityStorage
protected
  
  #
  # draw the storage screen
  #
  def city_storage_update
    clear

    # draw goods
    s 'Goods', 1, 0, :title
    y = 3
    c = ?a
    max_good_len = Good.all.map{ |g| g.name.length }.max
    @goods = {}
    Good.all.select{ |g| g.can_buy }.each do |good|
      s c, y, 1, :key 
      s ") #{good.name}", y, 2, :text
      s ('[%3d]' % @city.warehouse[good]), y, max_good_len + 5, :text
      y += 1
      @goods[c] = good
      c = c.next
    end

    # draw units and their slots
    x = 30
    y = 3
    c = ?A
    s 'Units', 1, x, :title
    max_unit_len = @game[@city.x, @city.y].units.select{ |u| u.military.cargo > 0 }.map{ |u| u.military.name.length }.max
    @storage_units = {}
    @game[@city.x, @city.y].units.select{ |u| u.military.cargo > 0 }.each do |unit|
      s unit.military.name, y, x+3, :text
      (0..(unit.military.cargo-1)).each do |slot|
        s c, y, x, :key 
        s ')', y, x+1, :text
        s "[ ]", y, x+5+max_unit_len, :text
        y += 1
        @storage_units[c] = [unit, slot]
        c = c.next
      end
    end

    refresh
  end

  # 
  # the user pressed a key
  #
  def city_storage_event
    ch = getch
    
    # return to units view
    if ch == '<'
      @city_view = :units

    # user chose a good
    elsif @goods.has_key? ch
      load_unit(ch, @goods[ch])

    # user chose a unit slot
    elsif @storage_units.has_key? ch
      unload_unit(ch, @storage_units[ch])

    # any other key
    else
      message _('Invalid key.')

    end
  end

  #
  # load goods into a unit
  #
  def load_unit(ch, good)
    curs_set 1
    ch = message _('To which unit do you want to load? (\'-\' for a parcial load) ')
    setpos (3 + ch.ord - ?a.ord), 1
    new_ch = getch
    message ''
    curs_set 0

    if @storage_units.has_key? new_ch
      unit, slot = @storage_units[new_ch]
    else
      message _('Invalid key.')
    end
  end

  #
  # unload goods from a unit
  #
  def unload_unit(ch, *slot_unit)
  end

end
