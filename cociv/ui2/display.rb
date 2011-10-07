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
    if key_list.has_key? ch
      method = "input_#{ch}".to_sym
      return self.method(method).call if self.respond_to? method
      return nil
    elsif ch == '?'
      show_help
      nil
    end
  end

  def show_help
    @scr.show_cursor = false
    w = 50
    h = key_list.map{ |k,v| v.wrap(25).split("\n").length }.sum + 6
    x = @scr.w/2-w/2
    y = @scr.h/2-h/2
    @scr.box x, y, w, h, true, 'help'

    @scr.puts x+4, y+2, '<help>Key                 Function'
    @scr.puts '<help>---                 --------'
    kl = key_list()
    kl['?'] = _('Show this help')
    @scr.y = y+4
    kl.each_pair do |k,v|
      key = (k != k.downcase) ? "Shift+#{k.upcase}" : k.upcase
      @scr.x = x+4
      @scr.print "<help>#{key}#{'.'*(20-key.length)}"
      @scr.x = x+24
      v.wrap(25).split("\n").each do |s|
        @scr.puts '<help>' + s
      end
    end

    @scr.refresh
    @scr.getch
  end

  def redraw
    raise AbstractMethod.new if self.class == Display
  end

  def key_list
    raise AbstractMethod.new if self.class == Display
  end

end
