require 'gosu'
require 'texplay'

require 'ui/util'
require 'ui/market'


class UI < Gosu::Window


  # create window
  def initialize
    super 800, 600, false
    self.caption = 'New Hope'
    @font_huge = Gosu::Font.new(self, 'data/FromWhereYouAre.ttf', 60)
    @font_big = Gosu::Font.new(self, 'data/FromWhereYouAre.ttf', 42)
    @font = Gosu::Font.new(self, 'data/FromWhereYouAre.ttf', 36)
    @font_tiny = Gosu::Font.new(self, 'data/FromWhereYouAre.ttf', 20)
    @image = load_images
    @player = $w.player
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
    Dir.entries('data').select { |f| f.end_with? '.png' or f.end_with? '.jpg' }.each do |filename|
      image[filename[0..-5].to_sym] = Gosu::Image.new(self, 'data/' + filename, true)
    end

    # setup goods images
    [:grain, :wood, :oil, :iron, :furs, :moonshine, :narcotics, :slaves,
     :computer, :medicine].each do |good|
      (1..9).each do |n|
        original = image[good]
        sym = "#{good.to_s}_#{n}".to_sym
        image[sym] = TexPlay.create_image(self, (original.width / 10.0 * n).to_i, original.height)
        image[sym].splice(original, 0, 0)
      end
    end

    return image
  end


end
