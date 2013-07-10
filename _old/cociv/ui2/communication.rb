class Communication

  attr_reader :messages

  def initialize(scr)
    @scr = scr
    @messages = []
  end

  # 
  # Ask the user a question that must be responded with a string
  # 
  def ask_s(question)
    txt = (question + ' ').wrap(@scr.w)
    @scr.x = @scr.y = 0
    txt.split("\n").each { @scr.puts ' ' * @scr.w }
    @scr.print 0, 0, '<message>' + txt.chomp
    refresh
    return @scr.gets
  end

  # 
  # Ask the user a question that must be responded with a char
  # 
  def ask_c(question, x=-1, y=-1)
    txt = (question + ' ').wrap(@scr.w)
    @scr.x = @scr.y = 0
    txt.split("\n").each { @scr.puts ' ' * @scr.w }
    @scr.x = (question.start_with? '<right>') ? @scr.w-1 : 0
    @scr.y = 0
    @scr.print '<message>' + txt.chomp
    @scr.refresh
    @scr.echo = true
    @scr.x = x; @scr.y = y if x != -1
    @scr.show_cursor = true
    response = @scr.getch
    @scr.show_cursor = false
    @scr.echo = false
    return nil if response == 27
    return response
  end

  #
  # Ask the user a question that must be responded with yes/no
  #
  def ask_yn(question, default=false)
    while true
      ch = ask_c(question + ' [' + _('yn') + ']')
      if ch == 'y'
        return true
      elsif ch == 'n'
        return false
      elsif ch == 10 or ch == 13 or ch == nil # (ESC)
        return default
      end
    end
  end

  #
  # Ask a question with a menu. Options is a list of arrays, each one
  # containing [return_if_selected, option_text]
  #
  def menu(question, options)
    max = (options.collect { |o| o[1].length }).max
    sx = @scr.w - max - 5 
    sy = 1
    c = ?a
    options.each do |option|
      @scr.print sx-1, sy, ' ' * (max+2)
      @scr.print sx, sy, "<message>#{c} - #{option[1]}"
      c = c.next
      sy += 1
    end
    @scr.print sx-1, sy, ' ' * (max+2)
    ch = ask_c("<right>#{question}")
    begin
      n = ch.ord - ?a.ord
    rescue
      return nil
    end
    return nil if n < 0 or n > options.length - 1
    return options[n][0]
  end

  def top_message(msg)
    m = msg.wrap(@scr.w)
    @scr.puts 0, 0, (' ' * @scr.w + "\n") * m.count("\n")
    @scr.puts 0, 0, '<message>' + msg
  end

  #
  # Display the last message
  #
  def show_messages
    if not @messages.empty?
      m = (@messages.join("\n") + "\n<default><reverse>" + _(' --- Press ENTER --- ')).wrap(@scr.w)
      @scr.puts 0, 0, (' ' * @scr.w + "\n") * m.count("\n")
      @scr.puts 0, 0, '<message>' + m
      @messages = [] # TODO
      until [27, 10, 13, ' '].include? getch ; end
      return true
    end
    return false
  end


  # 
  # Display a message to the user
  #
=begin
  def message(msg)
    m = msg.wrap(@scr.w)
    @scr.x = @scr.y = 0
    m.split("\n").each { @scr.puts ' ' * @scr.w }
    @scr.puts 0, 0, '<message>' + m
    refresh
  end
=end

end
