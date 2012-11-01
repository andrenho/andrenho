require 'yaml'
require 'optparse'
require 'pp'

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
yaml = nil
File.open(ARGV[0]) { |yf| yaml = YAML::load(yf) }

#
# classes
#
class Image

  attr_reader :image, :fontname, :fontsize, :fontcolor, :author, :pos,
              :quote, :shadow, :wrap

  def initialize(r)
    @image = r['image']
    @fontname = r['font'][0] or 'Arial'
    @fontsize = r['font'][1] or 36
    @fontcolor = r['color'] or 'white'
    @author = r['author']
    @pos = r['pos']
    @quote = r['quote']
    @wrap = r['wrap'] or 10000

    @shadow = false
    r['style'].each do |st|
      @shadow = true if st == 'shadow'
    end
  end

end

#
# wrap text
#
def wrap(txt, col = 80)
  txt.gsub(/(.{1,#{col}})( +|$\n?)|(.{1,#{col}})/,
    "\\1\\3\n") 
end

#
# parse image
#
yaml.each do |image_yaml|

  image = Image.new(image_yaml)

  image.quote.each_pair do |lang, quote|

    # create quote
    # -size #{image.pos[2]}x 
    montage = "montage.exe -background none -fill #{image.fontcolor} -font #{image.fontname} -pointsize #{image.fontsize} label:\"#{wrap(quote, image.wrap)}\" +set label "

    # add styles
    montage += '-shadow ' if image.shadow
    
    # image background
    montage += '-background transparent -geometry +5+5 temp.png'

    system(montage)

    # create new image
    filename = image.image.split('.')[0..-2].join('.') + ".#{lang}." + image.image.split('.')[-1]
    system("composite -geometry +#{image.pos[0]}+#{image.pos[1]} temp.png #{image.image} #{filename}")

  end
  
end
