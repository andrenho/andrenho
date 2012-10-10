module Market


private

  GoodPosition = Struct.new(:type, :good, :x, :y, :w, :h)


  def setup
    fail 'Location != City' unless @player.location.is_a? City
    @city = @player.location
    @moving = nil
  end


  def update
  end


  def button_down(id)
    if id == Gosu::MsLeft
      # grab thing
      goods = @goods_position.select do |n| 
                n.x <= mouse_x and n.y <= mouse_y and
                (n.x + n.w) > mouse_x and (n.y + n.h) > mouse_y
              end
      if not goods.empty?
        @moving = [goods[0].type, goods[0].good]
        p @moving
      end
    end
  end


  def button_up(id)
    if id == Gosu::MsLeft and @moving
      # drop thing
    end
  end


  def needs_cursor?
    return @moving == nil
  end


  def draw
    draw_background
    @goods_position = []
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
    x, y = 70, 90
    text_w = @city.goods.each_key.map { |g| 
               @font.text_width(g.to_s.capitalize) }.max
    @city.goods.each_pair do |good, amt|
      draw_good(good, amt, x, y, text_w, :buy)
    end
  end


  def draw_truck
    x, y = 440, 90
    text_w = @player.truck.cargo.each_key.map { |g| 
               @font.text_width(g.to_s.capitalize) }.max
    @player.truck.cargo.each_pair do |good, amt|
      draw_good(good, amt, x, y, text_w, :sell)
    end
  end


  def draw_good(good, amt, x_bas, y, text_w, type)
    price = (type == :buy) ? @city.buy_price(good) : @city.sell_price(good)
    @font.draw(good.to_s.capitalize, x_bas+5, y - 5, 5, 1.0, 1.0, 
               Gosu::Color::BLACK)
    @font_tiny.draw("#{amt.to_s}/&#{price}", 
                    @font.text_width(good.to_s.capitalize) + x_bas - 15, 
                    @font.height + y - 15, 5, 1.0, 1.0, Gosu::Color::BLACK)
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
    @goods_position << GoodPosition.new(type, good, x_bas, y-10, 
                                        350, @font.height + 30)
  end


  def draw_text
    text = "#{@city.name}'s General Store"
    @font_big.draw(text, 68, 14, 4, 1.0, 1.0, Gosu::Color.argb(0xa0ffffff))
    @font_big.draw(text, 66, 12, 5, 1.0, 1.0, Gosu::Color::BLACK)
    text = "&#{@player.credits}"
    @font.draw(text, 602, 542, 4, 1.0, 1.0, Gosu::Color.argb(0xa0ffffff))
    @font.draw(text, 600, 540, 552, 1.0, 1.0, Gosu::Color::BLACK)
    text = "#{@player.truck.slots_occupied}/#{@player.truck.slots}"
    @font.draw(text, 622, 567, 4, 1.0, 1.0, Gosu::Color.argb(0xa0ffffff))
    @font.draw(text, 620, 565, 5, 1.0, 1.0, Gosu::Color::BLACK)
  end


  def draw_cursor
    if @moving 
      @image[@moving[1]].draw(mouse_x, mouse_y, 10)
    end
  end


end
