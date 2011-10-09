require 'display'
require 'cityworkersdisplay'

class CityGoodsDisplay < Display

  def initialize(driver, city, scr)
    super(driver, scr)
    @city = city
  end

  def redraw
    super
    @scr.clear
    @scr.refresh

    # These variables are used to store the position of things. Each key (letter)
    # stores a triple: [thing, x, y, slot?]
    @goods = {}
    @units_store = {}

    # box
    @scr.box 0, 0, @scr.w-1, @scr.h-2
    s = "<title> #{@city.name} - #{_('Goods Management')} "
    @scr.print (@scr.w/2 - s.length/2), 0, s
    @scr.print @scr.w-1, @scr.h-3, "<right><gold>$#{@game.player.gold}"

    # goods available
    @scr.print 1, 1, '<title>' + _('Goods in the city')
    @scr.x = 2
    @scr.y = 3
    c = ?a
    Good.all.select{ |g| g.can_buy }.each do |good|
      @goods[c] = [good, @scr.x, @scr.y]
      @scr.puts "<key>#{c})<default> [#{'%3d' % @city.warehouse[good]}] #{good.name}"
      c.next!
    end

    # units available
    x = 40
    @scr.print x, 1, '<title>' + _('Units here')
    @scr.x = x
    @scr.y = 3
    c = ?A
    @game[@city.x,@city.y].units.select{ |u| u.military.cargo > 0 }.each do |unit|
      ub = true
      (0..(unit.military.cargo - 1)).each do |n|
        @units_store[c] = [unit, x, @scr.y, n]
        @scr.print x, @scr.y, "<key>#{c}) #{ub ? "[unit #{unit.hash}]" : ' '} "
        if unit.slots[n].amount > 0
          @scr.puts "[#{'%3d' % unit.slots[n].amount}] #{unit.slots[n].good.name}"
        else
          @scr.puts "[   ]"
        end
        ub = false if ub
        c.next!
      end
    end
  end

protected #################################

  def key_list
    {
      '@' => _('Manage city workers'),
    }
  end

  def input_other(ch)
    return CityWorkersDisplay.new(@driver, @city, @scr) if ch == '@'

    choice = (@goods[ch] or @units_store[ch])
    if choice
      @scr.show_cursor = true
      if choice[0].is_a? Good
        load_unit(choice[0], choice[1], choice[2])
      else
        unload_unit(choice[0], choice[3])
      end
      @scr.show_cursor = false
      return nil
    else
      invalid_key
    end
  end

private ###################################

  # 
  # Load goods from the city into the unit.
  #
  def load_unit(good, x=0, y=0, amt=-1)
    return if @city.warehouse[good] == 0

    message _('Where do you want to move these goods to?')
    @scr.print 1, @scr.h-1, '<key>#<default>: ' + _('Move a specific amount of goods')
    @scr.refresh

    # get new char
    @scr.x, @scr.y = x, y
    nch = @scr.getch
      
    # ask amount to the user
    if nch == '#'
      amt = ask_s _('How much of this good do you want to move?')
      amt = amt.to_i
      if amt < 1 or amt > 100
        message 'Invalid amount.'
        @scr.show_cursor = false
        return
      else
        load_unit(good, x, y, amt)
      end
    end

    # ask destination
    message '' ; @scr.show_cursor = false
    nchoice = @units_store[nch]
    if nchoice
      # move goods
      begin
        unit = nchoice[0]
        amt = [100, @city.warehouse[good]].min if amt == -1
        unit.load(good, amt)
      rescue CocivMessage => e
        message e.message + ' [' + _('Press SPACE') + ']'
        getch
      end
    else
      invalid_key
    end
  end

  #
  # Unload goods from the unit to the city
  #
  def unload_unit(unit, slot)
    amount = unit.slots[slot].amount
    good = unit.slots[slot].good
    return if amount == 0
    # ask amount to the user
    amt = ask_s _("How much of #{good.name.downcase} do you want to move? [#{amount}]")
    if amt == ''
      amt = amount
    else
      amt = amt.to_i
      if amt < 1 or amt > amount
        message 'Invalid amount.'
        @scr.show_cursor = false
        return
      end
    end

    # ask destination
    begin
      amt = [100, unit.slots[slot].amount].min if amt == -1
      unit.unload(slot, amt)
    rescue CocivMessage => e
      message e.message + ' [' + _('Press SPACE') + ']'
      getch
    end
  end

end
