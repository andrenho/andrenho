class LandUnit < Unit

protected

  def move_ok?(fx, fy, log=false)
    tile = @game[fx,fy]
    return false if not generic_move_ok? fx, fy, log
    if [Ocean].include? tile.terrain
      $log.debug 'Movement rejected because land units can\'t move over water.' if log
      return false 
    end

    return true
  end

end
