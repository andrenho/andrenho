class LandUnit < Unit

protected

  def move_ok?(fx, fy)
    tile = @game[fx,fy]
    return false if not generic_move_ok? fx, fy
    return false if [Ocean, Sea].include? tile.terrain

    return true
  end

end
