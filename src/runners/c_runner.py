"""Runner for C solutions (.c)."""


from .base_runner import BaseRunner


class CRunner(BaseRunner):
    language = "C"
    extension = ".c"
    compile_cmd = ["gcc", "-O2", "-Wall", "-Wextra"]
    link_flags = ["-lm"]
    stub_patterns = [r"(?<!\S)abort\(\)"]

    @property
    def include_flags(self) -> list[str]:
        return ["-Isrc/runners"]
