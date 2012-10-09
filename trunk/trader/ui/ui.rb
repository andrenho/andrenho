require 'gosu'

require 'ui/market'


class UI < Gosu::Window


  # create window
  def initialize
    super 640, 480, false
    self.caption = 'New Hope'
    @font = Gosu::Font.new(self, Gosu::default_font_name, 20)
    @image = load_images
    redefine!
  end


private


  # change the window methods depending on the player position
  def redefine!
    if $w.player.location.is_a? City
      case $w.player.sublocation
      when :market
        self.extend Market
        setup if respond_to? :setup, true
      else
        fail 'Invalid sublocation'
      end
    else
      fail 'Invalid location'
    end
    self
  end


  def clear_background
    draw_quad 0, 0, Gosu::Color::WHITE,
              width, 0, Gosu::Color::WHITE,
              width, height, Gosu::Color::WHITE,
              0, height, Gosu::Color::WHITE, 0
    self
  end


  def load_images
    image = {}
    Dir.entries('data').select { |f| f.end_with? '.png' }.each do |filename|
      image[filename.rpartition('.png')[0].to_sym] = Gosu::Image.new(self, 'data/' + filename, true)
    end
    return image
  end


end
