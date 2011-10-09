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
      @scr.puts "<key>#{c})<default> #{good.name}#{(' '*(12-good.name.length))}[#{@city.warehouse[good]}]"
      c = c.next
    end

    # units available
  end

  def key_list
    {
      '@' => _('Manage city workers'),
    }
  end

  def input_other(ch)
    return CityWorkersDisplay.new(@driver, @city, @scr) if ch == '@'
  end

end
