#!/usr/bin/env lua

require 'wp'

function vainwrite(lang)
  local img = wp.load_image('vainwrite.jpg')
  local quote = {
    en = 'How vain it is to sit down to write when you have not stood up to live.',
    pt = 'Quão vão é sentar-se para escrever quando você não se levantou para viver.'
  }
  local style = { color = 'white', font = 'Kingthings.ttf', pointsize = 65 }
  local text = wp.create_text(quote[lang]..'\n-- Thoreau', 600, style)
  wp.paste(img, text, 60, 90)
  wp.save_image(img, 'vainwrite.'..lang..'.jpg')
end

vainwrite('pt')
