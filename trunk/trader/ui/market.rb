module Market


private


  def setup
    fail 'Location != City' unless $w.player.location.is_a? City
    @city = $w.player.location
  end


  def update
  end


  def draw
    clear_background
    draw_goods
  end


  def draw_goods
    y = 30
    text_w = @city.goods.each_key.map { |g| @font.text_width(g.to_s.capitalize) }.max
    @city.goods.each_pair do |good, amt|
      @font.draw(good.to_s.capitalize, 20, y, 5, 1.0, 1.0, Gosu::Color::BLACK)
      x, left = 0, amt
      while left > 0
        if left > 10
          @image[good].draw(text_w + 30 + x, y, 5)
        else
          # TODO
        end
        left -= 10; x += 15
      end
    end
  end


end
