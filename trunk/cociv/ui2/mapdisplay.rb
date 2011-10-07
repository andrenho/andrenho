require 'display'

class MapDisplay < Display

  def initialize(driver, scr)
    super(driver, scr)
  end

  def key_list
    {
      'q' => 'Exit game',
      't' => 'Test',
    }
  end

  def redraw
    super
    clear
  end

  def input_q
    return :exit
  end

  def input_t
    r = menu 'Pergunta?', [ [nil,'teste 1'], [nil,'asdasd asasd'], ['a','xxx']]
    close_screen
    p r
    exit 1
  end

end
