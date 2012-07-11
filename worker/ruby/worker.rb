$: << '.'
require 'level'
require 'uicurses'

level = Level.new(0)
ui = UICurses.new
ui.level = level

while true
    ui.draw!
    if ui.running
        ui.step!
    else
        ui.edit!
    end
end
