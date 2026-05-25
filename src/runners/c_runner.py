"""Runner for C solutions (.c)."""


from .base_runner import BaseRunner


class CRunner(BaseRunner):
    language = "C"
    extension = ".c"
    compile_cmd = ["gcc", "-O2", "-Wall", "-Wextra"]

    @property
    def include_flags(self) -> list[str]:
        return ["-Isrc/runners"]
