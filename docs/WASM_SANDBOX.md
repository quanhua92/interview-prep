# WASM Code Execution Sandbox

Benchmarks, architecture, and implementation details for the WebAssembly (WASM) code execution sandbox. Replaces the bubblewrap approach described in [MULTI_USER_DEPLOYMENT.md](./MULTI_USER_DEPLOYMENT.md).

## Status

**Implemented and wired end-to-end.** Code runs inside wasmtime, not native subprocess.

- 5 languages supported: C, C++, Rust, JavaScript, Python
- `run.py` calls `wasm_runner` when `wasm_sandbox_active()`, falls back to native runners otherwise
- Stub detection (`abort()`, `todo!()`, `NotImplementedError`) works in WASM path
- All 5 languages compile and run successfully via WASM in Docker (40/40 tests pass)
- MD5-based `.wasm` cache avoids recompiling identical source
- `WASM_SANDBOX=auto` enables WASM when wasmtime is available, falls back to native otherwise
- All toolchain paths configurable via `.env` (see [Configuration](#configuration))

## Why WASM over bubblewrap

The bwrap approach requires `--userns=host` + `seccomp=unconfined` on the outer Docker container, which weakens Docker's security. WASM eliminates this entirely — no special Docker flags, no kernel escape surface, works on every OS.

| | bwrap | WASM (wasmtime) |
|---|---|---|
| Docker flags needed | `--userns=host`, `seccomp=unconfined`, `apparmor=unconfined` | **None** |
| Kernel escape surface | Full kernel (zero-day → host compromise) | WASM runtime bug (no kernel access) |
| Platform compatibility | Linux only | Everywhere (macOS, Windows, Linux) |
| Docker Desktop support | Falls back to no sandbox | **Full sandbox** |
| Resource limits | `setrlimit` (approximate, OS-enforced) | Fuel + hard memory cap (runtime-enforced, deterministic) |

## Benchmarks (Apple M4, macOS)

### Compilation: user code → .wasm

| Language | File | Native compile | WASM compile | Overhead | .wasm size |
|---|---|---|---|---|---|
| C | p003 (86 lines) | 0.04s | 0.06s | 1.5x | 102K |
| C++ | p003 (87 lines, `unordered_map`) | 0.18s | 0.34s | 1.9x | 199K |
| C++ | p483 (97 lines, complex) | — | 0.38s | — | 624K |
| Rust | p167 (67 lines, 2-step: rstest lib + problem) | 0.06s | 0.07s | 1.2x | 1.9M |
| Rust | p483 (complex) | 0.11s | 0.11s | 1.0x | — |
| JS | p003 (77 lines, via Javy/QuickJS) | 0s (interpreted) | ~1.0s | N/A | 1.2M |
| Python | (no compile — pre-built interpreter) | — | — | — | 25MB |

### Execution: .wasm via wasmtime

| Language | Native execute | WASM execute |
|---|---|---|
| C | <10ms | <10ms |
| C++ | <10ms | <10ms |
| Rust | <10ms | <10ms |
| JS (node) | ~10ms | ~10ms |
| Python (CPython) | ~20ms | ~180ms |

Python is 9x slower due to CPython WASM startup overhead (~170ms for interpreter init). Execution of actual test code is fast — the bottleneck is loading the 25MB `python-3.12.0.wasm` binary.

### Resource limits (all verified working)

| Limit | wasmtime flag | Tested |
|---|---|---|
| CPU (instruction count) | `-W fuel=2_000_000_000` | Infinite loop killed ("all fuel consumed") |
| Wall-clock timeout | `-W timeout=5s` | Infinite loop killed ("interrupt") |
| Memory cap | `-W max-memory-size=33554432` | MemoryError raised |

Python requires ~1.5B fuel for CPython startup + import + solve a simple problem.

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│  Docker Container (default security, no special flags)  │
│                                                          │
│  FastAPI Server                                          │
│  ├── web.py: load_dotenv() → env vars set               │
│  ├── src/runners/wasm_runner.py: reads env vars          │
│  │                                                       │
│  │  /api/run (C)   → wasm_runner.compile_to_wasm()      │
│  │                  → wasm_runner.run_wasm()             │
│  │  /api/run (C++) → wasm_runner.compile_to_wasm()      │
│  │                  → wasm_runner.run_wasm()             │
│  │  /api/run (Rust) → wasm_runner.compile_to_wasm()      │
│  │                  → wasm_runner.run_wasm()             │
│  │  /api/run (JS)   → wasm_runner.compile_to_wasm()      │
│  │                  → wasm_runner.run_wasm()             │
│  │  /api/run (Python) → wasm_runner.run_python_wasm()   │
│  │                                                       │
│  No bwrap. No --userns=host. No seccomp=unconfined.      │
│  Compilation: Docker's default seccomp provides isolation  │
│  Execution: wasmtime enforces fuel, memory, timeout       │
└─────────────────────────────────────────────────────────┘
```

Two-layer model:

```
Outer layer (Docker, default flags):  filesystem + process + network isolation from host
                                      ↑ Docker's default seccomp blocks ~50 dangerous syscalls
                                      ↑ No special flags needed
Inner layer (wasmtime):              WASM sandbox for code execution
                                      ↑ No filesystem access unless --dir
                                      ↑ No network (WASI has no networking)
                                      ↑ Fuel-based CPU limit, hard memory cap
                                      ↑ Works on every OS, no kernel exploit surface
```

### Module structure

```
src/runners/wasm_runner.py
├── WASM_SANDBOX        → "auto" | "0" | "1"  (from env)
├── wasm_available()     → shutil.which(wasmtime)
├── wasm_sandbox_active() → is WASM sandbox actually active?
├── compile_to_wasm(src, lang) → Path  (with MD5 cache)
│   ├── _compile_c()     → clang --target=wasm32-wasip1
│   ├── _compile_cpp()   → clang++ --target=wasm32-wasip1 -fno-exceptions
│   ├── _compile_rust()  → rustc --target wasm32-wasip1 (with rstest rlib)
│   └── _compile_js()    → javy build (with process.exit stripping)
├── run_wasm(wasm_path, source_dir) → dict
│   └── wasmtime run --dir ... -W fuel=... -W timeout=... -W max-memory-size=...
└── run_python_wasm(source, project_root) → dict
    └── wasmtime run --dir ... --env PYTHONPATH=... python-3.12.0.wasm -- script.py

run.py
├── wasm_sandbox_active()? → use wasm_runner (compile + run in wasmtime)
│   └── stub detection: abort(), todo!(), NotImplementedError → SKIP
└── fallback → native runners (CRunner, CppRunner, RustRunner, JSRunner, subprocess)
```

## Configuration

All toolchain paths are configurable via environment variables with sensible defaults (container paths). `.env` is loaded by `python-dotenv` at `web.py` import time, before `wasm_runner.py` evaluates its module-level constants.

See [`.env.example`](../.env.example):

| Variable | Default | Purpose |
|----------|---------|---------|
| `WASM_SANDBOX` | `auto` | `auto` = WASM if available, else native; `0` = force native; `1` = force WASM |
| `WASMTIME_BIN` | `wasmtime` | Path to wasmtime binary |
| `WASI_SDK_CLANG` | `/opt/wasi-sdk/bin/clang` | wasi-sdk clang for C |
| `WASI_SDK_CLANGPP` | `/opt/wasi-sdk/bin/clang++` | wasi-sdk clang++ for C++ |
| `WASI_SDK_SYSROOT` | `/opt/wasi-sdk/share/wasi-sysroot` | wasi-sdk sysroot |
| `JAVY_BIN` | `javy` | Javy binary for JS → WASM |
| `PYTHON_WASM` | `/opt/python.wasm` | Python WASM interpreter |
| `WASM_CACHE_DIR` | `/tmp/wasm-cache` | Directory for compiled `.wasm` cache |

Exported env vars take precedence over `.env` file values (uses `os.environ.get()`, not `setdefault`).

### macOS local development example

```env
WASM_SANDBOX=auto
WASI_SDK_CLANG=/tmp/wasi-sdk-33.0-arm64-macos/bin/clang
WASI_SDK_CLANGPP=/tmp/wasi-sdk-33.0-arm64-macos/bin/clang++
WASI_SDK_SYSROOT=/tmp/wasi-sdk-33.0-arm64-macos/share/wasi-sysroot
JAVY_BIN=/tmp/javy
PYTHON_WASM=/tmp/python-3.12.0.wasm
```

## Per-Language Details

### C → WASM

Toolchain: wasi-sdk (clang targeting `wasm32-wasip1`)

```bash
clang --target=wasm32-wasip1 --sysroot=/opt/wasi-sdk/share/wasi-sysroot \
  -O2 -Wall -Wextra -Isrc/runners source.c -o solution.wasm -lm
wasmtime run -W fuel=2_000_000_000 -W timeout=120s solution.wasm
```

The existing `ctest.h` test harness uses standard C (`printf`, `assert`-like macros, `abort()`). All work with wasi-libc. No changes to solution files needed.

### C++ → WASM

Toolchain: wasi-sdk (clang++ targeting `wasm32-wasip1`)

```bash
clang++ --target=wasm32-wasip1 --sysroot=/opt/wasi-sdk/share/wasi-sysroot \
  -O2 -Wall -Wextra -fno-exceptions -Isrc/runners source.cpp -o solution.wasm
wasmtime run -W fuel=2_000_000_000 -W timeout=120s solution.wasm
```

Requires `-fno-exceptions`. The existing `cpptest.h` test harness uses wasi-libc++. Solution files using `unordered_map`, `string`, `vector`, `algorithm` all work. Files using `std::optional`, `std::variant`, or exception-based error handling need `-fno-exceptions` stubs.

### Rust → WASM

Toolchain: rustup `wasm32-wasip1` target

```bash
rustc --edition 2024 -O --target wasm32-wasip1 \
  --extern rstest=librstest.rlib source.rs -o solution.wasm
wasmtime run -W fuel=2_000_000_000 -W timeout=120s solution.wasm
```

Two-step compilation (same as native):
1. Compile `src/runners/rstest.rs` → `librstest.rlib` (once, cached in memory)
2. Compile problem file → `.wasm` (cached to disk by MD5)

The `rstest.rs` test harness (`run_tests!` macro, `TestCase` struct, `print_arr`) works unchanged on `wasm32-wasip1`. Solution files need no modifications.

`std::process::exit()` works in WASI — no patching needed.

### JavaScript → WASM

Toolchain: [Javy](https://github.com/bytecodealliance/javy) v8.1.1 (Shopify/Bytecode Alliance)

```bash
javy build -o solution.wasm source.mjs
wasmtime run -W fuel=2_000_000_000 -W timeout=120s solution.wasm
```

Javy compiles JS to WASM using QuickJS as the embedded runtime. `console.log()` works and produces stdout. `process.exit()` is stripped by `_strip_process_exit()` before compilation — it crashes in QuickJS/WASM (no `process` global).

Compilation is ~1 second (QuickJS parse + bytecode emit). Static linking produces a 1.2MB `.wasm` binary.

### Python → WASM

Toolchain: [VMware WLR](https://github.com/vmware-labs/webassembly-language-runtimes) `python-3.12.0.wasm`

**Not Pyodide.** Pyodide's `python.wasm` is built via Emscripten (`wasm32-emscripten`) and requires a JS runtime to bootstrap. It cannot run via `wasmtime` CLI.

VMware WLR provides CPython 3.12.0 compiled to `wasm32-wasip1` via CPython's own `Tools/wasm/wasi.py` build script. It's a standalone WASI application — no JS, no Emscripten.

```bash
wasmtime run -W fuel=2_000_000_000 -W timeout=120s \
  --dir /app python-3.12.0.wasm -- /app/tier1/sliding_window/solutions/p003.py
```

Binary: 25MB (self-contained with full stdlib). No compilation step — the interpreter is pre-built.

**Stdlib coverage (all modules used by this project):**

| Module | Available? | Used by |
|---|---|---|
| `dataclasses` | OK | `Problem`, `TestCase` base class |
| `typing` | OK | type annotations |
| `pathlib` | OK | `Problem` base class |
| `functools` | OK | timer decorator |
| `contextlib` | OK | context managers |
| `collections` | OK | `Counter`, `defaultdict`, `deque` |
| `itertools` | OK | iterators |
| `bisect` | OK | binary search |
| `heapq` | OK | priority queues |
| `random` | OK | random module |
| `re` | OK | regex |
| `json` | OK | JSON |
| `math` | OK | math |
| `sqlite3` | OK | sqlite3 |
| `threading` | OK | threading |
| `multiprocessing` | **MISSING** | not needed |

The existing `src/utils/` framework (`Problem`, `TestCase`, `ListNode`, `TreeNode`) works unmodified inside WASM Python. Solution files need zero changes.

**Note:** The project is being archived. Development continues at [webassemblylabs/webassembly-language-runtimes](https://github.com/webassemblylabs/webassembly-language-runtimes). For newer Python versions (3.13+), consider building from source using CPython's `Tools/wasm/wasi.py` or using [Wasmer's Python](https://wasmer.io/posts/python-on-the-edge-powered-by-webassembly).

## Security Properties

The WASM sandbox **cannot**:

| Attack | Protection |
|---|---|
| Read other users' files | No filesystem access unless explicitly `--dir` |
| Network access | WASI has no networking (no socket syscalls) |
| Kernel escape | WASM runs in user-space — no kernel, no syscalls |
| Fork bomb | WASM is single-threaded, no `fork()` |
| Memory exhaustion | `-W max-memory-size=256MB` (hard cap) |
| Infinite loops | `-W timeout=120s` (wall-clock) or `-W fuel=N` (instruction count) |
| CPU exhaustion | `-W fuel=2_000_000_000` (deterministic instruction limit) |

## Dockerfile (WASM toolchain)

```dockerfile
FROM python:3.14-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc g++ rustc nodejs curl ca-certificates xz-utils \
  && rm -rf /var/lib/apt/lists/*

# wasmtime runtime
RUN curl https://wasmtime.dev/install.sh -sSf | bash
ENV PATH="/root/.wasmtime/bin:${PATH}"

# wasi-sdk for C/C++ → WASM compilation (multi-arch)
ARG WASI_SDK_VERSION=33
RUN ARCH=$(case "$(uname -m)" in x86_64) echo "x86_64" ;; aarch64|arm64) echo "arm64" ;; esac) && \
    curl -L "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-${WASI_SDK_VERSION}/wasi-sdk-${WASI_SDK_VERSION}.0-${ARCH}-linux.tar.gz" \
    | tar xz -C /opt/ && \
    ln -s /opt/wasi-sdk-${WASI_SDK_VERSION}.0-${ARCH}-linux /opt/wasi-sdk

# Rust wasm32-wasip1 target
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y --default-toolchain stable --profile minimal \
    && /root/.cargo/bin/rustup target add wasm32-wasip1
ENV PATH="/root/.cargo/bin:${PATH}"

# Javy for JS → WASM (multi-arch)
ARG JAVY_VERSION=8.1.1
RUN ARCH=$(case "$(uname -m)" in x86_64) echo "x86_64" ;; aarch64|arm64) echo "arm" ;; esac) && \
    curl -L "https://github.com/bytecodealliance/javy/releases/download/v${JAVY_VERSION}/javy-${ARCH}-linux-v${JAVY_VERSION}.gz" \
    | gunzip > /usr/local/bin/javy && chmod +x /usr/local/bin/javy

# Python WASM (CPython 3.12 for WASI)
ARG PYTHON_WASM_VERSION=3.12.0
RUN curl -L "https://github.com/vmware-labs/webassembly-language-runtimes/releases/download/python%2F${PYTHON_WASM_VERSION}%2B20231211-040d5a6/python-${PYTHON_WASM_VERSION}.wasm" \
    -o /opt/python.wasm

COPY --from=ghcr.io/astral-sh/uv:latest /uv /usr/local/bin/uv

WORKDIR /app

COPY pyproject.toml uv.lock ./
RUN uv sync --frozen --no-dev

COPY . .

EXPOSE 8888

CMD ["uv", "run", "python", "main.py", "start"]
```

Key differences from the pre-WASM Dockerfile:
- `xz-utils` added (required for wasmtime `.tar.xz` extraction)
- wasmtime installed via official install script, added to `PATH`
- wasi-sdk downloaded with multi-arch detection (`x86_64` / `arm64`)
- rustup installed (not just system `rustc`) for `wasm32-wasip1` target
- Javy downloaded with multi-arch detection
- python-3.12.0.wasm placed at `/opt/python.wasm`
- No bubblewrap, no `--privileged`, no special Docker flags

No `--privileged`. No Docker socket. No `--userns=host`. No `seccomp=unconfined`. Just `docker compose up`.

## Comparison: bwrap vs WASM

| | bwrap | WASM |
|---|---|---|
| Docker flags | `--userns=host` + `seccomp=unconfined` | **None** |
| Linux only | Yes (Docker Desktop = no sandbox) | **No (works everywhere)** |
| Kernel exploit surface | Yes (bwrap escape → host) | **No (WASM is user-space)** |
| Cross-user data leak | `--ro-bind /app /app` exposes all users | **No FS access by default** |
| CPU limiting | `setrlimit RLIMIT_AS` (approximate) | **Fuel (deterministic)** |
| Memory limiting | `setrlimit RLIMIT_AS` (approximate) | **Hard cap** |
| C compile + run | ~50ms + native speed | 60ms + native speed |
| C++ compile + run | ~50ms + native speed | 340ms + native speed |
| Rust compile + run | ~50ms + native speed | 70ms + native speed |
| JS run | ~10ms (node) | ~1s compile + ~10ms |
| Python run | ~20ms (CPython) | **~180ms** (CPython WASM startup) |
| Network from code | Outer Docker network | **Blocked** |
