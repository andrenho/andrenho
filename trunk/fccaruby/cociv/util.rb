class Array

  def next(item)
    raise if not self.include? item
    return item if self.last == item
    return self[self.find_index+1]
  end

end
