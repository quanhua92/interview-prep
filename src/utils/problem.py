"""Base Problem class and TestCase for running solutions with instant feedback."""

from dataclasses import dataclass, field
from typing import Any


@dataclass
class TestCase:
    """A single test case: input, expected output, and optional label."""
    input: Any
    expected: Any
    label: str = ""


class Problem:
    """Base class for solved LeetCode-style problems.

    Subclasses set:
        - name: human-readable problem title
        - test_cases: list[TestCase]

    And implement solve() matching the LeetCode signature.

    Usage (standalone):
        python tier1/sliding_window/p003_longest_substring.py
    """

    name: str = ""
    test_cases: list[TestCase] = field(default_factory=list)

    def solve(self, *args, **kwargs) -> Any:
        raise NotImplementedError

    def run(self) -> bool:
        """Run all test cases, print results, return True if all pass."""
        print(f"\n{'='*60}")
        print(f"  {self.name}")
        print(f"{'='*60}")

        all_passed = True
        self._results: dict[int, str] = {}
        for i, tc in enumerate(self.test_cases, 1):
            label = f" ({tc.label})" if tc.label else ""
            try:
                if isinstance(tc.input, tuple):
                    result = self.solve(*tc.input)
                elif isinstance(tc.input, dict):
                    result = self.solve(**tc.input)
                else:
                    result = self.solve(tc.input)

                passed = result == tc.expected
                status = "PASS" if passed else "FAIL"
                self._results[i] = status
                if not passed:
                    all_passed = False
                print(f"  Test {i}{label}: {status}")
                if not passed:
                    print(f"    Input:    {tc.input}")
                    print(f"    Expected: {tc.expected}")
                    print(f"    Got:      {result}")
            except Exception as e:
                all_passed = False
                self._results[i] = "ERROR"
                print(f"  Test {i}{label}: ERROR — {e}")

        total = len(self.test_cases)
        passed_count = sum(1 for v in self._results.values() if v == "PASS")
        print(f"\n  {passed_count}/{total} passed")
        print(f"{'='*60}\n")
        return all_passed


if __name__ == "__main__":
    print("Import a specific problem file and call Problem.run()")
