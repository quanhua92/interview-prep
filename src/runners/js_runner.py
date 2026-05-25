import subprocess

from .base_runner import BaseRunner


class JSRunner(BaseRunner):
    language = "JavaScript"
    extension = ".mjs"
    stub_patterns = [r"(?<!\S)throw\s+new\s+Error\(\"NotImplementedError\"\)"]

    def run_all(self, py_path=None) -> list[dict]:
        if py_path is None:
            raise ValueError("py_path is required")
        source = self.find_source(py_path)

        if self._is_problem_stub(source):
            return [{"status": "SKIP"}]

        try:
            result = subprocess.run(
                ["node", "--trace-uncaught", str(source)],
                capture_output=True,
                text=True,
                timeout=30,
            )
        except subprocess.TimeoutExpired:
            return [{"status": "ERROR", "error": "Timed out after 30s"}]
        except FileNotFoundError:
            return [{"status": "ERROR", "error": "node not found. Install Node.js to run JavaScript problems."}]

        output = result.stdout + result.stderr

        if result.returncode == 0:
            return [{"status": "PASS", "output": output.strip()}]
        else:
            return [{"status": "FAIL", "output": output.strip(), "exit_code": result.returncode}]
