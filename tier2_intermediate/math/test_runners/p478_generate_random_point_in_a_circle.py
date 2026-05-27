from src.utils.judge_base import JudgeBase, TestCase, register


class P478GenerateRandomPointInACircle(JudgeBase):
    name = "478. Generate Random Point in a Circle"
    test_cases = [
        TestCase(input=(1.0, 0.0, 0.0, 1000), expected=(1.0, 0.0, 0.0, 1000), label="points within unit circle"),
        TestCase(input=(0.5, 1.0, 2.0, 1000), expected=(0.5, 1.0, 2.0, 1000), label="points within offset circle"),
        TestCase(input=(0.01, 0.0, 0.0, 100), expected=(0.01, 0.0, 0.0, 100), label="tiny circle"),
        TestCase(input=(5.0, -100.0, 200.0, 500), expected=(5.0, -100.0, 200.0, 500), label="large offset center"),
        TestCase(input=(1.0, 0.0, 0.0, 1), expected=(1.0, 0.0, 0.0, 1), label="single point"),
    ]

    def to_stdin(self, tc_input) -> str:
        radius, x_center, y_center, count = tc_input
        return self.serialize_multi(
            f"{radius} {x_center} {y_center}\n",
            self.serialize_int(count),
        )

    def check_stdout(self, stdout: str, tc_expected) -> bool:
        r, cx, cy, count = tc_expected
        lines = [ln.strip() for ln in stdout.strip().split("\n") if ln.strip()]
        if len(lines) != count:
            return False
        for line in lines:
            parts = line.split()
            x, y = float(parts[0]), float(parts[1])
            if (x - cx) ** 2 + (y - cy) ** 2 > r * r + 1e-9:
                return False
        return True


register(P478GenerateRandomPointInACircle)
