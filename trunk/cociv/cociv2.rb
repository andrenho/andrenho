#!/usr/bin/env ruby

$: << '.'
require 'cociv/driver'
require 'ui2/ui'

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
