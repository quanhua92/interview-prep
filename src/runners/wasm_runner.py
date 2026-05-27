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
_JAVY_BIN = os.environ.get("JAVY_BIN", "javy")
_JAVY_PLUGIN_NS = "javy-default-plugin-v3"
_JAVY_PLUGIN_PATH: Path | None = None
_PYTHON_WASM = os.environ.get("PYTHON_WASM", "/opt/python-wasi/python.wasm")
_PYTHON_WASM_HOME = os.environ.get("PYTHON_WASM_HOME", "/opt/python-wasi")

_COMPILE_TIMEOUTS = {
    "c": 5,
    "cpp": 5,
    "rs": 30,
    "js": 10,
}

_WASM_FUEL = 5_000_000_000
_WASM_TIMEOUT = 120
_WASM_MAX_MEMORY = 268435456

_RSTEST_RLIB_PATH: Path | None = None


def _get_javy_plugin() -> Path | None:
    global _JAVY_PLUGIN_PATH
    if _JAVY_PLUGIN_PATH is not None and _JAVY_PLUGIN_PATH.exists():
        return _JAVY_PLUGIN_PATH
    plugin_path = _WASM_CACHE_DIR / "javy-plugin.wasm"
    _WASM_CACHE_DIR.mkdir(parents=True, exist_ok=True)
    result = subprocess.run(
        [_JAVY_BIN, "emit-plugin", "-o", str(plugin_path)],
        capture_output=True, text=True, timeout=30,
    )
    if result.returncode != 0:
        return None
    _JAVY_PLUGIN_PATH = plugin_path
    return plugin_path


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


def _compile_js(source: Path, out: Path) -> None:
    plugin = _get_javy_plugin()
    if plugin:
        cmd = [_JAVY_BIN, "build", "-C", "dynamic=y", "-C", f"plugin={plugin}", "-o", str(out), str(source)]
    else:
        cmd = [_JAVY_BIN, "build", "-o", str(out), str(source)]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["js"])
    if result.returncode != 0:
        raise RuntimeError(f"Javy compilation failed:\n{result.stderr}")


def _strip_process_exit(source_code: str) -> str:
    return re.sub(r"\bprocess\.exit\([^)]*\)\s*;?", "", source_code)


_COMPILE_FUNCS = {
    "c": _compile_c,
    "cpp": _compile_cpp,
    "rs": _compile_rust,
    "js": _compile_js,
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
            modified = _strip_process_exit(source.read_text(errors="replace"))
            tmp_src = out.with_suffix(".mjs")
            tmp_src.write_text(modified)
            _COMPILE_FUNCS[lang](tmp_src, out)
            tmp_src.unlink(missing_ok=True)
        elif lang == "py":
            raise ValueError("Python does not compile to WASM — use python.wasm directly")
        else:
            _COMPILE_FUNCS[lang](source, out)

        cached.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(out, cached)
        return cached
    finally:
        out.unlink(missing_ok=True)


def run_wasm(wasm_path: Path, source_dir: Path, timeout: int = _WASM_TIMEOUT, preload_plugin: Path | None = None) -> dict:
    cmd = [
        _WASMTIME_BIN, "run",
        "-W", f"fuel={_WASM_FUEL}",
        "-W", f"timeout={timeout}s",
        "-W", f"max-memory-size={_WASM_MAX_MEMORY}",
        "--dir", str(source_dir),
    ]
    if preload_plugin and preload_plugin.exists():
        cmd.extend(["--preload", f"{_JAVY_PLUGIN_NS}={preload_plugin}"])
    cmd.append(str(wasm_path))
    try:
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=timeout + 10,
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
    except FileNotFoundError:
        return {"exit_code": -1, "output": "", "timed_out": False, "error": "wasmtime not found. Install wasmtime to use the WASM sandbox."}


def run_python_wasm(source: Path, project_root: Path, timeout: int = _WASM_TIMEOUT) -> dict:
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
            capture_output=True,
            text=True,
            timeout=timeout + 10,
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
