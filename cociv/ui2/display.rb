require 'communication'
require 'curseslayer'
require 'gamelayer'

$messages = []

# 
# Basic class for screens. It should be inherited by each one of the screens.
#
class Display

  include Communication

  # 
  # Constructor
  #
  def initialize(driver, scr)
    raise AbstractMethod.new if self.class == Display
    @driver = driver
    @game = driver.game
    @scr = scr
  end

  # 
  # Deals with keyboard events from the user
  #
  def input
    ch = getch
    method = "input_#{ch}".to_sym
    if self.respond_to? method
      return self.method(method).call 
    elsif ch == '?'
      show_help
    elsif ch == 27 # ESC
      message ''
      return self.input_esc if self.respond_to? :input_esc
    elsif self.respond_to? :input_other
      return input_other ch
    else
      message _("Invalid key. Press '?' for help.")
    end
    return nil
  end

  # 
  # Redraw the screen
  #
  def redraw
    raise AbstractMethod.new if self.class == Display
  end

protected ################################

  # 
  # List of keys that can be used on this screen
  #
  def key_list
    raise AbstractMethod.new if self.class == Display
  end

  #
  # Display the last message
  #
  def show_messages
    if not $messages.empty?
      m = ($messages.join("\n") + "\n<default><reverse>" + _(' --- Press ENTER --- ')).wrap(@scr.w)
      @scr.puts 0, 0, (' ' * @scr.w + "\n") * m.count("\n")
      @scr.puts 0, 0, '<message>' + m
      $messages = [] # TODO
      until [27, 13, ' '].include? getch ; end
      redraw
    end
  end

  def invalid_key
    $messages << _("Invalid key. Press '?' for help.")
    redraw
    nil
  end

private ###################################

  #
  # Display help
  # 
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

end
