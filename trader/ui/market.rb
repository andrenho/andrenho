module Market


private

  GoodPosition = Struct.new(:type, :good, :pos)
  Moving = Struct.new(:type, :good, :parcial)


  class MarketTextInput < Gosu::TextInput
    attr_reader :selected
    def initialize(value)
      super()
      self.text = value.to_s
      @selected = true
    end
    def filter c
      self.text = '' if @selected
      @selected = false
      /[0-9]/ =~ c ? c : nil
    end
    def value
      return self.text.to_i
    end
  end


  def setup
    fail 'Location != City' unless @player.location.is_a? City
    @city = @player.location
    @moving = nil
    @buy_pos = Position.new(50, 60, 
                            @image[:market_border].width, 
                            @image[:market_border].height)
    @sell_pos = Position.new(420, 60, @buy_pos.w, @buy_pos.h)
  end


  def update
  end


  def button_down(id)
    # grab thing
    if id == Gosu::MsLeft or id == Gosu::MsRight
      goods = @goods_position.select { |n| n.pos.inside? mouse_x, mouse_y }
      if not goods.empty?
        @moving = Moving.new(goods[0].type, goods[0].good, id == Gosu::MsRight)
      end
    # return pressed
    elsif self.text_input and (id == Gosu::KbEnter or id == Gosu::KbReturn)
      if @moving.type == :buy
        @player.buy(@moving.good, self.text_input.value)
      elsif @moving.type == :sell
        @player.sell(@moving.good, self.text_input.value)
      end
      @moving = nil
      self.text_input = nil
    end
  end


  def button_up(id)
    if id == Gosu::MsRight and @moving
      v = (@moving.type == :buy) ? @city.goods[@moving.good] : @player.truck.cargo(@moving.good)
      self.text_input = MarketTextInput.new(v)
    elsif id == Gosu::MsLeft and @moving
      # drop thing
      if @moving.type == :buy and @sell_pos.inside? mouse_x, mouse_y
        @player.buy(@moving.good, 10)
      elsif @moving.type == :sell and @buy_pos.inside? mouse_x, mouse_y
        @player.sell(@moving.good, 10)
      end
      @moving = nil
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
    draw_gui if text_input
  end


  def draw_background
    @image[:market_bg].draw(0, 0, 0)
    @image[:market_border].draw(@buy_pos.x, @buy_pos.y, 1)
    @image[:market_border].draw(@sell_pos.x, @sell_pos.y, 1)
  end


  def draw_goods
    x, y = 70, 90
    text_w = @city.goods.each_key.map { |g| 
               @font.text_width(g.to_s.capitalize) }.max
    @city.goods.each_pair do |good, amt|
      draw_good(good, amt, x, y, text_w, :buy)
      y += 43
    end
  end


  def draw_truck
    x, y = 440, 90
    text_w = @player.truck.cargo.each_key.map { |g| 
               @font.text_width(g.to_s.capitalize) }.max
    @player.truck.cargo.each_pair do |good, amt|
      draw_good(good, amt, x, y, text_w, :sell)
      y += 43
    end
  end


  def draw_good(good, amt, x_bas, y, text_w, type)
    price = (type == :buy) ? @city.buy_price(good) : @city.sell_price(good)
    @font.draw(good.to_s.capitalize, x_bas+5, y - 5, 5, 1.0, 1.0, 
               Gosu::Color::BLACK)
    @font_tiny.draw("#{amt.to_s}/&#{price}", 
                    text_w + x_bas - 25, 
                    @font.height + y - 15, 5, 1.0, 1.0, Gosu::Color::BLACK)
    x, left = 0, [amt, 100].min
    while left > 0
      if left < 10
        @image["#{good.to_s}_gray".to_sym].draw(text_w + x_bas + 20 + x, y, 5)
        @image["#{good.to_s}_#{left}".to_sym].draw(text_w + x_bas + 20 + x, y, 5)
      else
        @image[good].draw(text_w + x_bas + 20 + x, y, 5)
      end
      left -= 10; x += 15
    end
    @goods_position << GoodPosition.new(type, good, 
                                        Position.new(x_bas, y-10, 
                                                     350, @font.height + 10))
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
    if @moving and not text_input
      @image[@moving.good].draw(mouse_x, mouse_y, 10)
    end
  end


  def draw_gui
    w, h = 300, 150
    x, y, s = self.width / 2 - w / 2, self.height / 2 - h / 2, 5
    b, t = Gosu::Color::BLACK, Gosu::Color::WHITE
    draw_quad x, y, b, x+w, y, b, x+w, y+h, b, x, y+h, b, 20
    draw_quad x+s, y+s, t, x+w-s, y+s, t, x+w-s, y+h-s, t, x+s, y+h-s, t, 21
    @font.draw('Amount', x+30, y+30, 22, 1.0, 1.0, b)
    if self.text_input.selected
      w2 = @font_huge.text_width(self.text_input.text + '.') + 20
      h2 = @font_huge.height
      x2, y2 = x+w-25-w2, y+h-35-h2
      c = Gosu::Color.argb(0xffa0a0a0)
      draw_quad x2, y2, c, x2+w2, y2, c, x2+w2, y2+h2, c, x2, y2+h2, c, 21
    end
    @font_huge.draw_rel(self.text_input.text + '.', x+w-30, y+h-30, 22, 1.0, 1.0, 1.0, 1.0, b)
  end


end
