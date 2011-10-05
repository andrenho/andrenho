require 'communication'
require 'curseslayer'
require 'gamelayer'

class Display

  include Communication

  def initialize
    raise AbstractMethod.new if self.class == Display
  end

  def redraw
    raise AbstractMethod.new if self.class == Display
  end

  def input
    raise AbstractMethod.new if self.class == Display
  end

end
