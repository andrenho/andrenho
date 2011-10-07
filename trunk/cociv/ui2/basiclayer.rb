class AbstractMethod < Exception; end

class BasicLayer

  attr_reader :x, :y
  attr_accessor :default_color

  def initialize
    raise AbstractMethod.new if self.class == BasicLayer
    @x = @y = 0
    @color = {}
    goto(0,0)
  end

  def x=(v)
    @x = v
    goto @x, @y
  end

  def y=(v)
    @y = v
    goto @x, @y
  end

  #def puts(*data)
  #  data[data.length == 3 ? 2 : 0] += "\n"
  #  print(*data)
  #end

  def print_raw(*data)
    self.color = nil
    if data.length == 1
      message = data[0]
    elsif data.length == 3
      self.x, self.y, message = data
    else
      raise 'Invalid number of parameters.'
    end
    ini_x = self.x
    
    w = message.gsub(/\<.+\>/,'').split("\n").map{ |s| s.length }.max

    parsing_command = false
    command = ''
    message.each_char do |c|
      if not parsing_command
        if c == "\n"
          self.x = ini_x
          self.y += 1
        elsif c == '<'
          command = ''
          parsing_command = true
        else
          printc c
          self.x += 1
        end
      else
        if c == '>'
          status = run_command(command)
          if status == :right
            self.x -= w
            x_ini = self.x
          end
          parsing_command = false
        else
          command += c
        end
      end
    end
  end

  def w; raise AbstractMethod.new; end
  def h; raise AbstractMethod.new; end
  def clear; raise AbstractMethod.new; end
  def printc(data); raise AbstractMethod.new; end
  def box(x,y,w,h,filled=false); raise AbstractMethod.new; end
  def refresh; raise AbstractMethod.new; end
  def init_color(name, color); raise AbstractMethod.new; end
  def color=(name); raise AbstractMethod.new; end
  def show_cursor=(t); raise AbstractMethod.new; end
  def echo=(t); raise AbstractMethod.new; end
  def getch; raise AbstractMethod.new; end
  def gets; raise AbstractMethod.new; end
  def exit; raise AbstractMethod.new; end
  
protected
  
  def goto(x,y); raise AbstractMethod.new; end

  def run_command(cmd)
    if @color.has_key? cmd or cmd == 'default'
      self.color = cmd
      return nil
    elsif cmd == 'right'
      return :right
    else
      raise "Invalid command #{cmd}!"
    end
  end

end
