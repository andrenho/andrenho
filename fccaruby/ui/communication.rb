module Communication

protected

  # 
  # Ask the user a question that must be responded with a string
  # 
  def ask(question)
    s question, 0, 0, :comm
    setpos 0, question.length + 1
    refresh
    echo
    response = getstr
    noecho
    return response == '' ? nil : response
  end

end
