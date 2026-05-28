# WASM Shared Libraries (`wasm_libs/`)

Blueprint for shared utility libraries across all WASM languages. This replaces the current pattern where each solution file duplicates data structures, parsers, and test infrastructure.

## Problem

Currently, every solution reimplements shared utilities per language:

- **C**: `p102_level_order.c` defines its own `TreeNode`, `build_tree`, `free_tree` (lines 44-90)
- **Rust**: `p102_level_order.rs` defines its own `TreeNode`, `build_tree` (lines 45-81)
- **Python**: Uses `src/utils/data_structures.py` (`TreeNode.from_list`, `TreeNode.to_list`)
- **JS/C++**: Same duplication

Each tree problem repeats 50+ lines of boilerplate in C and Rust. This scales poorly — 40 problems x 5 languages = massive duplication.

## Architecture

```
src/
  utils/                    <- Host Python only (Problem, TestCase, testing)
  wasm_libs/                <- WASM utility libraries (one per language)
    c/
      data_structures.h     <- ListNode, TreeNode, Graph structs + declarations
      data_structures.c     <- implementations (build_tree, build_list, etc.)
      test_runner.h         <- RUN_TESTS macro, TestCase, print helpers
      test_runner.c
      io.h                  <- stdin parsing, stdout formatting
      io.c
    cpp/
      data_structures.h     <- C++ versions (std::vector, std::string)
      data_structures.cpp
      test_runner.h
      test_runner.cpp
      io.h
      io.cpp
    rs/
      data_structures.rs    <- TreeNode, ListNode, Graph + builders
      test_runner.rs        <- run_tests! macro, TestCase, print_arr
      io.rs                 <- stdin parsing, stdout formatting
    js/
      data_structures.mjs   <- TreeNode, ListNode classes + builders
      test_runner.mjs       <- test runner, assertion helpers
      io.mjs                <- stdin parsing
    py/
      data_structures.py    <- same as src/utils/data_structures.py
      test_runner.py        <- same as src/utils/problem.py
      io.py                 <- stdin parsing
  runners/                  <- Host Python code only (wasm_runner.py, c_runner.py...)
    wasm_runner.py          <- compiles solutions, linking wasm_libs
    base_runner.py
    c_runner.py
    cpp_runner.py
    rust_runner.py
    js_runner.py
```

**Two layers, no confusion:**

| Layer | Location | Runs where |
|-------|----------|------------|
| Host | `src/runners/`, `src/utils/` | Python process (orchestrator) |
| WASM | `src/wasm_libs/` | Inside wasmtime sandbox |

`src/runners/` is host code that calls `wasmtime`. `src/wasm_libs/` is code that lives *inside* the WASM sandbox and gets compiled into each solution's `.wasm`.

## WASM Commands: LeetCode-Style I/O

All WASM solutions are **Commands** (standalone binaries with `_start`). They communicate through:

| Channel | Purpose | Convention |
|---------|---------|------------|
| **stdin** | Problem input | Structured text (see formats below) |
| **stdout** | Solution output | Structured text (answer only) |
| **stderr** | Debug logs | Free-form, ignored by runner on PASS |
| **exit code** | Status | `0` = PASS, `1` = FAIL, `2` = SKIP/WIP |

### Why Commands (not Reactors or Components)

| | Command | Reactor | Component |
|---|---------|---------|-----------|
| Entry point | `_start` | exported functions | WIT interfaces |
| Stdin/stdout I/O | Yes | No | No |
| Typed cross-lang interfaces | No | Manual pointers | Yes (WIT) |
| Language support | All 5 langs | All 5 langs | Rust mostly |
| Complexity | Low (text I/O) | Medium (memory mgmt) | High (tooling immature) |

**Commands are the right choice because:**
- Every language supports stdin/stdout natively
- No memory pointer juggling (Reactor limitation)
- No immature toolchain dependency (Component limitation)
- `wasmtime run` CLI handles execution, fuel, sandboxing
- stdout/stderr/exit code map cleanly to `subprocess.run`

### Reactor and Component: Why Not

**Reactors** export functions the host calls directly. But WASM only has 4 types (`i32`, `i64`, `f32`, `f64`) — no strings, no arrays, no structs. To return a string from a Reactor:

```c
// Reactor: return a string = manual memory management
int32_t solve(int32_t* out_len) {
    const char* result = "hello";
    memcpy(output_buf, result, 5);
    *out_len = 5;
    return 0;  // pointer to output_buf in linear memory
}
```

**Components** fix this with WIT (WebAssembly Interface Types) — typed interfaces with automatic serialization. But tooling is immature: only Rust has good support, Python has none.

**Commands** avoid all this — stdin/stdout handle text naturally.

### Input Formats

Keep input formats simple — avoid JSON in C/C++. Use text formats trivial to parse with `scanf` / `split`:

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

### Output Formats

**Single int:** `42\n`
**Array:** `1 2 3\n`
**Matrix:** `1 2\n3 4\n`
**Bool:** `true\n` or `false\n`
**String:** `result_string\n`

### Communication Flow

```
Host Python (wasm_runner.py)
  |
  |  writes input to stdin (for judge mode)
  v
wasmtime run solution.wasm
  |
  |  stdin  -> solution reads input (optional, for judge mode)
  |  solve()
  |  stdout -> answer
  |  stderr -> debug logs
  |  exit   -> 0/1/2
  v
Host Python (subprocess.run)
  |  result.stdout    -> the answer
  |  result.stderr    -> debug (displayed on FAIL)
  |  result.returncode -> pass/fail/skip
```

**Two modes:**

| Mode | Input source | Test location | Current use |
|------|-------------|---------------|-------------|
| **Embedded tests** | Hardcoded in `main()` | Inside WASM | Current (all langs) |
| **Judge mode** | stdin | Host Python | Future (Phase 4) |

Currently all solutions use embedded test cases (Option A). Judge mode (stdin/stdout) is a future improvement that enables external test case injection.

## Per-Language Library Guide

### C (`wasm_libs/c/`)

**Include mechanism:** `-Isrc/wasm_libs/c` flag passed to clang

**Current compile** (`wasm_runner.py:70-81`):
```python
# Only compiles the solution file
cmd = [
    _WASI_SDK_CLANG, "--target=wasm32-wasip1", "--sysroot", _WASI_SDK_SYSROOT,
    "-O2", "-Wall", "-Wextra", "-Isrc/runners",
    str(source), "-o", str(out), "-lm",
]
```

**Updated compile** (after refactor — must also link library `.c` files):
```python
cmd = [
    _WASI_SDK_CLANG, "--target=wasm32-wasip1", "--sysroot", _WASI_SDK_SYSROOT,
    "-O2", "-Wall", "-Wextra", "-Isrc/wasm_libs/c",
    str(source),
    "src/wasm_libs/c/data_structures.c",
    "src/wasm_libs/c/test_runner.c",
    "-o", str(out), "-lm",
]
```

**Solution file:**
```c
#include "data_structures.h"
#include "test_runner.h"

int* two_sum(int* nums, int n, int target, int* ret_size) {
    // solve logic
    *ret_size = 2;
    int* result = malloc(2 * sizeof(int));
    result[0] = 0;
    result[1] = 1;
    return result;
}

int main(void) {
    TC tests[] = {
        {"example 1", (int[]){2,7,11,15}, 4, 9, (int[]){0,1}, 2},
        {"no solution", (int[]){3,3}, 2, 6, (int[]){}, 0},
    };
    RUN_TESTS("Two Sum", two_sum, tests, 2);
}
```

**data_structures.h provides:**
```c
// TreeNode
typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;
TreeNode* tree_from_array(const int* vals, int n);  // -1 = null
void tree_free(TreeNode* root);

// ListNode
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;
ListNode* list_from_array(const int* vals, int n);  // -1 = end
void list_free(ListNode* head);

// Graph (adjacency list)
typedef struct {
    int n;
    int** adj;      // adj[u] = array of neighbors
    int* adj_sizes; // adj_sizes[u] = degree of u
} Graph;
Graph* graph_from_edge_list(int n, int edges[][2], int edge_count);
void graph_free(Graph* g);
```

**test_runner.h provides:**
```c
// TestCase struct (matches current ctest.h pattern)
typedef struct {
    const char* label;
    int input_arr[30000];
    int input_arr_n;
    int target;
    int expected[30000];
    int expected_n;
} TC;

// RUN_TESTS macro
#define RUN_TESTS(name, solve_fn, tc_array, tc_count)

// Print helpers
void print_arr(const int* a, int n);
void print_matrix(int** m, int rows, int* cols);
```

**io.h provides (for future judge mode):**
```c
int* read_ints_stdin(int* count);
char* read_line_stdin(void);
int** read_matrix_stdin(int* rows, int* cols);
```

### C++ (`wasm_libs/cpp/`)

**Include mechanism:** `-Isrc/wasm_libs/cpp` flag passed to clang++

**Updated compile:**
```python
cmd = [
    _WASI_SDK_CLANGPP, "--target=wasm32-wasip1", "--sysroot", _WASI_SDK_SYSROOT,
    "-O2", "-Wall", "-Wextra", "-fno-exceptions",
    "-Isrc/wasm_libs/cpp",
    str(source),
    "src/wasm_libs/cpp/data_structures.cpp",
    "src/wasm_libs/cpp/test_runner.cpp",
    "-o", str(out),
]
```

C++ has its own headers using `std::vector`, `std::string`, `std::optional` — not `extern "C"` wrappers around the C version. This gives idiomatic C++ APIs:

```cpp
#include "data_structures.h"
#include "test_runner.h"
#include <vector>

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    return {0, 1};
}

int main() {
    std::vector<TestCase> tests = {
        {"example 1", {2,7,11,15}, 9, {0,1}},
    };
    RUN_TESTS("Two Sum", twoSum, tests);
}
```

**data_structures.h provides:**
```cpp
// TreeNode with smart pointers
struct TreeNode {
    int val;
    std::unique_ptr<TreeNode> left, right;
};
std::unique_ptr<TreeNode> tree_from_array(const std::vector<int>& vals);
// -1 or INT_MIN = null

// ListNode with smart pointers
struct ListNode {
    int val;
    std::shared_ptr<ListNode> next;
};
std::shared_ptr<ListNode> list_from_array(const std::vector<int>& vals);
// -1 = end
```

**test_runner.h provides:**
```cpp
struct TestCase {
    std::string label;
    std::vector<int> input_arr;
    int target;
    std::vector<int> expected;
};

#define RUN_TESTS(name, solve_fn, tc_array)

void print_arr(const std::vector<int>& a);
```

**Note:** C++ requires `-fno-exceptions` for WASI. Solution files using `std::optional`, `std::variant`, or exception-based error handling need workarounds.

### Rust (`wasm_libs/rs/`)

**Link mechanism:** Pre-compile as `.rlib`, link with `--extern`

The current `rstest.rs` is already compiled as a library and linked per solution. The refactor adds `data_structures.rs` to this pattern. Both can be combined into one rlib or kept separate.

**Current compile** (`wasm_runner.py:98-128`):
```python
# Step 1: compile rstest lib (cached in memory)
lib_out = _compile_rstest_lib(out.parent)  # -> librstest.rlib

# Step 2: compile solution, linking rstest
cmd = [
    "rustc", "--edition", "2024", "-O", "--target", "wasm32-wasip1",
    str(source), "--extern", f"rstest={lib_out}", "-o", str(out),
]
```

**Updated compile** (data_structures + test_runner in one rlib):
```python
# Step 1: compile wasm_libs rlib (cached)
cmd_lib = [
    "rustc", "--edition", "2024", "-O", "--target", "wasm32-wasip1",
    "src/wasm_libs/rs/data_structures.rs",
    "--crate-type", "lib", "--crate-name", "wasm_libs",
    "-o", str(lib_out),
]

# Step 2: compile solution, linking wasm_libs
cmd = [
    "rustc", "--edition", "2024", "-O", "--target", "wasm32-wasip1",
    str(source), "--extern", f"wasm_libs={lib_out}", "-o", str(out),
]
```

**Alternative:** Cargo with path dependency:
```toml
# wasm_libs/rs/Cargo.toml
[package]
name = "wasm_libs"
version = "0.1.0"
edition = "2024"

[lib]
crate-type = ["rlib"]
```

**Solution file:**
```rust
use wasm_libs::{TreeNode, tree_from_array, print_arr, run_tests, TestCase};

fn level_order(root: Option<Box<TreeNode>>) -> Vec<Vec<i32>> {
    let mut result = Vec::new();
    // ... solve logic
    result
}

fn main() {
    let tests = vec![
        TestCase::new("example 1", vec![3,9,20,i32::MIN,i32::MIN,15,7]),
    ];
    run_tests!("Binary Tree Level Order", level_order, tests);
}
```

**data_structures.rs provides:**
```rust
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}
pub fn tree_from_array(vals: &[i32]) -> Option<Box<TreeNode>>  // i32::MIN = null
pub fn tree_free(root: Option<Box<TreeNode>>)

pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}
pub fn list_from_array(vals: &[i32]) -> Option<Box<ListNode>>  // -1 = end
```

**test_runner.rs provides (replaces current rstest.rs):**
```rust
pub struct TestCase { pub label: &'static str, /* ... */ }
pub fn print_arr(arr: &[i32])

#[macro_export]
macro_rules! run_tests {
    ($name:expr, $solve_fn:ident, $tests:expr) => { ... }
}
```

### JavaScript (`wasm_libs/js/`)

**Runtime mechanism:** `io.mjs` inlined at runtime, executed by QuickJS-NG WASI interpreter

QuickJS-NG runs `.mjs` files directly via `wasmtime run --module`. The `io.mjs` import is resolved at runtime by `run_quickjs_wasm()` — it strips the import line, prepends the `io.mjs` content, and passes the combined script to `wasmtime`.

**Current compile** (`wasm_runner.py` — `run_quickjs_wasm()`):
```python
# No compilation — inline io.mjs and run directly
source_text = Path(source).read_text()
source_text = re.sub(r"import\s+.*?from\s+['\"].*io\.mjs['\"];?", "", source_text)
io_content = Path("src/wasm_libs/js/io.mjs").read_text()
combined = io_content + "\n" + source_text
tmp_script = Path(temp_dir) / "script.mjs"
tmp_script.write_text(combined)

cmd = [
    "wasmtime", "run", "--dir", str(source_dir),
    "--module", _QUICKJS_WASM, str(tmp_script),
]
```

**Solution file:**
```js
import { readInts, writeInt } from '../../wasm_libs/js/io.mjs';

function maxArea(height) {
    let left = 0, right = height.length - 1;
    let max = 0;
    while (left < right) {
        const area = Math.min(height[left], height[right]) * (right - left);
        max = Math.max(max, area);
        if (height[left] < height[right]) left++;
        else right--;
    }
    return max;
}

writeInt(maxArea(readInts()));
```

**data_structures.mjs provides:**
```js
export class TreeNode {
    constructor(val, left = null, right = null) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

export function treeFromArray(vals) {
    // vals: [3, 9, 20, null, null, 15, 7] -> TreeNode
    if (!vals || vals.length === 0 || vals[0] === null) return null;
    const root = new TreeNode(vals[0]);
    const queue = [root];
    let i = 1;
    while (queue.length > 0 && i < vals.length) {
        const node = queue.shift();
        if (i < vals.length) {
            if (vals[i] !== null) {
                node.left = new TreeNode(vals[i]);
                queue.push(node.left);
            }
            i++;
        }
        if (i < vals.length) {
            if (vals[i] !== null) {
                node.right = new TreeNode(vals[i]);
                queue.push(node.right);
            }
            i++;
        }
    }
    return root;
}

export class ListNode {
    constructor(val, next = null) {
        this.val = val;
        this.next = next;
    }
}

export function listFromArray(vals) {
    // vals: [1, 2, 3, -1] -> ListNode (null on val = -1 or end)
    if (!vals || vals.length === 0) return null;
    const head = new ListNode(vals[0]);
    let current = head;
    for (let i = 1; i < vals.length && vals[i] !== -1; i++) {
        current.next = new ListNode(vals[i]);
        current = current.next;
    }
    return head;
}
```

**Limitations:**
- No Node.js APIs (`fs`, `path`, `process`)
- `console.log()` works (maps to WASI `fd_write` via QuickJS)
- `qjs:std` module provides stdio: `std.in.getline()`, `std.out.puts()`, `std.in.readAsString()`
- ESM supported via `--module` flag

### Python (`wasm_libs/py/`)

**Include mechanism:** Standard `import` via PYTHONPATH

No compilation step — `python.wasm` runs `.py` files directly. Libraries are available via `PYTHONPATH` env var (already set in `run_python_wasm` at `wasm_runner.py:229`).

**Solution file:**
```python
from wasm_libs.py.data_structures import TreeNode
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "102. Binary Tree Level Order Traversal"
    test_cases = [
        TestCase(
            input=TreeNode.from_list([3, 9, 20, None, None, 15, 7]),
            expected=[[3], [9, 20], [15, 7]],
            label="example 1",
        ),
    ]

    def solve(self, root):
        if not root:
            return []
        result = []
        queue = [root]
        while queue:
            level_size = len(queue)
            level = []
            for _ in range(level_size):
                node = queue.pop(0)
                level.append(node.val)
                if node.left: queue.append(node.left)
                if node.right: queue.append(node.right)
            result.append(level)
        return result

if __name__ == "__main__":
    Solution().run()
```

**data_structures.py:** Same as current `src/utils/data_structures.py` (ListNode, TreeNode with `from_list`/`to_list`).

**Note:** Python solutions keep using the `Problem` class with embedded test cases. The `wasm_libs/py/` path provides data structures; the `src/utils/` path provides the test framework. This is the only language that mixes both directories.

## Adding a New Language

To add a new language (e.g., Go, Zig, Java via WASM):

### 1. Create wasm_libs

```
src/wasm_libs/
  go/
    data_structures.go
    test_runner.go
    io.go
```

Implement the same API surface:
- `TreeNode` — binary tree with `from_array` builder
- `ListNode` — linked list with `from_array` builder
- Test runner — `RUN_TESTS` equivalent or test helper functions
- IO — stdin parsing, stdout formatting

### 2. Add compiler to wasm_runner.py

```python
_COMPILE_FUNCS = {
    "c": _compile_c,
    "cpp": _compile_cpp,
    "rs": _compile_rust,
    "js": _compile_js,
    "go": _compile_go,   # new
}

_COMPILE_TIMEOUTS = {
    "c": 5,
    "cpp": 5,
    "rs": 30,
    "js": 10,
    "go": 15,            # new
}
```

Implement `_compile_go(source, out)`:
```python
def _compile_go(source: Path, out: Path) -> None:
    cmd = ["tinygo", "build", "-target=wasi", "-o", str(out), str(source)]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["go"])
    if result.returncode != 0:
        raise RuntimeError(f"Go compilation failed:\n{result.stderr}")
```

Update `compile_to_wasm()` to handle linking wasm_libs for Go if needed (TinyGo may handle module resolution natively).

### 3. Add runner

Create `src/runners/go_runner.py` following the pattern of existing runners (`c_runner.py`, `rust_runner.py`).

### 4. Update run.py

Add file extension mapping (`.go`) and runner call in the language dispatch logic.

### 5. Update Dockerfile

Install the new WASM compiler. Example for Go with TinyGo:
```dockerfile
# TinyGo for Go -> WASM
ARG TINYGO_VERSION=0.35.0
RUN ARCH=$(case "$(uname -m)" in x86_64) echo "amd64" ;; aarch64|arm64) echo "arm64" ;; esac) && \
    curl -L "https://github.com/tinygo-org/tinygo/releases/download/v${TINYGO_VERSION}/tinygo_${TINYGO_VERSION}_${ARCH}.tar.gz" \
    | tar xz -C /opt/ && \
    ln -s /opt/tinygo /usr/local/tinygo
ENV PATH="/usr/local/tinygo/bin:${PATH}"
```

## Implementation Checklist

### Phase 1: Restructure (no behavior change)

Move existing test harnesses from `src/runners/` to `src/wasm_libs/`, update compile paths.

- [ ] Create `src/wasm_libs/` directory structure (`c/`, `cpp/`, `rs/`, `js/`, `py/`)
- [ ] Move `src/runners/rstest.rs` -> `src/wasm_libs/rs/test_runner.rs`
- [ ] Move `src/runners/ctest.h` -> `src/wasm_libs/c/test_runner.h`
- [ ] Move `src/runners/cpptest.h` -> `src/wasm_libs/cpp/test_runner.h`
- [ ] Update `wasm_runner.py` `_compile_c`: `-Isrc/runners` -> `-Isrc/wasm_libs/c`
- [ ] Update `wasm_runner.py` `_compile_cpp`: `-Isrc/runners` -> `-Isrc/wasm_libs/cpp`
- [ ] Update `wasm_runner.py` `_compile_rust`: `--extern rstest=` -> `--extern wasm_libs=`, update rlib path
- [ ] Verify all existing solutions still compile and pass (no solution file changes)

### Phase 2: Extract data structures

Create shared data structure libraries by extracting common patterns from existing solutions.

- [ ] Create `wasm_libs/c/data_structures.h/.c` (TreeNode, ListNode, Graph)
- [ ] Create `wasm_libs/cpp/data_structures.h/.cpp` (TreeNode, ListNode, Graph)
- [ ] Create `wasm_libs/rs/data_structures.rs` (TreeNode, ListNode, Graph)
- [ ] Create `wasm_libs/js/data_structures.mjs` (TreeNode, ListNode classes)
- [ ] Create `wasm_libs/py/` (symlink or copy from `src/utils/data_structures.py`)
- [ ] Update `wasm_runner.py` compile commands to link `data_structures.c/.cpp`
- [ ] Update `wasm_runner.py` Rust compile to include data_structures in rlib

### Phase 3: Refactor solutions

Replace inline data structure definitions with `#include` / `use` / `import`.

- [ ] Refactor C solutions: remove inline TreeNode/ListNode, add `#include "data_structures.h"`
- [ ] Refactor C++ solutions: remove inline definitions, add `#include "data_structures.h"`
- [ ] Refactor Rust solutions: remove inline definitions, add `use wasm_libs::*`
- [ ] Refactor JS solutions: remove inline definitions, add `import` from wasm_libs
- [ ] Python solutions: no change (already use `src/utils/data_structures.py`)

### Phase 4: Standardize I/O (optional, future)

Add stdin/stdout based judge mode alongside embedded test cases.

- [ ] Create `wasm_libs/c/io.h/.c` (read_ints_stdin, read_line_stdin, read_matrix_stdin)
- [ ] Create `wasm_libs/cpp/io.h/.cpp`
- [ ] Create `wasm_libs/rs/io.rs`
- [ ] Create `wasm_libs/js/io.mjs`
- [ ] Decide on input/output format standard (see Input Formats section)
- [ ] Add judge mode to runners: pipe stdin, capture stdout, compare with expected

## WASM Concepts Reference

### Module Types

| Type | Entry | Use case | Interop |
|------|-------|----------|---------|
| **Command** | `_start` | Standalone app | stdin/stdout/stderr/exit code |
| **Reactor** | exported funcs | Library | Direct function calls via pointers |
| **Component** | WIT interfaces | Language-agnostic lib | Typed structs, auto serialization |

### Why We Use Commands

Commands are the only module type that works across all 5 languages today with minimal tooling. Reactors require manual memory management (WASM has no strings/arrays — only flat memory buffers and pointers). Components would fix this but tooling is immature (only Rust has good support).

### Ecosystem Maturity

| Tool | Status | Use when |
|------|--------|----------|
| **wasmtime CLI** | Stable | Running Commands (our current approach) |
| **wasmtime-py** | Stable | In-process WASM via Python SDK |
| **wasm-bindgen** | Stable (Rust+JS only) | Rust in browser/Node.js |
| **WASI** | Stable | File/IO/syscall sandboxing |
| **Components** | Early | Cross-lang typed interfaces (future) |
| **WIT** | Early | Interface definition language for Components |
