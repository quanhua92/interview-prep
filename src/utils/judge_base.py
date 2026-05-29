from __future__ import annotations

import sys
from dataclasses import dataclass
from typing import Any

_OUT_PREFIX = "[OUT] "

_REGISTRY: dict[str, type] = {}


def register(cls: type) -> type:
    _REGISTRY[cls.__name__] = cls
    return cls


def get_judge(name: str):
    for cls in _REGISTRY.values():
        if hasattr(cls, "name") and cls.name == name:
            return cls
    raise KeyError(f"No judge registered with name={name!r}")


def list_judges():
    return {cls.name: cls for cls in _REGISTRY.values() if hasattr(cls, "name")}


def strip_output_prefix(stdout: str) -> str:
    out_lines = []
    for line in stdout.split("\n"):
        stripped = line.strip()
        if stripped.startswith(_OUT_PREFIX):
            out_lines.append(stripped[len(_OUT_PREFIX):])
    return "\n".join(out_lines)


@dataclass
class TestCase:
    input: Any
    expected: Any
    label: str = ""


class JudgeBase:
    name: str = ""
    test_cases: list[TestCase] = []

    def to_stdin(self, tc_input) -> str:
        raise NotImplementedError

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        raise NotImplementedError

    # --- shared serializers ---

    def serialize_int(self, n: int) -> str:
        return f"{n}\n"

    def serialize_int_array(self, arr) -> str:
        return " ".join(str(x) for x in arr) + "\n"

    def serialize_int_matrix(self, mat) -> str:
        if not mat:
            return "0\n"
        rows = len(mat)
        cols = len(mat[0]) if mat else 0
        lines = [f"{cols}"]
        for row in mat:
            lines.append(" ".join(str(x) for x in row))
        return "\n".join(lines) + "\n"

    def serialize_string(self, s: str) -> str:
        return s + "\n"

    def serialize_bool(self, b: bool) -> str:
        return "true\n" if b else "false\n"

    def serialize_multi(self, *parts: str) -> str:
        return "".join(parts)

    # --- shared parsers ---

    def parse_int(self, stdout: str) -> int:
        return int(stdout.strip())

    def parse_int_array(self, stdout: str) -> list[int]:
        text = stdout.strip()
        if not text:
            return []
        return [int(x) for x in text.split()]

    def parse_int_matrix(self, stdout: str) -> list[list[int]]:
        text = stdout.strip()
        if not text:
            return []
        lines = [l.strip() for l in text.split("\n") if l.strip()]
        return [list(map(int, l.split())) for l in lines]

    def parse_string(self, stdout: str) -> str:
        return stdout.strip()

    def parse_bool(self, stdout: str) -> bool:
        return stdout.strip().lower() == "true"
