# API Reference

Base URL: `http://localhost:8888`

## Health

### GET /api/health

System health, sandbox status, and runtime availability.

**Response:**
```json
{
  "status": "ok",
  "sandbox": {
    "type": "wasm",
    "wasmtime_available": true,
    "sandbox_active": true
  },
  "runtimes": {
    "wasmtime": { "available": true },
    "wasi-sdk-clang": { "available": true },
    "quickjs-wasm": { "available": true },
    "cpython-wasm": { "available": true }
  }
}
```

| Field | Type | Description |
|-------|------|-------------|
| `sandbox.type` | `string` | `"wasm"` if sandbox is active, `"none (direct subprocess)"` otherwise |
| `sandbox.wasmtime_available` | `bool` | Whether `wasmtime` binary is available |
| `sandbox.sandbox_active` | `bool` | Whether `/api/run` uses WASM isolation |
| `runtimes.{name}.available` | `bool` | Whether the runtime/toolchain is installed |

---

## Tracker

### GET /api/tracker

Load the full tracker state (all sections, all items).

**Response:**
```json
{
  "patterns": [
    { "name": "sliding_window", "tier": 1, "status": "in_progress", "attempts": 3, "last_attempt": "2026-05-20" }
  ],
  "system_design": [
    { "name": "url_shortener", "status": "not_started", "attempts": 0, "last_attempt": null }
  ],
  "behavioral": [...],
  "salary_negotiation": [...],
  "cs_fundamentals": [...],
  "resume_career": [...],
  "role_specific": [...],
  "ai_assisted": [...],
  "data_analytics": [...],
  "low_level_design": [...],
  "production_engineering": [...]
}
```

| Item Field | Type | Description |
|------------|------|-------------|
| `name` | `string` | Internal name (e.g. `sliding_window`) |
| `tier` | `int \| null` | Tier 1-4 (coding patterns only) |
| `status` | `string` | `"not_started"`, `"in_progress"`, or `"completed"` |
| `attempts` | `int` | Total practice attempts |
| `last_attempt` | `string \| null` | ISO date of last attempt (e.g. `"2026-05-20"`) |

---

### POST /api/update

Update a topic's status.

**Request:**
```json
{ "name": "sliding_window", "status": "completed" }
```

| Parameter | Type | Values |
|-----------|------|--------|
| `name` | `string` | Topic name (must exist in tracker) |
| `status` | `string` | `"not_started"`, `"in_progress"`, or `"completed"` |

**Response:**
```json
{
  "ok": true,
  "section_key": "coding",
  "item": { "name": "sliding_window", "tier": 1, "status": "completed", "attempts": 4, "last_attempt": "2026-05-25" },
  "old_status": "in_progress"
}
```

Setting `"not_started"` resets attempts to 0. Setting `"completed"` increments attempts and records today's date.

**Errors:** `400` if `name` is unknown or `status` is invalid.

---

### POST /api/attempt

Record a practice attempt (+1).

**Request:**
```json
{ "name": "two_pointers" }
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `name` | `string` | Topic name |

**Response:**
```json
{
  "ok": true,
  "section_key": "coding",
  "item": { "name": "two_pointers", "tier": 1, "status": "in_progress", "attempts": 2, "last_attempt": "2026-05-25" }
}
```

**Errors:** `400` if `name` is unknown.

---

## Run Code

### POST /api/run

Run problem files through the WASM judge. Code executes inside wasmtime sandbox. Falls back to native subprocess if wasmtime is unavailable.

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `lang` | `string[]` | `["py"]` | Languages to run. Valid: `py`, `c`, `cpp`, `rs`, `js` |
| `pattern` | `string \| null` | `null` | Specific pattern name (e.g. `sliding_window`) |
| `all_patterns` | `bool` | `false` | Run all patterns regardless of status |
| `solution` | `bool` | `false` | Run solutions instead of problem stubs |

**Examples:**

```
POST /api/run?lang=py
POST /api/run?lang=py&pattern=sliding_window
POST /api/run?lang=c,rs&solution=true
POST /api/run?lang=py&all_patterns=true
```

**Response:**
```json
{
  "results": [
    {
      "lang": "py",
      "runtime": "wasm",
      "output": "============================================================\n  Running 3 pattern(s) (problems)\n...",
      "exit_code": 0
    }
  ]
}
```

On timeout:
```json
{
  "results": [
    { "lang": "py", "runtime": "wasm", "error": "Timed out after 120 seconds" }
  ]
}
```

`runtime` is `"wasm"` when wasmtime is available, `"native"` otherwise.

**Resource limits** (enforced by wasmtime):
- 512MB max memory (`-W max-memory-size=536870912`)
- 5B fuel (`-W fuel=5_000_000_000`, CPU instruction limit)
- 120s timeout (`-W timeout=120s`)

**Sandbox** (WASM/wasmtime):
- No filesystem access unless explicitly `--dir`
- No network (WASI has no networking syscalls)
- No kernel access (WASM runs in user-space)
- No `fork()` (WASM is single-threaded)

---

## File Editor

### GET /api/files/ls

List files for a topic.

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | `string` | required | Topic name |
| `ext` | `string \| null` | `null` | Filter by extension (e.g. `.py`, `.c`) |

**Example:** `GET /api/files/ls?name=sliding_window&ext=.py`

**Response:**
```json
{
  "has_files": true,
  "files": [
    { "name": "p003_longest_substring.py", "size": 1234 },
    { "name": "p438_find_anagrams.py", "size": 892 }
  ]
}
```

**Errors:** `404` if topic is unknown.

---

### GET /api/files/read

Read a file's content.

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | `string` | required | Topic name |
| `file` | `string` | required | Filename |

**Example:** `GET /api/files/read?name=sliding_window&file=p003_longest_substring.py`

**Response:**
```json
{
  "content": "def solve():\n    ...",
  "language": "python"
}
```

`language` is the CodeMirror mode for syntax highlighting: `python`, `text/x-csrc`, `text/x-c++src`, `rust`, `text/javascript`, `markdown`, or `text`.

**Errors:** `404` if topic or file not found. `400` if name contains path traversal characters.

---

### POST /api/files/write

Save file content. Creates a version snapshot automatically.

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | `string` | required | Topic name |
| `file` | `string` | required | Filename |

**Request Body:**
```json
{ "content": "def solve():\n    return 42\n" }
```

**Response:**
```json
{ "ok": true, "size": 28 }
```

Only saves a new snapshot if the content differs from the last saved version.

**Errors:** `404` if topic not found. `400` if name contains path traversal characters.

---

### GET /api/files/solution

Read a solution file (answer key, read-only).

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | `string` | required | Topic name |
| `file` | `string` | required | Filename |

**Example:** `GET /api/files/solution?name=sliding_window&file=p003_longest_substring.py`

**Response:** Same as `/api/files/read`:
```json
{ "content": "...", "language": "python" }
```

**Errors:** `404` if topic or solution file not found. `400` if path traversal detected.

---

### GET /api/files/in-progress

List all files for topics currently marked as "in progress".

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `ext` | `string \| null` | `null` | Filter by extension |

**Example:** `GET /api/files/in-progress?ext=.py`

**Response:**
```json
{
  "files": [
    { "item": "sliding_window", "name": "p003_longest_substring.py", "size": 1234 },
    { "item": "two_pointers", "name": "p167_two_sum.py", "size": 567 }
  ]
}
```

---

### GET /api/files/history

Get version history for a file.

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | `string` | required | Topic name |
| `file` | `string` | required | Filename |

**Example:** `GET /api/files/history?name=sliding_window&file=p003_longest_substring.py`

**Response:**
```json
{
  "versions": [
    { "label": "Original", "key": "Original" },
    { "label": "Save @ 14:30:22", "key": "Save @ 14:30:22" },
    { "label": "Save @ 15:01:08", "key": "Save @ 15:01:08" }
  ]
}
```

---

### POST /api/files/revert

Revert a file to a previous version.

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | `string` | required | Topic name |
| `file` | `string` | required | Filename |
| `label` | `string` | required | Version label to revert to |

**Example:** `POST /api/files/revert?name=sliding_window&file=p003_longest_substring.py&label=Original`

**Response (reverted):**
```json
{ "ok": true }
```

**Response (no change):**
```json
{ "ok": true, "skipped": true }
```

**Errors:** `400` if version label not found. `404` if topic or file not found.

---

## Pages

| Route | Description |
|-------|-------------|
| `GET /` | Progress dashboard (HTML) |
| `GET /code` | Full-screen code editor (HTML) |
| `GET /static/*` | Static assets (JS, CSS, CodeMirror) |

---

## Allowed File Extensions

The file API only serves and accepts files with these extensions:

| Extension | Language | CodeMirror Mode |
|-----------|----------|-----------------|
| `.py` | Python | `python` |
| `.c` | C | `text/x-csrc` |
| `.cpp` | C++ | `text/x-c++src` |
| `.rs` | Rust | `rust` |
| `.mjs` | JavaScript | `text/javascript` |
| `.md` | Markdown | `markdown` |

---

## Security

### Path Traversal Protection

All `name` and `file` parameters are validated:
- `..`, `/`, `\`, `\0` are rejected
- Resolved paths must be relative to the topic's directory
- Solutions are read-only (cannot be written)

### Resource Limits (all `/api/run` calls, enforced by wasmtime)

| Limit | Value | Prevents |
|-------|-------|----------|
| Memory | 512 MB | Memory exhaustion |
| CPU fuel | 5B instructions | Infinite loops |
| Timeout | 120s | Long-running code |
| Filesystem | none by default | Host file access |
| Network | none (WASI) | Network access |
