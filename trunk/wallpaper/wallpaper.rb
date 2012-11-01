require 'yaml'
require 'optparse'

#
# get options
#
OptionParser.new do |opts|
  opts.banner = "Usage: #{File.basename($0)} config.yaml"
end.parse!

if ARGV.length == 0
  puts "Usage: #{File.basename($0)} config.yaml"
  exit 1
end

#
# read YAML file
#
File.open(ARGV[0]) { |yf| yaml = YAML::load(yf) }
