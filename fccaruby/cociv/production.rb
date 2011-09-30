class Production

  # Theorical number of goods that can be produced.
  attr_accessor :theorical

  # Effective production, considering storage and raw good production.
  attr_accessor :effective

  # How much it could be produced if the raw goods were available.
  attr_accessor :lacking

  # After the raw goods were used, how much is left.
  attr_accessor :surplus

  def initialize
    @theorical, @effective, @lacking, @surplus = 0, 0, 0, 0
  end

end
