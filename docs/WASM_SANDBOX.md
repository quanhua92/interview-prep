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

## Benchmarks

### End-to-end: 8 problems via /api/run (two_pointers, solutions)

**macOS (Apple M4, Docker arm64-native):**

| Language | Cold (1st run) | Warm (cached) | Per problem (warm) |
|---|---|---|---|
| C | 0.77s | 0.20s | 25ms |
| C++ | 4.35s | 0.15s | 19ms |
| Rust | 1.91s | 0.16s | 20ms |
| JS (Javy dynamic) | 5.57s | 0.24s | 30ms |
| Python 3.14.5 | 4.61s | 1.61s | 201ms |

**Linux VPS (amd64, small instance):**

| Language | Cold (1st run) | Warm (cached) | Per problem (warm) |
|---|---|---|---|
| C | 1.90s | 0.22s | 27ms |
| C++ | 16.9s | 0.21s | 26ms |
| Rust | 2.70s | 0.25s | 32ms |
| JS (Javy dynamic) | 6.27s | 0.44s | 55ms |
| Python 3.14.5 | 6.79s | 3.86s | 483ms |

Cold includes first-time compilation (clang/rustc/javy) and wasmtime module compilation. Warm hits the MD5 `.wasm` cache — only `wasmtime run` on pre-compiled binaries. Python is always "cold" for interpreter startup (28MB binary load per run) — it benefits from wasmtime's own compile cache but not from our file-level cache.

### Compilation: user code → .wasm

| Language | File | Native compile | WASM compile | Overhead | .wasm size |
|---|---|---|---|---|---|
| C | p003 (86 lines) | 0.04s | 0.06s | 1.5x | 102K |
| C++ | p003 (87 lines, `unordered_map`) | 0.18s | 0.34s | 1.9x | 199K |
| C++ | p483 (97 lines, complex) | — | 0.38s | — | 624K |
| Rust | p167 (67 lines, 2-step: rstest lib + problem) | 0.06s | 0.07s | 1.2x | 1.9M |
| Rust | p483 (complex) | 0.11s | 0.11s | 1.0x | — |
| JS | p003 (77 lines, via Javy dynamic) | 0s (interpreted) | ~0.5s | N/A | ~3KB |
| Python | (no compile — pre-built interpreter) | — | — | — | 28MB |

### Execution: .wasm via wasmtime

| Language | Native execute | WASM execute |
|---|---|---|
| C | <10ms | <10ms |
| C++ | <10ms | <10ms |
| Rust | <10ms | <10ms |
| JS (node) | ~10ms | ~10ms |
| Python (CPython) | ~20ms | ~180ms |

Python is slower due to CPython WASM startup overhead (~170ms for interpreter init). Execution of actual test code is fast — the bottleneck is loading the 28MB `python.wasm` binary.

### Resource limits (all verified working)

| Limit | wasmtime flag | Tested |
|---|---|---|
| CPU (instruction count) | `-W fuel=2_000_000_000` | Infinite loop killed ("all fuel consumed") |
| Wall-clock timeout | `-W timeout=5s` | Infinite loop killed ("interrupt") |
| Memory cap | `-W max-memory-size=33554432` | MemoryError raised |

Python requires ~5B fuel for CPython 3.14 startup + import + solve a simple problem.

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
├── _get_javy_plugin()   → javy emit-plugin (once, cached as /tmp/wasm-cache/javy-plugin.wasm)
├── compile_to_wasm(src, lang) → Path  (with MD5 cache)
│   ├── _compile_c()     → clang --target=wasm32-wasip1
│   ├── _compile_cpp()   → clang++ --target=wasm32-wasip1 -fno-exceptions
│   ├── _compile_rust()  → rustc --target wasm32-wasip1 (with rstest rlib)
│   └── _compile_js()    → javy build -C dynamic=y -C plugin=... (3KB) or javy build (1.2MB fallback)
├── run_wasm(wasm_path, source_dir, preload_plugin=...) → dict
│   └── wasmtime run --preload javy-default-plugin-v3=plugin.wasm ... (JS only)
│   └── wasmtime run --dir ... -W fuel=... -W timeout=... -W max-memory-size=...
└── run_python_wasm(source, project_root) → dict
    └── wasmtime run --dir ... --env PYTHONHOME=... --env PYTHONPATH=... python.wasm -- script.py

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
| `PYTHON_WASM` | `/opt/python-wasi/python.wasm` | Python WASM interpreter binary |
| `PYTHON_WASM_HOME` | `/opt/python-wasi` | Python WASM install dir (contains `lib/python3.14/`) |
| `WASM_CACHE_DIR` | `/tmp/wasm-cache` | Directory for compiled `.wasm` cache |

Exported env vars take precedence over `.env` file values (uses `os.environ.get()`, not `setdefault`).

### macOS local development example

```env
WASM_SANDBOX=auto
WASI_SDK_CLANG=/tmp/wasi-sdk-33.0-arm64-macos/bin/clang
WASI_SDK_CLANGPP=/tmp/wasi-sdk-33.0-arm64-macos/bin/clang++
WASI_SDK_SYSROOT=/tmp/wasi-sdk-33.0-arm64-macos/share/wasi-sysroot
JAVY_BIN=/tmp/javy
PYTHON_WASM=/tmp/python-wasi/python.wasm
PYTHON_WASM_HOME=/tmp/python-wasi
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

Toolchain: [Javy](https://github.com/bytecodealliance/javy) v8.1.1 (Shopify/Bytecode Alliance), **dynamic linking**

```bash
# One-time: emit the QuickJS plugin (~870KB, cached in /tmp/wasm-cache/)
javy emit-plugin -o /tmp/javy-plugin.wasm

# Compile JS to small dynamic module (~3KB)
javy build -C dynamic=y -C plugin=/tmp/javy-plugin.wasm -o solution.wasm source.mjs

# Run via wasmtime with plugin preloaded
wasmtime run --preload javy-default-plugin-v3=/tmp/javy-plugin.wasm solution.wasm
```

**Dynamic linking** (default) produces ~3KB `.wasm` files that share one QuickJS runtime plugin. All modules compiled with the same plugin are compatible. The plugin is emitted once via `javy emit-plugin` and cached in the WASM cache directory.

Static linking (fallback, if plugin emit fails) produces ~1.2MB `.wasm` files (each bundles its own QuickJS runtime). Used as fallback only.

`console.log()` works and produces stdout. `process.exit()` is stripped by `_strip_process_exit()` before compilation — it crashes in QuickJS/WASM (no `process` global). The Javy runtime wrapper may also reference `process` internally after user code returns, but `_strip_process_exit` on user code is sufficient for correct exit codes.

Performance with dynamic linking (Docker, 8 JS problems): ~4s total (compile cache hit) vs ~23s with static linking.

### Python → WASM

Toolchain: [brettcannon/cpython-wasi-build](https://github.com/brettcannon/cpython-wasi-build) CPython 3.14.5 (WASI SDK 24)

**Not Pyodide.** Pyodide's `python.wasm` is built via Emscripten (`wasm32-emscripten`) and requires a JS runtime to bootstrap. It cannot run via `wasmtime` CLI.

**Not VMware WLR.** That project (python-3.12.0.wasm) was archived in 2024. These builds are from unmodified upstream CPython source by Brett Cannon, the CPython WASI maintainer. WASI is a Tier 2 platform in CPython 3.13+, meaning WASI breakage blocks releases.

```bash
wasmtime run -W fuel=5_000_000_000 -W timeout=120s \
  --dir /opt/python-wasi --dir /app \
  --env PYTHONHOME=/opt/python-wasi \
  --env PYTHONPATH=/app \
  /opt/python-wasi/python.wasm -- /app/tier1_foundation/two_pointers/solutions/p003.py
```

Binary: 28MB `python.wasm` + stdlib in `lib/python3.14/` (separate `.py` files, ~13MB total zip). Requires `PYTHONHOME` set to the install directory so CPython can find its stdlib. No compilation step — the interpreter is pre-built.

Fuel: ~5B needed for CPython 3.14 startup + import + solve a problem (3.12 needed ~2B).

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

**Release cadence:** Brett Cannon publishes builds within days of every CPython release (3.13.x, 3.14.x, 3.15.0 alphas). See [releases](https://github.com/brettcannon/cpython-wasi-build/releases). PEP 816 (accepted, Python 3.15+) will formalize WASI as a supported platform with locked SDK versions per release.

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
| CPU exhaustion | `-W fuel=5_000_000_000` (deterministic instruction limit) |

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

# Python WASM (CPython 3.14 for WASI via brettcannon/cpython-wasi-build)
ARG PYTHON_WASM_VERSION=3.14.5
RUN curl -L "https://github.com/brettcannon/cpython-wasi-build/releases/download/v${PYTHON_WASM_VERSION}/python-${PYTHON_WASM_VERSION}-wasi_sdk-24.zip" \
    -o /tmp/python-wasi.zip \
    && unzip -q /tmp/python-wasi.zip -d /opt/python-wasi \
    && rm /tmp/python-wasi.zip

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
- CPython 3.14.5 WASI build extracted to `/opt/python-wasi/` (brettcannon/cpython-wasi-build)
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
| JS run | ~10ms (node) | ~0.5s compile + ~0.05s run (dynamic linking) |
| Python run | ~20ms (CPython) | **~180ms** (CPython 3.14 WASM startup) |
| Network from code | Outer Docker network | **Blocked** |
