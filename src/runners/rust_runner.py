"""Runner for Rust solutions (.rs)."""

import subprocess
from pathlib import Path

from .base_runner import BaseRunner, CompileError


class RustRunner(BaseRunner):
    language = "Rust"
    extension = ".rs"
    compile_cmd = ["rustc", "--edition", "2024", "-O"]
    stub_patterns = [r"(?<!\S)todo!\(\)"]

    def compile(self, source: Path, out: Path) -> None:
        test_lib = Path("src/runners/rstest.rs")
        lib_out = out.parent / "librstest.rlib"
        subprocess.run(
            ["rustc", "--edition", "2024", "-O", str(test_lib),
             "--crate-type", "lib", "--crate-name", "rstest", "-o", str(lib_out)],
            capture_output=True, text=True, timeout=60,
            check=True,
        )
        cmd = self.compile_cmd + [str(source), "--extern", f"rstest={lib_out}", "-o", str(out)]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
        lib_out.unlink(missing_ok=True)
        if result.returncode != 0:
            raise CompileError(f"Compilation failed:\n{result.stderr}")
