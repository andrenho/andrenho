require 'display'

class MapDisplay < Display

  def initialize(driver, scr)
    super(driver, scr)
  end

  def redraw
    super
  end

  def input_q
    return :exit
  end

end
