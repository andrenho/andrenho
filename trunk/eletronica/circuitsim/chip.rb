
class Chip

  def initialize
    @input = {}
    @@inputs.each { |a| @input[a] = 0 }
  end

  def method_missing(method, *args)
    if method.to_s[-1] == '='
      # attrib
      raise if not [0, -1].include? args[0] 
      port = method.to_s.chop.to_sym
      @input[port] = args[0]
    else
      5
    end
  end

  @@inputs = []
  def Chip.inputs(*args)
    args.each { |a| @@inputs << a }
  end

end


class NAND < Chip

  inputs :a, :b

end


nand = NAND.new
nand.a = 1
