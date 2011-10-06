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
    ch = getch
    method = "input_#{ch}".to_sym
    if self.respond_to? method
      return self.method(method).call
    end
    return nil
  end

  def redraw
    raise AbstractMethod.new if self.class == Display
  end

  def key_list
    raise AbstractMethod.new if self.class == Display
  end

end
