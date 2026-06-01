#!/usr/bin/env bash
# Convert cv.md to a professional, ATS-friendly PDF via Pandoc + XeLaTeX.
# Usage: ./scripts/cv-to-pdf.sh [output.pdf]
#
# Requirements: pandoc, xelatex (MacTeX or TeX Live)
#   brew install pandoc && brew install --cask mactex

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"
INPUT="$ROOT_DIR/cv.md"
OUTPUT="${1:-$ROOT_DIR/cv.pdf}"

if [ ! -f "$INPUT" ]; then
  echo "Error: $INPUT not found"
  exit 1
fi

# Clean up stale build artifacts
rm -f "$ROOT_DIR"/cv_*.aux "$ROOT_DIR"/cv_*.log "$ROOT_DIR"/cv_*.pdf "$ROOT_DIR"/cv_*.tex
rm -f "$OUTPUT"

# Generate PDF
pandoc "$INPUT" \
  --from markdown \
  --pdf-engine=xelatex \
  --variable=geometry:"margin=0.75in" \
  --variable=fontsize:"11pt" \
  --variable=fontfamily:"helvet" \
  --variable=linkcolor:"black" \
  --variable=urlcolor:"black" \
  --variable=linestretch:"1.15" \
  --standalone \
  --output "$OUTPUT"

# Clean up leftover LaTeX artifacts
rm -f "$ROOT_DIR"/cv_*.aux "$ROOT_DIR"/cv_*.log "$ROOT_DIR"/cv_*.tex

echo "Done: $OUTPUT"
