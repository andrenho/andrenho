require 'communication'
require 'curseslayer'
require 'gamelayer'

class Display

  include Communication

  def initialize(driver, scr)
    raise AbstractMethod.new if self.class == Display
    @driver = driver
    @game = driver.game
    @scr = scr
  end

  def input
    raise '@keys not set' if not @keys
    ch = getch
    if @keys.has_key? ch
      method = "input_#{ch}".to_sym
      return self.method(method).call if self.respond_to? method
      return nil
    end
  end

  def redraw
    raise AbstractMethod.new if self.class == Display
  end

  def key_list
    raise AbstractMethod.new if self.class == Display
  end

end
