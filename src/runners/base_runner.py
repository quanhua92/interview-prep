"""Base runner: compile a source file, run it, and report pass/fail."""

import subprocess
import tempfile
from pathlib import Path


class CompileError(Exception):
    pass


class RunError(Exception):
    pass


class BaseRunner:
    language: str = ""
    extension: str = ""
    compile_cmd: list[str] = []
    extra_compile_flags: list[str] = []
    link_flags: list[str] = []

    @property
    def include_flags(self) -> list[str]:
        return []

    def compile(self, source: Path, out: Path) -> None:
        cmd = self.compile_cmd + self.include_flags + self.extra_compile_flags + [str(source), "-o", str(out)] + self.link_flags
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=60,
        )
        if result.returncode != 0:
            raise CompileError(f"Compilation failed:\n{result.stderr}")

    def run_binary(self, exe: Path, timeout: int = 30) -> tuple[int, str, str]:
        try:
            result = subprocess.run(
                [str(exe)],
                capture_output=True,
                text=True,
                timeout=timeout,
            )
        except subprocess.TimeoutExpired:
            raise RunError(f"Timed out after {timeout}s")
        return result.returncode, result.stdout, result.stderr

    def find_source(self, py_path: Path) -> Path:
        if py_path.suffix == ".py":
            candidate = py_path.with_suffix(self.extension)
        else:
            candidate = py_path.with_suffix(".py").with_suffix(self.extension)
        if not candidate.exists():
            raise FileNotFoundError(f"No {self.language} file found: {candidate}")
        return candidate

    stub_patterns: list[str] = []

    def _is_problem_stub(self, source: Path) -> bool:
        import re
        content = source.read_text(errors="replace")
        for pattern in self.stub_patterns:
            if re.search(pattern, content, re.MULTILINE):
                return True
        return False

    def run_all(self, py_path: Path | None = None) -> list[dict]:
        """Compile and run the source file with embedded test cases.

        The source file must have embedded test cases and print PASS/FAIL.
        Exit code 0 = all tests passed.

        Returns list of result dicts.
        """
        if py_path is None:
            raise ValueError("py_path is required")
        source = self.find_source(py_path)

        if self._is_problem_stub(source):
            return [{"status": "SKIP"}]

        with tempfile.NamedTemporaryFile(suffix=self._exe_suffix(), delete=False) as tmp:
            exe_path = Path(tmp.name)

        try:
            self.compile(source, exe_path)
        except CompileError as e:
            return [{"status": "COMPILE_ERROR", "error": str(e)}]

        try:
            exit_code, stdout, stderr = self.run_binary(exe_path)
            output = stdout + stderr

            if exit_code == 0:
                return [{"status": "PASS", "output": output.strip()}]
            else:
                return [{"status": "FAIL", "output": output.strip(), "exit_code": exit_code}]
        except RunError as e:
            return [{"status": "ERROR", "error": str(e)}]
        finally:
            exe_path.unlink(missing_ok=True)

    def _exe_suffix(self) -> str:
        return ".out"
