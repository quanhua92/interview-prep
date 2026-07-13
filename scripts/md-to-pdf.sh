#!/usr/bin/env bash
# Convert any Markdown file to PDF via Pandoc + XeLaTeX.
# Usage: ./scripts/md-to-pdf.sh <input.md> [output.pdf]
#
# Requirements: pandoc, xelatex (MacTeX or TeX Live)
#   brew install pandoc && brew install --cask mactex

set -euo pipefail

if [ $# -lt 1 ]; then
  echo "Usage: $0 <input.md> [output.pdf]"
  exit 1
fi

INPUT="$(cd "$(dirname "$1")" && pwd)/$(basename "$1")"

if [ ! -f "$INPUT" ]; then
  echo "Error: $INPUT not found"
  exit 1
fi

# Default output: same name as input with .pdf extension
BASENAME="$(basename "$INPUT" .md)"
INPUT_DIR="$(dirname "$INPUT")"
OUTPUT="${2:-$INPUT_DIR/$BASENAME.pdf}"

# Clean up stale build artifacts
STEM="$INPUT_DIR/$BASENAME"
rm -f "$STEM".aux "$STEM".log "$STEM".tex
rm -f "$OUTPUT"

# Generate PDF — Menlo for Unicode box-drawing characters in ASCII diagrams
pandoc "$INPUT" \
  --from markdown \
  --pdf-engine=xelatex \
  --variable=geometry:"margin=0.6in" \
  --variable=fontsize:"10pt" \
  --variable=fontfamily:"helvet" \
  --variable=monofont:"Menlo" \
  --variable=linkcolor:"blue" \
  --variable=urlcolor:"blue" \
  --variable=linestretch:"1.1" \
  --toc \
  --toc-depth=2 \
  --standalone \
  --output "$OUTPUT"

# Clean up leftover LaTeX artifacts
rm -f "$STEM".aux "$STEM".log "$STEM".tex

echo "Done: $OUTPUT"
