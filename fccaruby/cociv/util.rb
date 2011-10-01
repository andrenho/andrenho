class Array

  def next(item)
    raise if not self.include? item
    return self[0] if self.last == item
    return self[self.find_index(item)+1]
  end

end
