$: << '.'
require 'cociv/driver'
require 'ui/ui'

#
# main
#
begin
  ui = UI.new
  ui.init
  ui.run!
ensure
  ui.close
end
