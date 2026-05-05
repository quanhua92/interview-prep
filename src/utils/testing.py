"""Assertion helpers for use in tests and Problem.run()."""


def assert_equals(actual, expected, msg: str = ""):
    """Assert two values are equal with an optional message."""
    assert actual == expected, (
        f"{msg}\n  Expected: {expected}\n  Got:      {actual}"
        if msg else f"Expected {expected}, got {actual}"
    )


def assert_true(value, msg: str = ""):
    """Assert a value is truthy."""
    assert value, msg or f"Expected True, got {value}"


def assert_false(value, msg: str = ""):
    """Assert a value is falsy."""
    assert not value, msg or f"Expected False, got {value}"
