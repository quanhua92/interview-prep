# Multi-User Deployment

Deploying interview-prep to a shared server where multiple people can use it simultaneously, each with their own isolated workspace and progress.

Code execution is sandboxed via **WASM** (wasmtime). See [WASM_SANDBOX.md](./WASM_SANDBOX.md) for benchmarks, toolchain details, and security properties.

## Problem

The current architecture is single-user:

| Data | Location | Shared? |
|------|----------|---------|
| Progress | `progress/tracker.json` | Single file, all users see same state |
| Code edits | `tier*_*/.../problems/` on disk | Overwrites between users |
| Version history | `_file_snapshots` in-memory dict | Lost on restart, shared |
| Code execution | `subprocess.run` on host | Any user can run arbitrary code, access other users' files, network, etc. |

If deployed as-is, all users share the same system. Two people working on the same problem would overwrite each other's code. More critically, the `/api/run` endpoint (`web.py`) runs user-edited code — a major security vulnerability in a multi-user context.

## Multi-User Architecture

### Overview

```
┌──────────────────────────────────────────────────────┐
│  Main Container (FastAPI + auth + wasmtime)          │
│                                                       │
│  Auth Layer (session cookie)                        │
│  ┌────────────────────────────────────────────┐       │
│  │  data/user1/                              │       │
│  │    tracker.json                           │       │
│  │    files/sliding_window/p003.py           │       │
│  │    snapshots/sliding_window/p003.json     │       │
│  │                                            │       │
│  │  data/user2/                              │       │
│  │    tracker.json                           │       │
│  │    files/two_pointers/p167.py            │       │
│  │    snapshots/two_pointers/p167.json       │       │
│  └────────────────────────────────────────────┘       │
│                                                       │
│  Shared (read-only):                                  │
│    tier*_*/solutions/  (answer keys)                  │
│    system_design/*/discussion.md                       │
│    behavioral/*/discussion.md                          │
│    ... all other topic dirs                            │
│    static/ (JS, CSS, CodeMirror)                      │
│                                                       │
│  /api/run ──compile── .wasm ──┐                       │
│              (wasm_runner.py)  ├── wasmtime (sandboxed)│
│                               ┘                       │
│                                                       │
│  WASM sandbox per run:                                │
│    fuel=2B      → CPU instruction limit               │
│    timeout=120s → wall-clock timeout                   │
│    max-mem=256M → hard memory cap                     │
│    --dir <user> → only user's code dir visible        │
│    no network  → WASI has no networking               │
└──────────────────────────────────────────────────────┘
  No --privileged. No Docker socket. No special flags.
```

### Auth Layer

Simple username/password with session cookies:

- `POST /api/auth/register` — create account (bcrypt hashed password)
- `POST /api/auth/login` — validate credentials, set `httponly` session cookie
- `POST /api/auth/logout` — clear session
- `GET /api/auth/me` — return current user from session
- Middleware: all `/api/*` endpoints (except auth) require valid session, inject `user_id`

Session store: SQLite table `sessions (id, user_id, token, expires_at)`.

No OAuth, no email verification — keep it simple for personal/small-team use.

### Data Isolation

**Per-user (read-write, isolated by `data/{user_id}/`):**

| Data | Path | Format |
|------|------|--------|
| Progress | `data/{user_id}/tracker.json` | Same schema as current `tracker.json` |
| Edited code | `data/{user_id}/files/{item_name}/{filename}` | Source code |
| Version history | `data/{user_id}/snapshots/{item_name}/{filename}.json` | JSON array of versions |

**Shared (read-only, available to all users):**

| Data | Path | Notes |
|------|------|-------|
| Solutions | `tier*_*/.../solutions/` | Answer keys, view-only via `/api/files/solution` |
| Topic discussions | `system_design/*/discussion.md`, etc. | Reference material |
| Checklists | `*/checklist.md` | Reference material |
| Static assets | `static/` | JS, CSS, CodeMirror |
| AI prompts | `ai_assisted/*/README.md`, `TIPS.md` | Reference material |

### How `tracker.py` Changes

Current:
```python
TRACKER_PATH = ROOT / "progress" / "tracker.json"
```

After:
```python
def get_tracker_path(user_id: str) -> Path:
    return ROOT / "data" / user_id / "tracker.json"
```

All functions that read/write tracker data accept `user_id` and use the dynamic path. The schema inside `tracker.json` stays identical — no migration needed.

### How `web.py` Changes

- All endpoints that touch user data (tracker, files, snapshots) get `user_id` from session
- File read/write routes use `data/{user_id}/files/` prefix instead of the shared tier dirs
- Version history (`_file_snapshots`) becomes `data/{user_id}/snapshots/` on disk, loaded on demand
- `/api/files/solution` still reads from shared `solutions/` dirs (no change)
- `/api/files/ls` for shared topics (system_design, behavioral, etc.) returns the read-only shared files

## Code Execution Sandbox (WASM)

See [WASM_SANDBOX.md](./WASM_SANDBOX.md) for full details.

### Implementation Status

The WASM sandbox is **implemented and wired end-to-end**. Code runs inside wasmtime, not native subprocess.

**What's done:**

- `src/runners/wasm_runner.py` — compile C/C++/Rust/JS to `.wasm`, execute via wasmtime
- `run.py` — uses `wasm_runner` when `wasm_sandbox_active()` (checks `WASM_SANDBOX` env), falls back to native runners otherwise
- `run.py` — stub detection (`abort()`, `todo!()`, `NotImplementedError`) in WASM path, matching native runner behavior
- `wasm_runner.py` — sets `PYTHONPATH` for Python WASM so `src.utils` imports work
- `web.py` — `/api/run` delegates to `run.py`; response includes `"runtime": "wasm" | "native"` field
- `/api/health` — reports WASM toolchain availability and sandbox status
- `.env.example` — configurable toolchain paths (see [Configuration](#configuration))
- `python-dotenv` — `.env` loaded at `web.py` import time, env vars inherited by `run.py` subprocess
- `docker-compose.yml` — `WASM_SANDBOX=auto` with commented-out toolchain path overrides
- `Dockerfile` — installs wasmtime, wasi-sdk v33, javy v8.1.1, CPython 3.14.5 WASI build
- MD5-based `.wasm` cache in `/tmp/wasm-cache/` — avoids recompiling identical source
- `WASM_SANDBOX=auto` — enables WASM when wasmtime available, falls back to native
- `WASM_SANDBOX=0` — disables sandbox, uses native subprocess directly
- All bwrap code removed (no `_detect_bwrap`, `_run_sandboxed`, `import resource`)
- Verified: all 5 languages (py, c, cpp, rs, js) pass in Docker via WASM, stubs correctly skipped

**What's NOT done yet (multi-user):**

- Per-user data directories (`data/{user_id}/`)
- Auth layer (register/login/logout/session middleware)
- Per-user file isolation
- Snapshot persistence to disk

### Configuration

All WASM toolchain paths are configurable via environment variables with sensible defaults (container paths). Set them in `.env` (loaded by `python-dotenv` at startup) or export directly.

See [`.env.example`](../.env.example) for all variables:

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

`load_dotenv()` runs at `web.py` module import time, before `wasm_runner.py` reads `os.environ.get()`. Env vars are inherited by `run.py` subprocess (no need for `load_dotenv()` in `run.py`). Exported env vars take precedence over `.env` file values.

### Resource Limits (enforced by wasmtime)

| Limit | Flag | Value | Purpose |
|-------|------|-------|---------|
| CPU instructions | `-W fuel` | 2,000,000,000 | Deterministic CPU limit (kills infinite loops) |
| Wall-clock timeout | `-W timeout` | 120s | Hard time limit |
| Memory | `-W max-memory-size` | 256MB | Hard memory cap |

### Security Properties

| Attack | Protection |
|--------|-----------|
| Read other users' files | No filesystem access unless explicitly `--dir` |
| Network access from code | WASI has no networking syscalls |
| Kernel escape | WASM runs in user-space — no kernel, no syscalls |
| Fork bomb | WASM is single-threaded, no `fork()` |
| Memory exhaustion | Hard memory cap enforced by wasmtime |
| Infinite loops | Fuel limit + wall-clock timeout |
| Cross-user data access | Per-user directories, session-based user_id injection |
| Path traversal on file API | `_validate_fs_name` + `resolve().is_relative_to()` |
| Session hijacking | `httponly`, `Secure`, `SameSite=Strict` cookie flags |

### Dockerfile

See [WASM_SANDBOX.md](./WASM_SANDBOX.md#dockerfile-wasm-toolchain) for the full Dockerfile with WASM toolchain (wasmtime, wasi-sdk, javy, python.wasm).

### docker-compose.yml

No special compose file needed. Just:
```bash
docker compose up -d
```

No `--privileged`. No Docker socket. No `--userns=host`. No `seccomp=unconfined`.

## Security Considerations

### Threat Model

The system is designed to be safe against:

1. **Malicious code execution** — user writes code that tries to access other users' data, the network, or exhaust host resources
2. **Path traversal** — user tries to read/write files outside their own directory (already handled by `_validate_fs_name` and `_resolve_safe_path`)
3. **Session hijacking** — protected by `httponly`, `Secure`, `SameSite=Strict` cookie flags

### Why No `--privileged` or Docker Socket

| Approach | Risk | Used by |
|----------|------|---------|
| `--privileged` | Full host access — same as running on bare metal | nsjail, Docker-from-Docker |
| Docker socket mount | Full Docker API — can create privileged containers | Docker-in-Docker |
| `--userns=host` + `seccomp=unconfined` | Root inside container = root on host, no syscall filtering | bwrap (legacy) |
| **WASM (wasmtime)** | **No kernel access, no special Docker flags** | **This project** |

### Historical note: bubblewrap tradeoffs

The previous approach used bubblewrap (bwrap) with Linux namespaces. bwrap works well but requires `--userns=host` + `seccomp=unconfined` on the Docker container, which weakens the outer container's security. The main concerns:

- **`--ro-bind /app /app`** exposes all users' data directories to sandboxed code (cross-user data leak)
- **Shared `/tmp`** between concurrent bwrap instances allows reading other users' compilation artifacts
- **No `--unshare-net`** — sandboxed code has network access through the outer container
- **Linux only** — doesn't work on Docker Desktop (macOS/Windows VM kernel doesn't support user namespaces)
- **Kernel exploit surface** — bwrap escape combined with weakened Docker security could lead to full host compromise

All bwrap code has been removed. WASM eliminates all of these issues. See [WASM_SANDBOX.md](./WASM_SANDBOX.md) for the full comparison.

### Health Check

```
GET /api/health
```

Returns system health, sandbox status, and runtime availability:

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
    "javy": { "available": true },
    "python-wasm": { "available": true }
  }
}
```

| Field | Meaning |
|-------|---------|
| `sandbox.type` | `"wasm"` or `"none (direct subprocess)"` |
| `sandbox.wasmtime_available` | Whether `wasmtime` binary exists |
| `sandbox.sandbox_active` | Whether `/api/run` will use WASM isolation |

### Password Security

- bcrypt hash with `cost=12`
- No plaintext storage
- Session tokens: `secrets.token_urlsafe(32)` with expiry

## API Changes

### Existing Endpoints

```
GET  /api/health           → system health, sandbox status, runtime availability
POST /api/run              → run problems, returns results with "runtime" field (wasm/native)
GET  /api/files/ls         → list files
GET  /api/files/read       → read file
POST /api/files/write      → write file
GET  /api/files/solution   → read-only solutions
GET  /api/files/history    → file version history
POST /api/files/revert     → revert file
GET  /api/files/in-progress → in-progress files
GET  /api/tracker          → progress tracker
POST /api/update           → update progress
POST /api/attempt          → record attempt
```

### `/api/run` response format

```json
{
  "results": [
    {
      "lang": "py",
      "runtime": "wasm",
      "output": "...",
      "exit_code": 0
    }
  ]
}
```

The `runtime` field indicates whether the code ran in WASM sandbox (`"wasm"`) or native subprocess (`"native"`).

### Planned New Endpoints (not yet implemented)

```
POST /api/auth/register    { username, password }    → { ok, user_id }
POST /api/auth/login       { username, password }    → set session cookie
POST /api/auth/logout      (session cookie)          → clear session cookie
GET  /api/auth/me          (session cookie)          → { user_id, username }
```

### Modified Endpoints (planned, all require session cookie)

```
GET  /api/tracker          → user's tracker.json
POST /api/update           → update user's progress
POST /api/attempt          → record user's attempt
GET  /api/files/ls         → user's files (or shared topic files)
POST /api/files/write      → write to user's data dir
GET  /api/files/in-progress → user's in-progress files
GET  /api/files/history    → user's version history
POST /api/files/revert     → revert user's file
```

### Unchanged Endpoints

```
GET /                      → dashboard (HTML)
GET /code                  → code editor page (HTML)
GET /static/*              → static assets (JS, CSS, CodeMirror)
GET /api/files/solution    → shared read-only solutions (no user scope)
```

## Implementation Order

1. **WASM sandbox** — done (`src/runners/wasm_runner.py`, `web.py` integration, `Dockerfile`)
2. **Per-user data directories** — modify `tracker.py` to accept `user_id`, create `data/` structure
3. **Auth layer** — add login/register/logout endpoints, session middleware
4. **File isolation** — update all file endpoints to use per-user paths
5. **Testing** — verify isolation between users, sandbox escape attempts, resource limits
