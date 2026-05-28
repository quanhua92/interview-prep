# WASM Judge System

Architecture for running coding problems across 5 languages using a Python-driven judge that tests solutions via stdin/stdout.

## Overview

```
Python Judge (run.py)
  |
  |  For each problem:
  |    1. Load test_runners/pXXX.py  ->  test_cases, to_stdin(), check_stdout()
  |    2. Find solution file (problems/ or solutions/)
  |    3. Detect stub (abort/todo!/throw/raise) -> SKIP without compiling
   |    4. Compile to .wasm (or run python.wasm)
  |    5. For each TestCase:
  |       to_stdin(tc.input) --stdin--> [wasmtime run | python3] --stdout--> check_stdout(stdout, tc.expected)
  |                                                                          |
  |                                                                     PASS / FAIL
```

**One judge. Five languages. Per-problem IO contracts.**

The judge system is the **default and only** execution path in `run.py`. Patterns without `test_runners/` are rejected with an error.

## Why This Architecture

| Before | After |
|--------|-------|
| Each solution has 30-50 lines of test boilerplate in main() | main() is 4-5 lines: read stdin, call solve, write stdout |
| Test cases duplicated across 5 languages (576 copies) | Test cases defined ONCE in test_runners/ |
| Test logic inside WASM (can't see what failed) | Test logic in Python (full error messages, flexible comparison) |
| Per-language test runners (ctest.h, cpptest.h, rstest.rs, inline JS) | ONE Python judge for all languages |
| C uses RUN_TESTS macro, C++ uses custom struct loop, Rust uses run_tests!, JS uses inline loop | All use the same judge |

## Folder Structure

```
tier1_foundation/two_pointers/
  problems/              # User workspace (write code here)
    p011_container_water.c
    p011_container_water.cpp
    p011_container_water.rs
    p011_container_water.mjs
    p011_container_water.py
    ...
  solutions/             # Predefined answers (hints, verified correct)
    p011_container_water.c       <- LeetCode solve() + tiny stdin/stdout main()
    p011_container_water.cpp
    p011_container_water.rs
    p011_container_water.mjs
    p011_container_water.py
    ...
  test_runners/          # Judge for each problem (single source of truth)
    __init__.py
    p011_container_water.py      <- test_cases + to_stdin() + check_stdout()
    p015_three_sum.py
    p167_two_sum.py
    ...

src/
  wasm_libs/             # WASM-side IO building blocks
    c/   io.h, io.c
    cpp/ io.h, io.cpp
    rs/  lib.rs
    js/  io.mjs
    py/  io.py
  utils/
    judge_base.py         # JudgeBase class with common IO helpers
  runners/
    wasm_runner.py        # Compile + execution + stdin piping (judge + legacy)
```

## test_runner Contract

Each `test_runners/pXXX.py` defines a `JudgeBase` subclass:

```python
from src.utils.judge_base import JudgeBase, register

class P011ContainerWater(JudgeBase):
    name = "11. Container With Most Water"
    test_cases = [
        TestCase(input=[1, 8, 6, 2, 5, 4, 8, 3, 7], expected=49, label="example 1"),
        TestCase(input=[1, 1], expected=1, label="example 2"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int(stdout) == tc_expected

register(P011ContainerWater)
```

### Required methods

| Method | Purpose | Must override |
|--------|---------|:---:|
| `name` | Problem title for display | Yes |
| `test_cases` | `list[TestCase]` | Yes |
| `to_stdin(tc_input)` | Python object -> stdin text | Yes |
| `check_stdout(stdout, expected)` | Compare stdout with expected | Yes |

### JudgeBase shared helpers

```python
# Serializers (use in to_stdin)
serialize_int_array(arr) -> "1 8 6 2\n"
serialize_int_matrix(mat) -> "3\n1 2 3\n4 5 6\n"
serialize_string(s) -> "abc\n"
serialize_int(n) -> "42\n"
serialize_bool(b) -> "true\n"
serialize_multi(*args) -> line-separated args

# Parsers (use in check_stdout)
parse_int(stdout) -> 42
parse_int_array(stdout) -> [1, 2, 3]
parse_int_matrix(stdout) -> [[1,2],[3,4]]
parse_string(stdout) -> "abc"
parse_bool(stdout) -> True
```

### Example: complex problem (3Sum, returns matrix)

```python
class P015ThreeSum(JudgeBase):
    name = "15. 3Sum"
    test_cases = [
        TestCase(input=[-1,0,1,2,-1,-4], expected=[[-1,-1,2],[-1,0,1]]),
        TestCase(input=[0,1,1], expected=[]),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_int_array(tc_input)

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        lines = [l.strip() for l in stdout.strip().split("\n") if l]
        got = sorted(sorted(map(int, l.split())) for l in lines)
        exp = sorted(sorted(t) for t in tc_expected)
        return got == exp
```

### Example: multi-arg problem (Two Sum, takes array + target)

```python
class P167TwoSum(JudgeBase):
    name = "167. Two Sum II - Input Array Is Sorted"
    test_cases = [
        TestCase(input=([2,7,11,15], 9), expected=[1,2], label="example 1"),
    ]

    def to_stdin(self, tc_input) -> str:
        return self.serialize_multi(
            self.serialize_int_array(tc_input[0]),
            self.serialize_int(tc_input[1]),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_int_array(stdout) == tc_expected
```

## Solution File Structure

Each solution is a LeetCode-style function/class + a tiny main() bridge.

### C

```c
#include "io.h"

int maxArea(int *height, int n) {
    int left = 0, right = n - 1;
    int max_area = 0;
    while (left < right) {
        int h = height[left] < height[right] ? height[left] : height[right];
        int area = h * (right - left);
        if (area > max_area) max_area = area;
        if (height[left] < height[right]) left++;
        else right--;
    }
    return max_area;
}

int main(void) {
    int n;
    int *height = read_ints(&n);
    write_int(maxArea(height, n));
    free(height);
    return 0;
}
```

### C++

```cpp
#include "io.h"

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int max_area = 0;
        while (left < right) {
            int h = std::min(height[left], height[right]);
            max_area = std::max(max_area, h * (right - left));
            if (height[left] < height[right]) left++;
            else right--;
        }
        return max_area;
    }
};

int main() {
    auto height = read_ints();
    write_int(Solution{}.maxArea(height));
}
```

### Rust

```rust
use wasm_libs::io::{read_ints, write_int};

impl Solution {
    pub fn max_area(height: &[i32]) -> i32 {
        let (mut left, mut right) = (0, height.len() - 1);
        let mut max_a = 0;
        while left < right {
            let h = height[left].min(height[right]);
            max_a = max_a.max(h * (right - left) as i32);
            if height[left] < height[right] { left += 1; } else { right -= 1; }
        }
        max_a
    }
}

fn main() {
    let height = read_ints();
    write_int(Solution::max_area(&height));
}
```

### JavaScript

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

### Python

```python
from src.wasm_libs.py.io import read_ints, write_int

def max_area(height):
    left, right = 0, len(height) - 1
    max_a = 0
    while left < right:
        h = min(height[left], height[right])
        max_a = max(max_a, h * (right - left))
        if height[left] < height[right]: left += 1
        else: right -= 1
    return max_a

if __name__ == "__main__":
    write_int(max_area(read_ints()))
```

## wasm_libs IO Reference

### C (wasm_libs/c/io.h)

```c
int  *read_ints(int *count);          // "1 8 6 2\n" -> [1,8,6,2], *count=4
char *read_line(void);                 // reads one line from stdin
void write_int(int val);               // 42 -> "42\n"
void write_ints(int *arr, int n);     // [1,2,3] -> "1 2 3\n"
void write_string(const char *s);      // "abc" -> "abc\n"
void write_bool(int b);                // 1 -> "true\n", 0 -> "false\n"
```

### C++ (wasm_libs/cpp/io.h)

```cpp
std::vector<int> read_ints();
int read_int();
std::string read_line();
void write_int(int val);
void write_ints(const std::vector<int>& arr);
void write_string(const std::string& s);
void write_bool(bool b);
```

### Rust (wasm_libs/rs/lib.rs, crate name: `wasm_libs`)

```rust
pub fn read_ints() -> Vec<i32>;
pub fn read_line() -> String;
pub fn write_int(val: i32);
pub fn write_ints(arr: &[i32]);
pub fn write_matrix(mat: &Vec<Vec<i32>>);
pub fn write_string(s: &str);
pub fn write_bool(b: bool);
```

### JS (wasm_libs/js/io.mjs)

Uses QuickJS-NG `qjs:std` module (`std.in.readAsString`, `std.out.puts`) for WASI compatibility.

```js
export function readInts();           // -> number[]
export function readLine();           // -> string
export function writeInt(val);        // -> prints "val\n"
export function writeInts(arr);       // -> prints "1 2 3\n"
export function writeMatrix(mat);     // -> prints each row
export function writeString(s);
export function writeBool(b);
```

### Python (wasm_libs/py/io.py)

```python
def read_ints() -> list[int]: ...
def read_line() -> str: ...
def write_int(val: int): ...
def write_ints(arr: list[int]): ...
def write_matrix(mat: list[list[int]]): ...
def write_string(s: str): ...
def write_bool(b: bool): ...
```

## Compile Pipeline

```
.c    -> wasi-sdk clang -Isrc/wasm_libs/c  src/wasm_libs/c/io.c  -> .wasm
.cpp  -> wasi-sdk clang++ -Isrc/wasm_libs/cpp  src/wasm_libs/cpp/io.cpp  -> .wasm
.rs   -> rustc --target wasm32-wasip1 --extern wasm_libs=lib.rlib  -> .wasm
.mjs  -> inline io.mjs -> wasmtime run --module quickjs.wasm
.py   -> python.wasm via wasmtime
```

## Stub Detection

Stubs are detected by scanning source text **before compiling**. Detected stubs print `[SKIP]` and are never executed.

| Language | Pattern |
|----------|---------|
| C / C++ | `abort()` |
| Rust | `todo!()` |
| JavaScript | `throw new Error("NotImplementedError")` |
| Python | `raise NotImplementedError` |

## run.py Dispatch

`run.py` is the **only** entry point. Same CLI for `web.py` compatibility.

```bash
python run.py two_pointers --solution          # Python solutions (default lang)
python run.py two_pointers --solution --lang rs  # Rust solutions
python run.py two_pointers                      # Python problem stubs
python run.py two_pointers --lang c             # C problem stubs
```

Flow:
```
run.py two_pointers --solution --lang rs
  1. Load tracker, find pattern
  2. Check test_runners/ exists (error if missing)
  3. Import all test_runners/*.py -> populate judge registry
  4. Match problem stems to judges
  5. For each file:
     a. _is_stub() -> [SKIP] (regex scan, no compile)
      b. Compile to .wasm via judge_compile_to_wasm() (or inline io.mjs + run via run_quickjs_wasm() for JS)
     c. For each TestCase:
        - stdin = judge.to_stdin(tc.input)
        - result = run_wasm(wasm_path, stdin_text=stdin)
        - passed = judge.check_stdout(result["output"], tc.expected)
     d. Print [PASS] (all tests) or [FAIL] (show failing tests)
```

## IO Protocol Reference (two_pointers POC)

| Problem | Input | stdin | stdout | Test Cases |
|---------|-------|-------|--------|:----------:|
| p011 Container Water | `int[]` | `1 8 6 2 5 4 8 3 7\n` | `49\n` | 8 |
| p015 3Sum | `int[]` | `-1 0 1 2 -1 -4\n` | `-1 -1 2\n-1 0 1\n` | 8 |
| p167 Two Sum II | `(int[], int)` | `2 7 11 15\n9\n` | `1 2\n` | 7 |
| p392 Is Subsequence | `(str, str)` | `abc\nahbgdc\n` | `true\n` | 6 |
| p475 Heaters | `(int[], int[])` | `1 2 3\n2\n` | `1\n` | 7 |
| p522 Uncommon Subseq II | `str[]` | `3\naba\ncdc\neae\n` | `3\n` | 6 |
| p524 Longest Word Dict | `(str, str[])` | `abpcplea\n4\nale\napple\nmonkey\nplea\n` | `apple\n` | 6 |
| p532 K-diff Pairs | `(int[], int)` | `3 1 4 1 5\n2\n` | `2\n` | 7 |

Multi-arg stdin: arguments are line-separated. Count-prefixed arrays (p522, p524): first line is count, followed by that many lines.

## Adding a New Problem

1. Create `test_runners/pXXX.py` with `JudgeBase` subclass + `register()`
2. Create `problems/pXXX.*` for each language (user workspace, with stub)
3. Create `solutions/pXXX.*` for each language (verified answers)
4. Each solution: LeetCode function + 4-line main() using wasm_libs IO
5. Run: `python run.py topic_name --solution` to verify

## Verified Status

| Language | Status | Toolchain |
|----------|--------|-----------|
| Python | 144/144 PASS | python.wasm via wasmtime |
| Rust | 144/144 PASS | rustc + wasmtime |
| C | 144/144 PASS | wasi-sdk + wasmtime |
| C++ | 144/144 PASS | wasi-sdk + wasmtime |
| JS | 144/144 PASS | QuickJS-NG WASI + wasmtime |

## POC Scope

All 29 topics, 144 problems verified across all 5 languages (720 solutions + 720 stubs = 1440 files).
