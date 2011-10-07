require 'display'

class CityWorkersDisplay < Display

  def initialize(driver, city, scr)
    super(driver, scr)
    @city = city
  end

  def key_list
    {
    }
  end

  def redraw
    super
    @scr.clear

    # box
    @scr.box 0, 0, @scr.w-1, @scr.h-2
    @scr.print (@scr.w/2 - @city.name.length/2), 0, '<title> '+@city.name+' '

    # buildings
    @scr.puts 1, 1, '<title>'+_('Buildings')
    max_bd_len = (BuildingType.all.collect { |b| b.name.length }).max
    @scr.puts max_bd_len+7, 1, "#{_('Wks')}   #{_('Production')}"
    c = ?a
    @city.buildings.each do |building|
      @scr.x = 2
      @scr.print "<key>#{c}<default> - #{building.type.name}"

      @scr.puts
      c = c.next
    end
  end

end
