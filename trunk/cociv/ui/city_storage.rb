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
        if unit.slots[slot].amount > 0
          s '[ %d %s ]' % [unit.slots[slot].amount, unit.slots[slot].good.name], y, x+5+max_unit_len, :text
        else
          s '[ ]', y, x+5+max_unit_len, :text
        end
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
    amt = 0
    max_amt = @city.warehouse[good] > 100 ? 100 : @city.warehouse[good]
    unload_all = ask_yn(_('Do you want to load %d t of %s?') % [max_amt, good.name])
    if not unload_all
      amt = ask_s_(_('How much do you want to unload?')).to_i
      if amt < 1 or amt > 100
        message _('Invalid amount')
      else
        amt = max_amt
      end
    end

    new_ch = ask_c(_('Which unit do you want to load?'))
    if @storage_units.has_key? new_ch
      unit, slot = @storage_units[new_ch]
      unit.load(good, amt)
      message Cargo::Messages[:loaded] % [amt, good.name]
    else
      message _('Invalid key.')
    end
  end

  #
  # unload goods from a unit
  #
  def unload_unit(ch, *slot_unit)
    unit, n_slot = slot_unit
    slot = unit.slots[n_slot]
    unload_all = ask_yn(_('Do you want to unload all the %d t of %s?') % [slot.amount, slot.good.name])
    begin
      if unload_all
        unit.unload(slot.good, slot.amount)
      else
        amt = ask_s_(_('How much do you want to unload?')).to_i
        if amt < 1 or amt > 100
          message _('Invalid amount')
        else
          unit.unload(slot.good, amt)
        end
      end
    rescue
      # TODO
    end
  end

end
