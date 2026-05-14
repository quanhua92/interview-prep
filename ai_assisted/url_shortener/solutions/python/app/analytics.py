"""Click analytics with buffered writes simulating async write-behind."""

from collections import Counter, deque


class AnalyticsTracker:
    def __init__(self, buffer_size: int = 100) -> None:
        self._counter: Counter[str] = Counter()
        self._buffer: deque[str] = deque(maxlen=buffer_size)
        self._buffer_size = buffer_size

    def record_click(self, alias: str) -> None:
        """Buffer a click event (fire-and-forget). Auto-flushes when buffer is full."""
        if len(self._buffer) >= self._buffer_size:
            self._flush()
        self._buffer.append(alias)

    def _flush(self) -> None:
        """Flush buffered clicks into the counter."""
        while self._buffer:
            alias = self._buffer.popleft()
            self._counter[alias] += 1

    def get_clicks(self, alias: str) -> int:
        """Return total clicks for an alias (flushes first for accuracy)."""
        self._flush()
        return self._counter.get(alias, 0)

    def get_top(self, n: int = 10) -> list[tuple[str, int]]:
        """Return top-N aliases by click count."""
        self._flush()
        return self._counter.most_common(n)
