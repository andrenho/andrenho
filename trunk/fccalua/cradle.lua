package.path = package.path .. ';.\\tileset\\?.dll'
print(package.path)
require 'tileset'
require 'game'

ts = TS.new(8, 8)
