"""LRU cache with optional TTL support for hot URL resolution."""

import time
from collections import OrderedDict


class LRUCache:
    def __init__(self, capacity: int = 10_000, ttl: float | None = None) -> None:
        self.capacity = capacity
        self.ttl = ttl  # seconds; None means no expiration
        self._cache: OrderedDict[str, tuple[str, float]] = OrderedDict()

    def get(self, key: str) -> str | None:
        """Return cached value or None on miss / expiry."""
        if key not in self._cache:
            return None

        value, inserted_at = self._cache[key]

        if self.ttl is not None and (time.monotonic() - inserted_at) > self.ttl:
            del self._cache[key]
            return None

        # Move to end (most recently used)
        self._cache.move_to_end(key)
        return value

    def put(self, key: str, value: str) -> None:
        """Insert or update an entry, evicting LRU if at capacity."""
        if key in self._cache:
            self._cache.move_to_end(key)
            self._cache[key] = (value, time.monotonic())
            return

        if len(self._cache) >= self.capacity:
            self._cache.popitem(last=False)  # evict oldest

        self._cache[key] = (value, time.monotonic())

    def invalidate(self, key: str) -> None:
        self._cache.pop(key, None)

    def clear(self) -> None:
        self._cache.clear()

    @property
    def size(self) -> int:
        return len(self._cache)
