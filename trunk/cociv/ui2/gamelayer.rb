require 'chars'

class GameLayer

  def initialize(game, basiclayer)
    @game = game
    @basiclayer = basiclayer
  end

  def method_missing(m, *a)
    @basiclayer.method(m).call(*a)
  end

  def puts(*data)
    data[data.length == 3 ? 2 : 0] += "\n"
    print(*data)
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
    message.gsub! /\[unit\s+(\d)\]/ do |m|
      char_unit($1)
    end

    # cities
    message.gsub! /\[city\s+(\d)\]/ do |m|
      char_city($1)
    end

    # terrains
    message.gsub! /\[terrain\s+(\d)\s+(\d)\]/ do |m|
      char_terrain($1, $2)
    end
    
    # tiles
    message.gsub! /\[tile\s+(\d)\s+(\d)\]/ do |m|
      char_tile($1, $2)
    end
    
    if data.length == 1
      self.print_raw message
    elsif data.length == 3
      self.print_raw x, y, message 
    end
  end

private

  def char_unit(n)
    'X'
  end

  def char_city(n)
    'O'
  end

  def char_terrain(x,y)
    '.'
  end

  def char_tile(x,y)
    if @game[x,y].city
      char_city(@game[x,y].city.hash)
    elsif not @game[x,y].units.empty?
      char_unit(@game[x,y].units[0]) # TODO
    else
      char_terrain(x,y)
    end
  end

end
