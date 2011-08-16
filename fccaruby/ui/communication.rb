module Communication

protected

  # 
  # Ask the user a question that must be responded with a string
  # 
  def ask_s(question)
    s question, 0, 0, :comm
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
    s question, 0, 0, :comm
    setpos 0, question.length + 1
    refresh
    echo
    response = getch
    noecho
    return response
  end

  # 
  # Display a message to the user
  #
  def message(msg)
    s question, 0, 0, :comm
    setpos 0, question.length + 1
    refresh
  end
end
