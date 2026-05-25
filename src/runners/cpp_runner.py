"""Runner for C++ solutions (.cpp)."""

from .base_runner import BaseRunner


class CppRunner(BaseRunner):
    language = "C++"
    extension = ".cpp"
    compile_cmd = ["g++", "-std=c++17", "-O2", "-Wall", "-Wextra"]
    stub_patterns = [r"(?<!\S)/\*\s*TODO\s*:\s*Implement"]

    @property
    def include_flags(self) -> list[str]:
        return ["-Isrc/runners"]
