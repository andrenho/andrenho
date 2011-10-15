require 'chars'

class GameLayer

  def initialize(driver, basiclayer)
    @driver = driver
    @game = driver.game
    @basiclayer = basiclayer
  end

  def method_missing(m, *a)
    @basiclayer.method(m).call(*a)
  end

  def puts(*data)
    if data == []
      print("\n") 
    else
      data[data.length == 3 ? 2 : 0] += "\n"
      print(*data)
    end
  end

  def print(*data)
    if data.length == 1
      message = data[0]
    elsif data.length == 3
      x, y, message = data
    else
      raise 'Invalid number of parameters.'
    end

    # units
    message.gsub! /\[unit\s+(\-?\d+)\]/ do |m|
      char_unit($1.to_i)
    end

    # cities
    message.gsub! /\[city\s+(\-?\d+)\]/ do |m|
      char_city($1.to_i)
    end

    # terrains
    message.gsub! /\[terrain\s+(\d+)\s+(\d+)\]/ do |m|
      char_terrain($1.to_i, $2.to_i)
    end
    
    # tiles
    message.gsub! /\[tile\s+(\d+)\s+(\d+)\]/ do |m|
      char_tile($1.to_i, $2.to_i)
    end
    
    if data.length == 1
      self.print_raw message
    elsif data.length == 3
      self.print_raw x, y, message 
    end
  end

private

  def char_unit(n)
    @game.nations.each do |nation|
      nation.units.each do |unit|
        if unit.hash == n
          return "<#{nation_color(nation)}>#{$chars[unit.military]}"
        end
      end
    end
    raise
  end

  def char_city(n)
    @game.nations.each do |nation|
      nation.cities.each do |city|
        if city.hash == n
          if city.residents.length < 10
            c = city.residents.length.to_s
          else
            c = '#'
          end
          return "<#{nation_color(nation)}><reverse>#{c}"
        end
      end
    end
    raise
  end

  def char_terrain(x,y)
    terrain = @game[x,y].terrain # TODO rivers, etc...
    ch = $chars[terrain]
    if @game[x,y].river
      ch = $chars[:river]
    end
    return "<#{ch[1]}>#{ch[0]}"
  end

  def char_tile(x,y)
    if not @game[x,y].known[@game.player] and not @driver.wizard
      return ' '
    elsif @game[x,y].city
      char_city(@game[x,y].city.hash)
    elsif not @game[x,y].units.empty?
      if @game[x,y].units.include? @driver.focused
        char_unit(@driver.focused.hash)
      else
        char_unit(@game[x,y].units[0].hash)
      end
    else
      char_terrain(x,y)
    end
  end

  def nation_color(nation)
    if nation.name == 'Israel' # TODO
      return 'israel'
    end
  end

end
