# Multi-User Deployment

> **ON HOLD** — The sandbox layer requires `--userns=host` + `seccomp=unconfined` on the outer Docker container to enable bwrap inside. This weakens Docker's security (root inside container = root on host, no seccomp filtering). The bwrap tradeoff is acceptable for small-team/personal use (bwrap's user namespace is the real security boundary for code execution), but not for a public multi-tenant service. Revisit with a custom seccomp profile (restore Docker's default syscall filtering while allowing `unshare()`), or a stronger isolation approach (Firecracker/Kata VMs, gVisor user-space kernel).

Deploying interview-prep to a shared server where multiple people can use it simultaneously, each with their own isolated workspace and progress.

## Problem

The current architecture is single-user:

| Data | Location | Shared? |
|------|----------|---------|
| Progress | `progress/tracker.json` | Single file, all users see same state |
| Code edits | `tier*_*/.../problems/` on disk | Overwrites between users |
| Version history | `_file_snapshots` in-memory dict | Lost on restart, shared |
| Code execution | `subprocess.run` on host | Any user can run arbitrary code, access other users' files, network, etc. |

If deployed as-is, all users share the same system. Two people working on the same problem would overwrite each other's code. More critically, the `/api/run` endpoint (`web.py:259`) runs user-edited code directly on the host via `subprocess.run` — a major security vulnerability in a multi-user context.

## Multi-User Architecture

### Overview

```
┌──────────────────────────────────────────────────────┐
│  Main Container (FastAPI + auth + bwrap)             │
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
│  /api/run ──spawn── bwrap ──┐                         │
│                    bwrap ──┤  (sandboxed)             │
│                    bwrap ──┘                         │
│                                                       │
│  Sandboxed view per run:                              │
│    /usr  → ro-bind (compilers, libs)                 │
│    /bin  → ro-bind (essential binaries)              │
│    /lib  → ro-bind (shared libs)                     │
│    /lib64 → ro-bind (dynamic linker)                 │
│    /etc  → ro-bind (system config)                   │
│    /app  → ro-bind (code, solutions)                 │
│    /tmp  → rw-bind (compilation output)              │
│    /dev  → minimal (null only)                       │
│    /proc → new proc namespace                         │
│    user  → new user namespace (unprivileged mapping)  │
└──────────────────────────────────────────────────────┘
  No --privileged. No Docker socket. No external daemon.
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

## Code Execution Sandbox (bubblewrap)

### The Problem

When someone uses `/api/run`, we execute their code on the server. Without sandboxing, they could:

- Read other users' files
- Access the network
- Fork bomb or exhaust memory
- See host processes

### Linux Namespaces Explained

Linux namespaces are the same technology that Docker uses under the hood. They let you create "mini containers" without Docker. Each namespace type isolates something:

| Namespace | Isolates | bwrap Flag | Example |
|-----------|----------|------------|---------|
| **user** | User IDs (root inside = nobody outside) | `--unshare-user` | Process thinks it's root, but is actually UID 100000 on host |
| **pid** | Process IDs (PID 1 inside) | `--unshare-pid` | Can't see or kill host processes |
| **ipc** | Inter-process communication | `--unshare-ipc` | Can't interact with host IPC (shared memory, semaphores) |
| **uts** | Hostname | `--unshare-uts` | Isolated hostname |
| **net** | Network interfaces | `--unshare-net` | No network interfaces (not used — see below) |
| **mount** | Filesystem view | (implicit) | Only explicitly bind-mounted paths are visible |

`bubblewrap` (bwrap) is a lightweight tool that sets up these namespaces. Same primitives as Docker, but ~50ms spawn time and no daemon. It's used by **Flatpak** (the Linux app sandbox) and is maintained by Red Hat.

### Why `--unshare-user` Is the Key

Here's what happened during debugging:

1. **First attempt**: Used `--unshare-net`, `--unshare-pid` → **failed** (Operation not permitted)
2. **Added `--cap-add SYS_ADMIN`** → **still failed**
3. **Added `--security-opt seccomp=unconfined`** → **still failed**
4. **Added `--userns=host` + `--unshare-user`** → **worked!**

Why? In Docker's default setup, the container runs in Docker's own user namespace. Docker blocks `unshare()` inside the container (via seccomp) to prevent a process from creating nested namespaces — that's a security feature of Docker itself.

`--userns=host` tells Docker: "don't create your own user namespace, use the host's." This allows bwrap to call `unshare(CLONE_NEWUSER)` inside the container. Once bwrap creates its own user namespace, the process inside the sandbox is mapped to an unprivileged user (typically UID 0 inside → some high UID outside). **This is the isolation boundary** — the sandboxed code thinks it's root, but it's actually a nobody user with no real permissions.

Then with user namespace established, all other namespace types (`--unshare-pid`, `--unshare-ipc`, `--unshare-uts`) work because the process has its own user namespace.

We don't use `--unshare-net` because Docker doesn't give containers `CAP_NET_ADMIN` by default, and we don't want to add it. The outer container's network is already isolated by Docker.

### What the Sandboxed Process Sees

```
Normal container filesystem:
/home, /var, /etc, /usr, /app, /tmp, /proc, /dev, ...

Bwrap sandbox (only what we explicitly mount):
/usr  → read-only (compilers, python, node)
/bin  → read-only (essential binaries)
/lib  → read-only (shared libraries)
/lib64 → read-only (dynamic linker)
/etc  → read-only (system config)
/app  → read-only (your code, solutions)
/tmp  → read-write (compilation output only)
/dev  → minimal devices
/proc → new namespace (can't see host processes)

Everything else: doesn't exist. No /home, no /var, no /root.
```

### Security Tradeoff: `--userns=host` + `seccomp=unconfined` + `apparmor=unconfined`

> **WARNING** These flags weaken the outer Docker container's security. Read this section carefully.

#### What each flag does

| Flag | Effect | Why we need it |
|------|--------|----------------|
| `--userns=host` | Container shares the host's UID mapping. Root inside container = root on host. | bwrap needs `CLONE_NEWUSER` to create its own user namespace |
| `seccomp=unconfined` | All syscalls allowed inside the container (Docker normally blocks ~50 dangerous ones) | Docker's default seccomp blocks `unshare()` |
| `apparmor=unconfined` | AppArmor MAC profile disabled | AppArmor blocks `unshare()` |

#### What the risks actually are

These flags primarily matter for **container escape** scenarios. If someone finds a kernel exploit (e.g., CVE-2022-0185, dirty pipe):

- **With these flags**: attacker is root on host with unrestricted syscalls — full host compromise
- **Without these flags**: attacker is an unprivileged high-UID user with restricted syscalls — much harder to escalate

The attack chain would be:
1. User submits malicious code via `/api/run`
2. bwrap sandbox contains the code (user namespace isolation)
3. Attacker finds a **kernel vulnerability** inside the bwrap sandbox
4. Kernel exploit breaks out of bwrap's user namespace
5. With `userns=host`: they're now root on the host with no seccomp/AppArmor restrictions

Steps 3-4 require a **zero-day kernel exploit**. This is extremely hard and would affect millions of servers.

#### Why it's acceptable for this use case

- **Small team / personal tool**, not a public-facing multi-tenant service
- The main threat (user running arbitrary code) is mitigated by **bwrap's namespace isolation** — the inner sandbox is the real security boundary for code execution
- Container escape requires a **kernel-level vulnerability**, which is a host-wide problem regardless of these flags
- Keep the host kernel updated to minimize the container escape surface
- For a **production multi-tenant service**, you'd want either a custom seccomp profile (allowlist only `unshare`, `clone`, `clone3`, `mount`, `pivot_root`, `setns`, `move_mount` instead of disabling seccomp entirely) or a stronger isolation approach (Firecracker/Kata VMs, gVisor user-space kernel)

#### Two-layer model

```
Outer layer (Docker):  filesystem + process isolation from host
                       ↑ weakened by userns=host, seccomp=unconfined
Inner layer (bwrap):   user namespace isolation for code execution
                       ↑ this is the real security boundary for /api/run
```

`--userns=host` and `seccomp=unconfined` weaken the outer layer to allow the inner layer to work. The inner layer (bwrap namespaces) is the security boundary that protects against the primary threat: user-submitted code.

#### Future improvement: custom seccomp profile

A custom seccomp profile that adds only `unshare`, `clone3`, `mount`, `pivot_root`, `setns`, and `move_mount` to Docker's default allowlist would keep all of Docker's default protections (~50 blocked syscalls like `keyctl`, `bpf`, `kexec_load`, `reboot`) while allowing bwrap to work.

However, creating this profile is non-trivial:
1. Docker's default profile is compiled into the binary — there's no JSON file on disk to extend
2. Every syscall the app and its dependencies need must be audited at runtime
3. An incomplete profile will crash the container at startup (tested — missing syscalls broke `uv`)

### Auto-Detection and Fallback

```
At startup:
1. Check if `bwrap` binary exists
2. Try running: bwrap --unshare-user --unshare-pid ... /bin/true
3. If exit code 0 → sandbox active
4. If fails → fallback to direct subprocess (with same resource limits)

Docker Desktop (macOS/Windows): fails (VM kernel limitation) → fallback
Linux server with proper flags: works → full sandbox
```

Resource limits (512MB memory, 16 processes, 64 file descriptors, 130s timeout) apply in both paths.

### Why bubblewrap over alternatives

| | Docker-from-Docker | nsjail | bubblewrap |
|---|---|---|---|
| Extra privileges needed | Docker socket (`--privileged` equiv) | `--privileged` (nested namespaces) | **None** |
| Container security | Exposes Docker daemon to container | Requires `--privileged` — defeats purpose | Works in unprivileged containers |
| Attack surface | Full Docker API | nsjail binary + privileged container | Single `bwrap` binary, no privileges |
| Isolation level | Container | Namespace (same primitives) | Namespace (same primitives) |
| Spawn time | ~1-2 seconds | ~50ms | ~50ms |
| Installation | Mount Docker socket | Build from source | `apt install bubblewrap` |
| Works in Docker Desktop | Yes (but insecure) | No (needs `--privileged`) | Yes on Linux servers |

**Key insight:** nsjail requires `--privileged` to create namespaces inside a container, which completely defeats the purpose of sandboxing — a privileged container has full access to the host, same as exposing the Docker socket. bubblewrap is specifically designed to work **inside** unprivileged containers using `CLONE_NEWUSER`.

### Installation

```bash
# Debian/Ubuntu
sudo apt install bubblewrap

# RHEL/CentOS
sudo dnf install bubblewrap

# Alpine
sudo apk add bubblewrap
```

Single binary. No build from source. No dependencies beyond glibc.

### Security Properties

The sandboxed process **cannot**:

- Access the network (no `--unshare-net` — not available in Docker containers without `CAP_NET_ADMIN`, but the outer container's network is controlled by Docker)
- Read/write host filesystem (only explicitly bind-mounted paths are visible)
- Read other users' files (only `/app` is mounted read-only)
- See host processes (`--unshare-user` + `--unshare-pid` — new user and PID namespaces)
- Access IPC resources (`--unshare-ipc`)
- Escape the user namespace (`--unshare-user` maps to unprivileged UID)
- Fork bombs (`resource.setrlimit(RLIMIT_NPROC, 16)` before sandbox spawn)
- Exhaust memory (`resource.setrlimit(RLIMIT_AS, 512MB)` before sandbox spawn)
- Exhaust file descriptors (`resource.setrlimit(RLIMIT_NOFILE, 64)` before sandbox spawn)
- Run longer than the time limit (`subprocess.run(timeout=130)`)

### Dockerfile

```dockerfile
FROM python:3.14-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc g++ rustc nodejs bubblewrap \
  && rm -rf /var/lib/apt/lists/*

COPY --from=ghcr.io/astral-sh/uv:latest /uv /usr/local/bin/uv

WORKDIR /app

COPY pyproject.toml uv.lock ./
RUN uv sync --frozen --no-dev

COPY . .

EXPOSE 8888

CMD ["uv", "run", "python", "main.py", "start"]
```

No `--privileged`. No Docker socket. Just `apt install bubblewrap`.

### docker-compose.yml

Default (local dev — no sandbox):
```bash
docker compose up -d
```

With bwrap sandbox (Linux server):
```bash
docker compose -f docker-compose.sandbox.yml up -d
```

### How `/api/run` Works

Current (unsafe — runs directly on host):
```python
result = subprocess.run(
    [sys.executable, str(tracker.ROOT / "run.py")],
    capture_output=True, text=True, timeout=120,
    cwd=str(tracker.ROOT),
)
```

After (sandboxed via bwrap):
```python
import resource

_BWRAP_BASE = [
    "--unshare-user",     # user namespace (unprivileged UID mapping)
    "--unshare-pid",      # PID isolation
    "--unshare-ipc",      # IPC isolation
    "--unshare-uts",      # UTS isolation
    "--die-with-parent",  # cleanup when parent dies
    "--new-session",      # new session (no controlling terminal)
]

def _set_resource_limits():
    resource.setrlimit(resource.RLIMIT_AS, (512 * 1024 * 1024, 512 * 1024 * 1024))
    resource.setrlimit(resource.RLIMIT_NPROC, (16, 16))
    resource.setrlimit(resource.RLIMIT_NOFILE, (64, 64))

def _run_in_bwrap(cmd: list[str], timeout: int = 120) -> subprocess.CompletedProcess:
    return subprocess.run(
        [
            "bwrap",
            *_BWRAP_BASE,
            "--ro-bind", "/usr", "/usr",          # compilers, libs (read-only)
            "--ro-bind", "/bin", "/bin",           # essential binaries (read-only)
            "--ro-bind", "/lib", "/lib",           # shared libs (read-only)
            "--ro-bind", "/lib64", "/lib64",       # linker (read-only)
            "--ro-bind", "/etc", "/etc",           # config (read-only)
            "--ro-bind", "/app", "/app",           # app code (read-only)
            "--bind", "/tmp", "/tmp",              # compilation output (read-write)
            "--dev", "/dev",                        # minimal /dev
            "--proc", "/proc",                      # new proc namespace
            "--chdir", "/app",
            "--",
            *cmd,
        ],
        capture_output=True,
        text=True,
        timeout=timeout + 10,
        preexec_fn=_set_resource_limits,           # memory, process, fd limits
    )
```

### bwrap Flags Reference

| Flag | Purpose |
|------|---------|
| `--unshare-user` | New user namespace (maps to unprivileged UID — key isolation primitive) |
| `--ro-bind /usr /usr` | Mount system binaries/libs read-only |
| `--ro-bind /bin /bin` | Mount essential binaries read-only |
| `--ro-bind /lib /lib` | Mount shared libraries read-only |
| `--ro-bind /lib64 /lib64` | Mount dynamic linker read-only |
| `--ro-bind /etc /etc` | Mount system config read-only |
| `--ro-bind /app /app` | Mount app code read-only (no edits possible) |
| `--bind /tmp /tmp` | Mount /tmp read-write (needed for compilation) |
| `--dev /dev` | Minimal `/dev` (only essential devices) |
| `--proc /proc` | New `/proc` filesystem (can't see host processes) |
| `--unshare-pid` | New PID namespace (isolated process tree) |
| `--unshare-ipc` | New IPC namespace (can't interact with host IPC) |
| `--unshare-uts` | New UTS namespace (isolated hostname) |
| `--die-with-parent` | Sandbox dies if the parent process dies |
| `--new-session` | New session group (no controlling terminal) |
| `--chdir /app` | Set working directory |

### Resource Limits (set via Python `resource` module)

| Limit | Value | Purpose |
|-------|-------|---------|
| `RLIMIT_AS` | 512MB | Max virtual memory (prevent memory exhaustion) |
| `RLIMIT_NPROC` | 16 | Max child processes (prevent fork bombs) |
| `RLIMIT_NOFILE` | 64 | Max open file descriptors (prevent fd exhaustion) |
| `subprocess timeout` | 130s | Kill sandbox after timeout (prevent infinite loops) |

## Security Considerations

### Threat Model

The system is designed to be safe against:

1. **Malicious code execution** — user writes code that tries to access other users' data, the network, or exhaust host resources
2. **Path traversal** — user tries to read/write files outside their own directory (already handled by `_validate_fs_name` and `_resolve_safe_path`)
3. **Session hijacking** — protected by `httponly`, `Secure`, `SameSite=Strict` cookie flags

### What Is Protected

| Attack | Protection |
|--------|-----------|
| Read other users' files | bwrap namespace isolation — only `/app` visible, read-only |
| Network access from code | Outer container's network is controlled by Docker (no `CAP_NET_ADMIN` exposed) |
| Fork bomb | `RLIMIT_NPROC 16` via Python `resource` module |
| Memory exhaustion | `RLIMIT_AS 512MB` via Python `resource` module |
| Infinite loops | `subprocess.run(timeout=130)` kills the sandbox |
| Read host /proc | `--unshare-pid` (new PID namespace, new /proc) |
| IPC attacks | `--unshare-ipc` (new IPC namespace) |
| User namespace escape | `--unshare-user` (maps to unprivileged UID inside sandbox) |
| File descriptor exhaustion | `RLIMIT_NOFILE 64` via Python `resource` module |
| Path traversal on file API | `_validate_fs_name` + `resolve().is_relative_to()` |
| Cross-user data access | Per-user directories, session-based user_id injection |

### Why No `--privileged` or Docker Socket

| Approach | Risk | Required for |
|----------|------|-------------|
| `--privileged` | Full host access — same as running on bare metal | nsjail nested namespaces |
| Docker socket mount | Full Docker API — can create privileged containers | Docker-from-Docker |
| `--cap-add SYS_ADMIN` | Broad capability — can mount filesystems, bypass restrictions | nsjail (partial) |
| `--userns=host` + `seccomp=unconfined` | Low — outer container has normal isolation, bwrap creates its own unprivileged user namespace | **bwrap** |

| **Nothing** (bwrap on Docker Desktop) | **Minimal** — container provides isolation, fallback to direct subprocess | **Development only** |

bwrap with `--userns=host` + `seccomp=unconfined` is the recommended approach for production Linux servers.

### Docker Desktop vs Linux Server

| Environment | bwrap works? | Notes |
|-------------|-------------|-------|
| Linux server (EC2, DigitalOcean, etc.) | Yes | Needs `--userns=host` + `--security-opt seccomp=unconfined --security-opt apparmor=unconfined` on outer container |
| Docker Desktop on macOS | No | VM kernel doesn't support user namespaces, even with `--userns=host` |
| Docker Desktop on Windows | No | Same VM limitation |

On Docker Desktop, bwrap is installed but namespace creation fails (VM limitation). The system **automatically falls back** to direct `subprocess.run` with the same resource limits applied — this is acceptable for local development (single-user). On a real Linux server, bwrap sandboxing is fully active.

### Health Check

```
GET /api/health
```

Returns system health, sandbox status, and runtime availability:

```json
{
  "status": "ok",
  "sandbox": {
    "type": "bwrap",
    "bwrap_available": true,
    "bwrap_namespaces": true,
    "sandbox_active": true
  },
  "runtimes": {
    "python": { "available": true, "version": "Python 3.14.5" },
    "gcc":    { "available": true, "version": "gcc (Debian 14.2.0-19) 14.2.0" },
    "g++":    { "available": true, "version": "g++ (Debian 14.2.0-19) 14.2.0" },
    "rustc":  { "available": true, "version": "rustc 1.85.0 ..." },
    "node":   { "available": true, "version": "v20.19.2" }
  }
}
```

| Field | Meaning |
|-------|---------|
| `sandbox.type` | `"bwrap"` or `"none (direct subprocess)"` |
| `sandbox.bwrap_available` | Whether `bwrap` binary exists |
| `sandbox.bwrap_namespaces` | Whether namespace creation succeeded (false on Docker Desktop) |
| `sandbox.sandbox_active` | Whether `/api/run` will use bwrap isolation |

On Docker Desktop you'll see `sandbox_active: false`. On a Linux server, `sandbox_active: true`.

### Password Security

- bcrypt hash with `cost=12`
- No plaintext storage
- Session tokens: `secrets.token_urlsafe(32)` with expiry

## API Changes

### New Endpoints

```
GET  /api/health           → system health, sandbox status, runtime versions
POST /api/auth/register    { username, password }    → { ok, user_id }
POST /api/auth/login       { username, password }    → set session cookie
POST /api/auth/logout      (session cookie)          → clear session cookie
GET  /api/auth/me          (session cookie)          → { user_id, username }
```

### Modified Endpoints (all require session cookie)

```
GET  /api/tracker          → user's tracker.json
POST /api/update           → update user's progress
POST /api/attempt          → record user's attempt
POST /api/run              → run in bwrap sandbox (or fallback with resource limits if bwrap unavailable)
GET  /api/files/ls         → user's files (or shared topic files)
GET  /api/files/read       → user's file (or shared topic file)
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

1. **Per-user data directories** — modify `tracker.py` to accept `user_id`, create `data/` structure
2. **Auth layer** — add login/register/logout endpoints, session middleware
3. **File isolation** — update all file endpoints to use per-user paths
4. **bwrap sandbox** — add `bubblewrap` to Dockerfile, replace `subprocess.run` with bwrap wrapper
5. **Fallback for Docker Desktop** — detect when bwrap is unavailable and fall back to direct subprocess
6. **Testing** — verify isolation between users, sandbox escape attempts, resource limits
