function CodeBlock(block)
  if block.classes[1] == "mermaid" then
    local content = block.text
    local hash = pandoc.sha1(content)
    -- Put generated image files in the same directory
    local img_path = "mermaid-" .. hash .. ".png"
    
    -- Check if image already exists to speed up recompilation
    local f_check = io.open(img_path, "r")
    if f_check then
      f_check:close()
      return pandoc.Para({pandoc.Image({pandoc.Str("")}, img_path)})
    end

    -- Create a temporary file containing the Mermaid code
    local tmp_in = os.tmpname() .. ".mmd"
    local f_in = io.open(tmp_in, "w")
    f_in:write(content)
    f_in:close()

    -- Locate the local mmdc binary
    local mmdc_bin = "node_modules/.bin/mmdc"
    local f_mmdc = io.open(mmdc_bin, "r")
    if f_mmdc then
      f_mmdc:close()
    else
      mmdc_bin = "mmdc" -- Fallback to global if local not found
    end

    -- Run mmdc command to generate PNG
    local cmd = string.format('"%s" -i "%s" -o "%s" -b white', mmdc_bin, tmp_in, img_path)
    os.execute(cmd)
    os.remove(tmp_in)
    
    return pandoc.Para({pandoc.Image({pandoc.Str("")}, img_path)})
  end
end
