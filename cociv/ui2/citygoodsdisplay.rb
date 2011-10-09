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
      # display help
      show_help_move_goods
      # move focus
      @scr.x, @scr.y = choice[1], choice[2]
      @scr.show_cursor = true

      # get new char
      nch = @scr.getch
      amt = -1
      # TODO - check amount
      message '' ; @scr.show_cursor = false
      nchoice = (choice[0].is_a? Good) ? @units_store[ch] : @goods[ch]
      if nchoice
        if choice[0].is_a? Good # moving from city to unit
          amt = [100, @city.warehouse[choice[0]].amount].max if amt == -1
          nchoice[0].load(choice[0], amt)
        else # moving from unit to city
          amt = [100, choice[0].slots[choice[3]].amount].max if amt == -1
          choice[0].unload(nchoice[0], amt)
        end
      else
        invalid_key

      end

    else
      invalid_key
      
    end
  end

private ###################################

  def show_help_move_goods
    message _('Where do you want to move these goods to?')
    help = '<key>#<default>: ' + _('Move a specific amount of goods')
    @scr.print 1, @scr.h-1, help
  end


end
