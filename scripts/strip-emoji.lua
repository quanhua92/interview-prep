-- Strip emoji and variation selectors that XeLaTeX cannot render.
-- Targets: U+1F000-U+1FFFF (emoji), U+FE00-U+FE0F (variation selectors).
-- Applied to Str, Code, and CodeBlock elements.
-- Applied via: pandoc --lua-filter=strip-emoji.lua

local function strip_emoji(s)
  -- 4-byte UTF-8 emoji (U+1F000-U+1FFFF): F0 9F xx xx
  s = s:gsub("\240\159[\128-\191][\128-\191]", "")
  -- Variation selectors (U+FE00-U+FE0F): EF B8 80-8F
  s = s:gsub("\239\184[\128-\143]", "")
  return s
end

function Str(el)
  el.text = strip_emoji(el.text)
  el.text = el.text:gsub("^%s+", ""):gsub("%s+$", "")
  if el.text == "" then
    return {}
  end
  return el
end

function Code(el)
  el.text = strip_emoji(el.text)
  return el
end

function CodeBlock(el)
  el.text = strip_emoji(el.text)
  return el
end
