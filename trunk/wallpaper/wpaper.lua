#!/usr/bin/env lua

require 'wp'

function vainwrite(lang)
  local img = wp.load_image('vainwrite.jpg')
  local quote = {
    en = 'How vain it is to sit down to write when you have not stood up to live.',
    pt = 'Quão vão é sentar-se para escrever quando você não se levantou para viver.'
  }
  local style = { color = 0xffffff, font = 'Kingthings.ttf', pointsize = 35,
                  shadow = 2 }
  local text = wp.create_text(quote[lang]..'\n-- Thoreau', 820, style)
  wp.paste(img, text, 70, 60)
  wp.save_image(img, 'vainwrite.'..lang..'.jpg')
end

function house(lang)
  local img = wp.load_image('house.jpg')
  local quote = {
    en = 'A man builds a fine house; and now he has a master, and a task for life: he is to furnish, watch, show it, and keep it in repair, the rest of his days.',
    pt = 'Quão vão é sentar-se para escrever quando você não se levantou para viver.'
  }
  local style = { color = 0xffffff, font = 'WC_RoughTrad.ttf', pointsize = 50,
                  shadow = 2 }
  local text = wp.create_text(quote[lang]..'\n-- Emerson', 1100, style)
  wp.paste(img, text, 300, 60)
  wp.save_image(img, 'house.'..lang..'.jpg')
end


--vainwrite('en')
--vainwrite('pt')
house('en')
