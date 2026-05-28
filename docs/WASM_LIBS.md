# WASM Shared Libraries (`src/wasm_libs/`)

Per-language I/O libraries used by all 144 solution files. Every solution reads stdin via these libraries, calls `solve()`, and writes stdout — the judge in `test_runners/` validates the output.

## Architecture

```
src/
  wasm_libs/
    __init__.py
    c/
      io.h      — read_ints, read_line, read_int, write_int, write_ints, write_string, write_bool
      io.c      — implementations
    cpp/
      io.h      — C++ versions (std::vector, std::string)
      io.cpp    — implementations
    rs/
      lib.rs    — all IO functions + re-exports (read_ints, write_int, etc.)
    js/
      io.mjs       — QuickJS-NG WASI (qjs:std module)
      io_node.mjs  — Node.js (fs.readFileSync) — used by native_runner.py
    py/
      io.py     — read_ints, read_line, read_int, write_int, write_ints, write_matrix, write_string, write_bool
  runners/
    wasm_runner.py    — compile + execution for WASM sandbox path
    native_runner.py  — compile + execution for native fallback path
    base_runner.py
    c_runner.py       — legacy, not used by run.py
    cpp_runner.py     — legacy
    rust_runner.py    — legacy
    js_runner.py      — legacy
    ctest.h           — legacy C test harness
    cpptest.h         — legacy C++ test harness
    rstest.rs         — legacy Rust test harness
```

| Layer | Location | Runs where |
|-------|----------|------------|
| Host | `src/runners/` | Python process (orchestrator) |
| WASM | `src/wasm_libs/` | Inside wasmtime sandbox (or native) |

## Communication: stdin/stdout Commands

All solutions are standalone programs that communicate through stdin/stdout:

| Channel | Purpose | Convention |
|---------|---------|------------|
| **stdin** | Problem input (from judge) | Structured text |
| **stdout** | Solution output | Structured text (answer only) |
| **stderr** | Debug logs | Free-form, ignored on PASS |
| **exit code** | Status | `0` = PASS, nonzero = FAIL |

### Why Commands (not Reactors or Components)

| | Command | Reactor | Component |
|---|---------|---------|-----------|
| Entry point | `_start` | exported functions | WIT interfaces |
| Stdin/stdout I/O | Yes | No | No |
| Language support | All 5 langs | All 5 langs | Rust mostly |
| Complexity | Low (text I/O) | Medium (memory mgmt) | High (tooling immature) |

Every language supports stdin/stdout natively. Reactors require manual memory pointer juggling (WASM only has `i32`/`i64`/`f32`/`f64`). Components fix this with WIT but tooling is immature. Commands avoid all of this.

## Input Formats

**Integers (space-separated):**
```
3 9 20 -1 -1 15 7
```

**String (single line):**
```
abcabcbb
```

**Matrix (first line = rows cols, then rows):**
```
3 3
1 2 3
4 5 6
7 8 9
```

**Graph (first line = node count, then edges):**
```
5
0 1
1 2
0 2
```

**Tree (level-order, -1 = null):**
```
3 9 20 -1 -1 15 7
```

**Linked list (space-separated, -1 = end):**
```
1 2 3 4 5 -1
```

**Multiple args (line-separated):**
```
3
9
20
```

## Output Formats

**Single int:** `42\n`
**Array:** `1 2 3\n`
**Matrix:** `1 2\n3 4\n`
**Bool:** `true\n` or `false\n`
**String:** `result_string\n`

## Communication Flow

```
Host Python (wasm_runner.py / native_runner.py)
  |
  |  writes input to stdin (from test_runners/pXXX.py)
  v
wasmtime run solution.wasm     (or native binary)
  |
  |  stdin  -> solution reads input
  |  solve()
  |  stdout -> answer
  |  exit   -> 0/1
  v
Host Python (subprocess.run)
  |  result.stdout    -> the answer
  |  result.returncode -> pass/fail
```

## Per-Language IO Reference

### Python (`wasm_libs/py/io.py`)

```python
from src.wasm_libs.py.io import *

def solve(param: type) -> type:
    ...

if __name__ == "__main__":
    data = read_ints()
    result = solve(data)
    write_int(result)
```

Available functions: `read_line() -> str`, `read_ints() -> list[int]`, `read_int() -> int`, `write_int(val)`, `write_ints(arr)`, `write_string(s)`, `write_bool(b)`, `write_matrix(mat)`.

**WASM execution:** `wasmtime run python.wasm -- script.py` (no compilation, PYTHONPATH set to project root).

**Native execution:** `python3 script.py` (PYTHONPATH set to project root).

### C (`wasm_libs/c/`)

```c
#include "io.h"
#include <stdlib.h>

int* solve(const int* nums, int n, int target, int* ret_size) {
    ...
}

int main(void) {
    int n;
    int* nums = read_ints(&n);
    int target = read_int();
    int ret_size;
    int* result = solve(nums, n, target, &ret_size);
    write_ints(result, ret_size);
    free(nums);
    free(result);
    return 0;
}
```

Available functions: `read_ints(int* count) -> int*`, `read_int() -> int`, `read_line() -> char*`, `write_int(int)`, `write_ints(int*, int)`, `write_string(const char*)`, `write_bool(int)`.

**WASM compile:**
```
clang --target=wasm32-wasip1 --sysroot=... -O2 -Wall -Wextra -Isrc/wasm_libs/c source.c src/wasm_libs/c/io.c -o out.wasm -lm
```

**Native compile:**
```
gcc -O2 -Wall -Wextra -Isrc/wasm_libs/c source.c src/wasm_libs/c/io.c -o out -lm
```

### C++ (`wasm_libs/cpp/`)

```cpp
#include "io.h"
#include <vector>

std::vector<int> solve(const std::vector<int>& nums, int target) {
    ...
}

int main(void) {
    std::vector<int> nums = read_ints();
    int target = read_int();
    write_ints(solve(nums, target));
    return 0;
}
```

Available functions: `read_ints() -> std::vector<int>`, `read_int() -> int`, `read_line() -> std::string`, `write_int(int)`, `write_ints(const vector<int>&)`, `write_string(const string&)`, `write_bool(bool)`.

**WASM compile:**
```
clang++ --target=wasm32-wasip1 --sysroot=... -O2 -Wall -Wextra -fno-exceptions -Isrc/wasm_libs/cpp source.cpp src/wasm_libs/cpp/io.cpp -o out.wasm
```

**Native compile:**
```
g++ -O2 -Wall -Wextra -Isrc/wasm_libs/cpp source.cpp src/wasm_libs/cpp/io.cpp -o out
```

**Note:** C++ requires `-fno-exceptions` for WASI.

### Rust (`wasm_libs/rs/lib.rs`)

```rust
use wasm_libs::*;

fn solve(numbers: &[i32], target: i32) -> Vec<i32> {
    ...
}

fn main() {
    let numbers = read_ints();
    let target = read_int();
    write_ints(&solve(&numbers, target));
    std::process::exit(0);
}
```

Available functions: `read_ints() -> Vec<i32>`, `read_line() -> String`, `read_int() -> i32`, `write_int(i32)`, `write_ints(&[i32])`, `write_string(&str)`, `write_bool(bool)`.

**WASM compile (two-step):**
```python
# Step 1: compile wasm_libs as rlib (cached)
rustc --edition 2024 -O --target wasm32-wasip1 src/wasm_libs/rs/lib.rs --crate-type lib --crate-name wasm_libs -o lib.rlib

# Step 2: compile solution linking wasm_libs
rustc --edition 2024 -O --target wasm32-wasip1 source.rs --extern wasm_libs=lib.rlib -o out.wasm
```

**Native compile (same two-step, no --target):**
```python
# Step 1: compile wasm_libs as rlib (cached)
rustc --edition 2024 -O src/wasm_libs/rs/lib.rs --crate-type lib --crate-name wasm_libs -o lib.rlib

# Step 2: compile solution linking wasm_libs
rustc --edition 2024 -O source.rs --extern wasm_libs=lib.rlib -o out
```

### JavaScript (`wasm_libs/js/`)

```js
import { readInts, writeInts } from '../../wasm_libs/js/io.mjs';

function solve(numbers, target) {
    ...
}

const numbers = readInts();
const target = readInt();
writeInts(solve(numbers, target));
```

Available functions: `readLine()`, `readInts()`, `readInt()`, `writeInt(val)`, `writeInts(arr)`, `writeString(s)`, `writeBool(b)`.

No compilation step. The import line is stripped at runtime and `io.mjs` content is prepended to the solution source.

**WASM execution:** `wasmtime run --dir ... --module quickjs.wasm script.mjs` (QuickJS-NG WASI, uses `qjs:std` module for stdio).

**Native execution:** `node script.mjs` (uses `io_node.mjs` which reads stdin via `fs.readFileSync(0)`).

## WASM Module Types Reference

| Type | Entry | Use case |
|------|-------|----------|
| **Command** | `_start` | Standalone app, stdin/stdout/stderr/exit code |
| **Reactor** | exported funcs | Library, direct function calls via pointers |
| **Component** | WIT interfaces | Language-agnostic lib, typed structs |

This project uses **Commands** — the only module type that works across all 5 languages with minimal tooling.
