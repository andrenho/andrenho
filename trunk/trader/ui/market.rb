module Market


private


  def setup
    fail 'Location != City' unless $w.player.location.is_a? City
    @city = $w.player.location
    @moving = false
  end


  def update
  end


  def needs_cursor?
    return !@moving
  end


  def draw
    draw_background
    draw_goods
    draw_truck
    draw_text
    draw_cursor
  end


  def draw_background
    @image[:market_bg].draw(0, 0, 0)
    @image[:market_border].draw(50, 60, 1)
    @image[:market_border].draw(420, 60, 1)
  end


  def draw_goods
    x_bas, y_bas = 70, 90
    y = y_bas
    text_w = @city.goods.each_key.map { |g| @font.text_width(g.to_s.capitalize) }.max
    @city.goods.each_pair do |good, amt|
      @font.draw(good.to_s.capitalize, x_bas+5, y, 5, 1.0, 1.0, Gosu::Color::BLACK)
      @font_tiny.draw(amt.to_s, @font.text_width(good.to_s.capitalize) + x_bas, @font.height + y - 5, 5, 1.0, 1.0, Gosu::Color::BLACK)
      x, left = 0, amt
      while left > 0
        if left < 10
          @image["#{good.to_s}_gray".to_sym].draw(text_w + x_bas + 20 + x, y, 5)
          @image["#{good.to_s}_#{left}".to_sym].draw(text_w + x_bas + 20 + x, y, 5)
        else
          @image[good].draw(text_w + x_bas + 20 + x, y, 5)
        end
        left -= 10; x += 15
      end
    end
  end


  def draw_truck
  end


  def draw_text
    text = "#{@city.name}'s General Store"
    @font_big.draw(text, 68, 14, 4, 1.0, 1.0, Gosu::Color.argb(0xa0ffffff))
    @font_big.draw(text, 66, 12, 5, 1.0, 1.0, Gosu::Color::BLACK)
    text = "Credits: #{$w.player.credits}"
    @font.draw(text, 552, 542, 4, 1.0, 1.0, Gosu::Color.argb(0xa0ffffff))
    @font.draw(text, 550, 540, 552, 1.0, 1.0, Gosu::Color::BLACK)
    text = "#{0}/#{200}"
    @font.draw(text, 622, 567, 4, 1.0, 1.0, Gosu::Color.argb(0xa0ffffff))
    @font.draw(text, 620, 565, 5, 1.0, 1.0, Gosu::Color::BLACK)
  end


  def draw_cursor
  end


end
