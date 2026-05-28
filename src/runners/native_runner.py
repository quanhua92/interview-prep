"""Native runner: compile and execute solutions without WASM sandbox."""

import hashlib
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

_NATIVE_CACHE_DIR = Path(os.environ.get("WASM_CACHE_DIR", "/tmp/wasm-cache")) / "native"

_WASM_LIBS_DIR = Path("src/wasm_libs")

_COMPILED_RLIB: Path | None = None

_COMPILE_TIMEOUTS = {
    "c": 5,
    "cpp": 5,
    "rs": 30,
}


def _native_cache_path(content: bytes, suffix: str = "") -> Path:
    _NATIVE_CACHE_DIR.mkdir(parents=True, exist_ok=True)
    h = hashlib.md5(content).hexdigest()
    return _NATIVE_CACHE_DIR / f"{h}{suffix}"


def _run_native(binary_path: Path, stdin_text: str = "", timeout: int = 120) -> dict:
    cmd = [str(binary_path)]
    try:
        result = subprocess.run(
            cmd,
            input=stdin_text,
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
        return {"exit_code": -1, "output": "", "timed_out": True}
    except FileNotFoundError:
        return {"exit_code": -1, "output": f"Binary not found: {binary_path}", "timed_out": False}


def run_python_native(target: Path, project_root: Path, stdin_text: str = "", timeout: int = 120) -> dict:
    python_bin = os.environ.get("PYTHON_BIN", "python3")
    cmd = [python_bin, str(target)]
    try:
        result = subprocess.run(
            cmd,
            input=stdin_text,
            capture_output=True,
            text=True,
            timeout=timeout + 10,
            cwd=str(project_root),
            env={**os.environ, "PYTHONPATH": str(project_root)},
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
        return {"exit_code": -1, "output": f"Python not found: {python_bin}", "timed_out": False}


def run_js_native(target: Path, stdin_text: str = "", timeout: int = 120) -> dict:
    node_bin = os.environ.get("NODE_BIN", "node")
    io_node_mjs = _WASM_LIBS_DIR / "js" / "io_node.mjs"

    src_content = target.read_text(errors="replace")
    src_content = re.sub(
        r"""import\s*\{[^}]*\}\s*from\s*['"][^'"]*io\.mjs['"];?\s*""",
        "", src_content,
    )
    combined = io_node_mjs.read_text(errors="replace") + "\n" + src_content

    with tempfile.NamedTemporaryFile(suffix=".mjs", delete=False, mode="w", dir="/tmp") as tmp:
        tmp.write(combined)
        tmp_path = Path(tmp.name)

    cmd = [node_bin, str(tmp_path)]
    try:
        result = subprocess.run(
            cmd,
            input=stdin_text,
            capture_output=True,
            text=True,
            timeout=timeout + 10,
        )
        output = result.stdout
        if result.stderr:
            output += "\n" + result.stderr
        return {"exit_code": result.returncode, "output": output.strip(), "timed_out": False}
    except subprocess.TimeoutExpired:
        return {"exit_code": -1, "output": "", "timed_out": True}
    except FileNotFoundError:
        return {"exit_code": -1, "output": f"Node not found: {node_bin}", "timed_out": False}
    finally:
        tmp_path.unlink(missing_ok=True)


def _compile_rust_lib() -> Path:
    global _COMPILED_RLIB
    if _COMPILED_RLIB is not None and _COMPILED_RLIB.exists():
        return _COMPILED_RLIB
    lib_out = _NATIVE_CACHE_DIR / "libwasm_libs_native.rlib"
    _NATIVE_CACHE_DIR.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [
            "rustc", "--edition", "2024", "-O",
            str(_WASM_LIBS_DIR / "rs" / "lib.rs"),
            "--crate-type", "lib", "--crate-name", "wasm_libs",
            "-o", str(lib_out),
        ],
        capture_output=True, text=True, timeout=60, check=True,
    )
    _COMPILED_RLIB = lib_out
    return lib_out


def _native_compile_c(source: Path, out: Path) -> None:
    cmd = [
        os.environ.get("CC", "gcc"),
        "-O2", "-Wall", "-Wextra",
        f"-I{_WASM_LIBS_DIR / 'c'}",
        str(source),
        str(_WASM_LIBS_DIR / "c" / "io.c"),
        "-o", str(out), "-lm",
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["c"])
    if result.returncode != 0:
        raise RuntimeError(f"C native compilation failed:\n{result.stderr}")


def _native_compile_cpp(source: Path, out: Path) -> None:
    cmd = [
        os.environ.get("CXX", "g++"),
        "-O2", "-Wall", "-Wextra",
        f"-I{_WASM_LIBS_DIR / 'cpp'}",
        str(source),
        str(_WASM_LIBS_DIR / "cpp" / "io.cpp"),
        "-o", str(out),
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["cpp"])
    if result.returncode != 0:
        raise RuntimeError(f"C++ native compilation failed:\n{result.stderr}")


def _native_compile_rust(source: Path, out: Path) -> None:
    lib_out = _compile_rust_lib()
    cmd = [
        "rustc", "--edition", "2024", "-O",
        str(source), "--extern", f"wasm_libs={lib_out}",
        "-o", str(out),
    ]
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=_COMPILE_TIMEOUTS["rs"])
    if result.returncode != 0:
        raise RuntimeError(f"Rust native compilation failed:\n{result.stderr}")


_NATIVE_COMPILE_FUNCS = {
    "c": _native_compile_c,
    "cpp": _native_compile_cpp,
    "rs": _native_compile_rust,
}


def run_compiled_native(source: Path, lang: str, stdin_text: str = "", timeout: int = 120) -> dict:
    compile_fn = _NATIVE_COMPILE_FUNCS.get(lang)
    if not compile_fn:
        return {"exit_code": -1, "output": f"No native compiler for {lang}", "timed_out": False}

    content = source.read_bytes()
    cached = _native_cache_path(content, suffix=".native")
    if not cached.exists():
        with tempfile.NamedTemporaryFile(suffix=".native", delete=False, dir="/tmp") as tmp:
            out = Path(tmp.name)
        try:
            compile_fn(source, out)
            cached.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(out, cached)
        finally:
            out.unlink(missing_ok=True)

    return _run_native(cached, stdin_text=stdin_text, timeout=timeout)
