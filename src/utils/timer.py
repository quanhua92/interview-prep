"""Timing utilities for measuring solution performance."""

import time
from functools import wraps
from contextlib import contextmanager


@contextmanager
def Timer(name: str = ""):
    """Context manager that times a block of code.

    Usage:
        with Timer("solution"):
            result = solve(input)
    """
    start = time.perf_counter()
    yield
    elapsed = time.perf_counter() - start
    if name:
        print(f"  [{name}] {elapsed*1000:.2f} ms")
    else:
        print(f"  {elapsed*1000:.2f} ms")


def timed(func):
    """Decorator that prints execution time of a function.

    Usage:
        @timed
        def solve(nums):
            ...
    """
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        print(f"  [{func.__name__}] {elapsed*1000:.2f} ms")
        return result
    return wrapper
