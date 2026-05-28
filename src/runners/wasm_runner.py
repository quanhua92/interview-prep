"""WASM sandbox runner: compile source to .wasm, execute via wasmtime."""

import hashlib
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

WASM_SANDBOX = os.environ.get("WASM_SANDBOX", "auto")

_WASM_CACHE_DIR = Path(os.environ.get("WASM_CACHE_DIR", "/tmp/wasm-cache"))
_WASMTIME_BIN = os.environ.get("WASMTIME_BIN", "wasmtime")
_WASI_SDK_SYSROOT = os.environ.get("WASI_SDK_SYSROOT", "/opt/wasi-sdk/share/wasi-sysroot")
_WASI_SDK_CLANG = os.environ.get("WASI_SDK_CLANG", "/opt/wasi-sdk/bin/clang")
_WASI_SDK_CLANGPP = os.environ.get("WASI_SDK_CLANGPP", "/opt/wasi-sdk/bin/clang++")
_QUICKJS_WASM = os.environ.get("QUICKJS_WASM", "/opt/quickjs.wasm")
_PYTHON_WASM = os.environ.get("PYTHON_WASM", "/opt/python-wasi/python.wasm")
_PYTHON_WASM_HOME = os.environ.get("PYTHON_WASM_HOME", "/opt/python-wasi")

_WASM_LIBS_DIR = Path("src/wasm_libs")

_COMPILED_LIBS: dict[str, Path | None] = {"rs": None}

_COMPILE_TIMEOUTS = {
    "c": 5,
    "cpp": 5,
    "rs": 30,
}

_WASM_FUEL = 5_000_000_000
_WASM_TIMEOUT = 120
_WASM_MAX_MEMORY = 536870912

_RSTEST_RLIB_PATH: Path | None = None


def wasm_available() -> bool:
    return shutil.which(_WASMTIME_BIN) is not None


def wasm_sandbox_active() -> bool:
    if WASM_SANDBOX == "auto":
        return wasm_available()
    return WASM_SANDBOX.lower() in ("1", "true", "yes", "auto")


def _wasm_cache_path(content: bytes, suffix: str = ".wasm") -> Path:
    _WASM_CACHE_DIR.mkdir(parents=True, exist_ok=True)
    h = hashlib.md5(content).hexdigest()
    return _WASM_CACHE_DIR / f"{h}{suffix}"


# --- Legacy compile functions (ctest.h, cpptest.h, rstest.rs) -- used by non-judge topics ---

def _compile_c(source: Path, out: Path) -> None:
    cmd = [
        _WASI_SDK_CLANG,
        "--target=wasm32-wasip1",
        "--sysroot", _WASI_SDK_SYSROOT,
        "-O2", "-Wall", "-Wextra",
        "-Isrc/runners",
        str(source), "-o", str(out), "-lm",
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["c"])
    if result.returncode != 0:
        raise RuntimeError(f"C compilation failed:\n{result.stderr}")


def _compile_cpp(source: Path, out: Path) -> None:
    cmd = [
        _WASI_SDK_CLANGPP,
        "--target=wasm32-wasip1",
        "--sysroot", _WASI_SDK_SYSROOT,
        "-O2", "-Wall", "-Wextra", "-fno-exceptions",
        "-Isrc/runners",
        str(source), "-o", str(out),
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["cpp"])
    if result.returncode != 0:
        raise RuntimeError(f"C++ compilation failed:\n{result.stderr}")


def _compile_rstest_lib(out_dir: Path) -> Path:
    global _RSTEST_RLIB_PATH
    if _RSTEST_RLIB_PATH is not None and _RSTEST_RLIB_PATH.exists():
        return _RSTEST_RLIB_PATH
    lib_out = out_dir / "librstest.rlib"
    subprocess.run(
        [
            "rustc", "--edition", "2024", "-O",
            "--target", "wasm32-wasip1",
            "src/runners/rstest.rs",
            "--crate-type", "lib", "--crate-name", "rstest",
            "-o", str(lib_out),
        ],
        capture_output=True, text=True, timeout=60, check=True,
    )
    _RSTEST_RLIB_PATH = lib_out
    return lib_out


def _compile_rust(source: Path, out: Path) -> None:
    lib_out = _compile_rstest_lib(out.parent)
    cmd = [
        "rustc", "--edition", "2024", "-O",
        "--target", "wasm32-wasip1",
        str(source), "--extern", f"rstest={lib_out}",
        "-o", str(out),
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["rs"])
    if result.returncode != 0:
        raise RuntimeError(f"Rust compilation failed:\n{result.stderr}")


_COMPILE_FUNCS = {
    "c": _compile_c,
    "cpp": _compile_cpp,
    "rs": _compile_rust,
}

# --- Judge compile functions (wasm_libs) -- used by judge-mode topics ---

def _compile_wasm_libs_rs(out_dir: Path) -> Path:
    if _COMPILED_LIBS["rs"] is not None and _COMPILED_LIBS["rs"].exists():
        return _COMPILED_LIBS["rs"]
    lib_out = out_dir / "libwasm_libs.rlib"
    subprocess.run(
        [
            "rustc", "--edition", "2024", "-O",
            "--target", "wasm32-wasip1",
            str(_WASM_LIBS_DIR / "rs" / "lib.rs"),
            "--crate-type", "lib", "--crate-name", "wasm_libs",
            "-o", str(lib_out),
        ],
        capture_output=True, text=True, timeout=60, check=True,
    )
    _COMPILED_LIBS["rs"] = lib_out
    return lib_out


def _judge_compile_c(source: Path, out: Path) -> None:
    cmd = [
        _WASI_SDK_CLANG,
        "--target=wasm32-wasip1",
        "--sysroot", _WASI_SDK_SYSROOT,
        "-O2", "-Wall", "-Wextra",
        "-Isrc/wasm_libs/c",
        str(source),
        str(_WASM_LIBS_DIR / "c" / "io.c"),
        "-o", str(out), "-lm",
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["c"])
    if result.returncode != 0:
        raise RuntimeError(f"C compilation failed:\n{result.stderr}")


def _judge_compile_cpp(source: Path, out: Path) -> None:
    cmd = [
        _WASI_SDK_CLANGPP,
        "--target=wasm32-wasip1",
        "--sysroot", _WASI_SDK_SYSROOT,
        "-O2", "-Wall", "-Wextra", "-fno-exceptions",
        "-Isrc/wasm_libs/cpp",
        str(source),
        str(_WASM_LIBS_DIR / "cpp" / "io.cpp"),
        "-o", str(out),
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["cpp"])
    if result.returncode != 0:
        raise RuntimeError(f"C++ compilation failed:\n{result.stderr}")


def _judge_compile_rust(source: Path, out: Path) -> None:
    lib_out = _compile_wasm_libs_rs(out.parent)
    cmd = [
        "rustc", "--edition", "2024", "-O",
        "--target", "wasm32-wasip1",
        str(source), "--extern", f"wasm_libs={lib_out}",
        "-o", str(out),
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["rs"])
    if result.returncode != 0:
        raise RuntimeError(f"Rust compilation failed:\n{result.stderr}")


_JUDGE_COMPILE_FUNCS = {
    "c": _judge_compile_c,
    "cpp": _judge_compile_cpp,
    "rs": _judge_compile_rust,
}


def compile_to_wasm(source: Path, lang: str) -> Path:
    if lang not in _COMPILE_FUNCS and lang != "py":
        raise ValueError(f"Unsupported language for WASM compilation: {lang}")

    content = source.read_bytes()
    cached = _wasm_cache_path(content)
    if cached.exists():
        return cached

    with tempfile.NamedTemporaryFile(suffix=".wasm", delete=False, dir="/tmp") as tmp:
        out = Path(tmp.name)

    try:
        if lang == "js":
            raise ValueError("JS does not compile to WASM — use QuickJS WASI runtime instead")
        elif lang == "py":
            raise ValueError("Python does not compile to WASM — use python.wasm directly")
        else:
            _COMPILE_FUNCS[lang](source, out)

        cached.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(out, cached)
        return cached
    finally:
        out.unlink(missing_ok=True)


def judge_compile_to_wasm(source: Path, lang: str) -> Path:
    if lang not in _JUDGE_COMPILE_FUNCS and lang != "py":
        raise ValueError(f"Unsupported language for judge compilation: {lang}")

    content = source.read_bytes()
    cached = _wasm_cache_path(content, suffix=".judge.wasm")
    if cached.exists():
        return cached

    with tempfile.NamedTemporaryFile(suffix=".wasm", delete=False, dir="/tmp") as tmp:
        out = Path(tmp.name)

    try:
        if lang == "py":
            raise ValueError("Python does not compile to WASM — use python.wasm directly")
        elif lang == "js":
            raise ValueError("JS does not compile to WASM — use QuickJS WASI runtime instead")
        _JUDGE_COMPILE_FUNCS[lang](source, out)
        cached.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(out, cached)
        return cached
    finally:
        out.unlink(missing_ok=True)


def run_wasm(wasm_path: Path, source_dir: Path, timeout: int = _WASM_TIMEOUT, stdin_text: str = "") -> dict:
    cmd = [
        _WASMTIME_BIN, "run",
        "-W", f"fuel={_WASM_FUEL}",
        "-W", f"timeout={timeout}s",
        "-W", f"max-memory-size={_WASM_MAX_MEMORY}",
        "--dir", str(source_dir),
    ]
    cmd.append(str(wasm_path))
    try:
        result = subprocess.run(
            cmd,
            input=stdin_text,
            capture_output=True,
            text=True,
            timeout=timeout + 10,
            env={**os.environ, "WASMTIME_BACKTRACE_DETAILS": "1", "RUST_BACKTRACE": "1"},
        )
        output = result.stdout
        if result.stderr:
            output += "\n" + result.stderr
        return {
            "exit_code": result.returncode,
            "output": output.strip(),
            "timed_out": False,
        }
    except subprocess.TimeoutExpired:
        return {"exit_code": -1, "output": "", "timed_out": True}
    except FileNotFoundError:
        return {"exit_code": -1, "output": "", "timed_out": False, "error": "wasmtime not found. Install wasmtime to use the WASM sandbox."}


def run_python_wasm(source: Path, project_root: Path, timeout: int = _WASM_TIMEOUT, stdin_text: str = "") -> dict:
    if not Path(_PYTHON_WASM).exists():
        return {"exit_code": -1, "output": "", "timed_out": False, "error": f"python.wasm not found at {_PYTHON_WASM}"}

    python_home = Path(_PYTHON_WASM_HOME)
    cmd = [
        _WASMTIME_BIN, "run",
        "-W", f"fuel={_WASM_FUEL}",
        "-W", f"timeout={timeout}s",
        "-W", f"max-memory-size={_WASM_MAX_MEMORY}",
        "--dir", str(python_home),
        "--dir", str(project_root),
        "--env", f"PYTHONHOME={python_home}",
        "--env", f"PYTHONPATH={project_root}",
        _PYTHON_WASM,
        "--", str(source),
    ]
    try:
        result = subprocess.run(
            cmd,
            input=stdin_text,
            capture_output=True,
            text=True,
            timeout=timeout + 10,
            env={**os.environ, "WASMTIME_BACKTRACE_DETAILS": "1"},
        )
        output = result.stdout
        if result.stderr:
            output += "\n" + result.stderr
        return {
            "exit_code": result.returncode,
            "output": output.strip(),
            "timed_out": False,
        }
    except subprocess.TimeoutExpired:
        return {"exit_code": -1, "output": "", "timed_out": True, "error": f"Timed out after {timeout}s"}


def run_quickjs_wasm(source: Path, timeout: int = _WASM_TIMEOUT, stdin_text: str = "") -> dict:
    if not Path(_QUICKJS_WASM).exists():
        return {"exit_code": -1, "output": "", "timed_out": False, "error": f"quickjs.wasm not found at {_QUICKJS_WASM}"}

    io_mjs = Path(__file__).resolve().parent.parent / "wasm_libs" / "js" / "io.mjs"
    src_content = source.read_text(errors="replace")
    src_content = re.sub(
        r"""import\s*\{[^}]*\}\s*from\s*['"][^'"]*io\.mjs['"];?\s*""",
        "", src_content,
    )
    combined = io_mjs.read_text(errors="replace") + "\n" + src_content

    with tempfile.NamedTemporaryFile(suffix=".mjs", delete=False, mode="w", dir="/tmp") as tmp:
        tmp.write(combined)
        tmp_path = Path(tmp.name)

    source_dir = source.parent
    cmd = [
        _WASMTIME_BIN, "run",
        "-W", f"fuel={_WASM_FUEL}",
        "-W", f"timeout={timeout}s",
        "-W", f"max-memory-size={_WASM_MAX_MEMORY}",
        "--dir", str(source_dir),
        "--dir", "/tmp",
        _QUICKJS_WASM,
        "--module", str(tmp_path),
    ]
    try:
        result = subprocess.run(
            cmd,
            input=stdin_text,
            capture_output=True,
            text=True,
            timeout=timeout + 10,
            env={**os.environ, "WASMTIME_BACKTRACE_DETAILS": "1", "RUST_BACKTRACE": "1"},
        )
        output = result.stdout
        if result.stderr:
            output += "\n" + result.stderr
        return {"exit_code": result.returncode, "output": output.strip(), "timed_out": False}
    except subprocess.TimeoutExpired:
        return {"exit_code": -1, "output": "", "timed_out": True, "error": f"Timed out after {timeout}s"}
    finally:
        tmp_path.unlink(missing_ok=True)
