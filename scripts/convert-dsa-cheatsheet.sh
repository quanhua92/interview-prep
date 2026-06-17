#!/bin/bash

# Move to the root directory of the project
cd "$(dirname "$0")/.."

echo "Converting DSA_CHEATSHEET.md to PDF..."

if ! command -v quarto &> /dev/null; then
    echo "Error: 'quarto' is not installed."
    echo "Please install Quarto (https://quarto.org)."
    exit 1
fi

# Render using Quarto with our custom Lua filter
quarto render DSA_CHEATSHEET.md --to pdf --no-clean --lua-filter scripts/mermaid-filter.lua

if [ $? -ne 0 ]; then
    echo "Error: Failed to convert DSA_CHEATSHEET.md. Aborting script execution."
    exit 1
fi

echo "Conversion complete! PDF is saved in the current directory."
