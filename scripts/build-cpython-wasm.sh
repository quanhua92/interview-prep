#!/usr/bin/env bash
set -euo pipefail

# Download and pre-compile CPython WASM binary for faster startup
# Run this to update the python.cwasm file for container builds
# Output: python.wasm + python.cwasm in <repo-root>/python-wasi/

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CPYTHON_VERSION="3.14.5"
OUT_DIR="$REPO_ROOT/python-wasi"

echo "==> Downloading CPython ${CPYTHON_VERSION} WASM build..."
mkdir -p "$OUT_DIR"
curl -L "https://github.com/brettcannon/cpython-wasi-build/releases/download/v${CPYTHON_VERSION}/python-${CPYTHON_VERSION}-wasi_sdk-24.zip" \
    -o /tmp/python-wasi.zip
unzip -q /tmp/python-wasi.zip -d "$OUT_DIR"
rm /tmp/python-wasi.zip
ls -lh "$OUT_DIR/python.wasm"

echo "==> Pre-compiling to .cwasm for faster startup..."
wasmtime compile -W fuel=1 -W epoch-interruption=y -W max-memory-size=536870912 \
    "$OUT_DIR/python.wasm" -o "$OUT_DIR/python.cwasm"
ls -lh "$OUT_DIR/python.cwasm"

echo "==> Verification: running python.cwasm with wasmtime..."
echo 'print("CPython WASM build OK!")' | \
wasmtime run --allow-precompiled --dir /tmp \
    --env PYTHONHOME="$OUT_DIR" \
    "$OUT_DIR/python.cwasm" -c "import math, json, re; print('math.factorial(5):', math.factorial(5)); print('CPython WASM build OK!')"

echo "==> Done. python.wasm and python.cwasm are ready at $OUT_DIR/"
