require 'gosu'

require 'ui/market'

class UI < Gosu::Window

  def initialize
    super 640, 480, false
    self.caption = 'New Hope'
    redefine!
  end

  def redefine!
    if $w.player.location.is_a? City
      case $w.player.sublocation
      when :market
        self.extend Market
      else
        fail 'Invalid sublocation'
      end
    else
      fail 'Invalid location'
    end
  end

end
