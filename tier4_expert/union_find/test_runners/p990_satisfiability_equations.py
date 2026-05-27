from src.utils.judge_base import JudgeBase, TestCase, register


class P990SatisfiabilityEquations(JudgeBase):
    name = "990. Satisfiability of Equality Equations"
    test_cases = [
        TestCase(input=["a==b", "b!=a"], expected=False, label="example 1"),
        TestCase(input=["b==a", "a==b"], expected=True, label="example 2"),
        TestCase(input=["a==b", "b==c", "a==c"], expected=True, label="example 3"),
        TestCase(input=["a!=a"], expected=False, label="contradiction"),
        TestCase(
            input=["a!=b", "b!=c", "c!=a"],
            expected=True,
            label="all different no contradiction",
        ),
        TestCase(
            input=["a==b", "b==c", "c==d", "a!=d"],
            expected=False,
            label="chain equality then inequality",
        ),
        TestCase(input=["a==b", "c!=d"], expected=True, label="independent groups"),
        TestCase(input=["a==a"], expected=True, label="self equality"),
    ]

    def to_stdin(self, tc_input) -> str:
        lines = [str(len(tc_input))]
        for eq in tc_input:
            lines.append(eq)
        return "\n".join(lines) + "\n"

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        return self.parse_bool(stdout) == tc_expected


register(P990SatisfiabilityEquations)
