module Communication

protected

  # 
  # Ask the user a question that must be responded with a string
  # 
  def ask_s(question)
    s ' ' * cols, 0, 0, :comm
    s '<message>' + question, 0, 0, :comm
    setpos 0, question.length + 1
    refresh
    echo
    response = getstr
    noecho
    return response == '' ? nil : response
  end

  # 
  # Ask the user a question that must be responded with a char
  # 
  def ask_c(question)
    s ' ' * cols, 0, 0, :comm
    s '<message>' + question, 0, 0, :comm
    setpos 0, question.length + 1
    refresh
    echo
    response = getch
    noecho
    return response
  end

  #
  # Ask the user a question that must be responded with yes/no
  #
  def ask_yn(question, default=true)
    while true
      ch = ask_c(question + ' [' + _('yn') + ']')
      if ch == 'y'
        return true
      elsif ch == 'n' or ch == 27
        return false
      elsif ch == 10 or ch == 13
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
    sx = cols - max - 5 
    sy = 1
    c = ?a
    options.each do |option|
      s ' ' * (max+2), sy, sx-1, :comm
      s "#{c} - #{option[1]}", sy, sx, :comm
      c = c.next
      sy += 1
    end
    s ' ' * (max+2), sy, sx-1, :comm
    ch = ask_c question
    n = ch.ord - ?a.ord
    message ''
    return nil if n < 0 or n > options.length - 1
    return options[n][0]
  end

  # 
  # Display a message to the user
  #
  def message(msg)
    @scr.print 0, 0, '<message>' + msg
    refresh
    @last_message = msg
  end

  def show_last_message
    if @last_message
      message @last_message
      @last_message = nil
    end
  end

end
