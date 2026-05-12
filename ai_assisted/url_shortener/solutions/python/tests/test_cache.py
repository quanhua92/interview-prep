"""Unit tests for LRU cache."""

import time
from unittest.mock import patch

from app.cache import LRUCache


def test_get_put_basic() -> None:
    cache = LRUCache(capacity=3)
    cache.put("a", "url-a")
    assert cache.get("a") == "url-a"
    assert cache.get("missing") is None


def test_eviction_at_capacity() -> None:
    cache = LRUCache(capacity=2)
    cache.put("a", "url-a")
    cache.put("b", "url-b")
    cache.put("c", "url-c")  # should evict "a"
    assert cache.get("a") is None
    assert cache.get("b") == "url-b"
    assert cache.get("c") == "url-c"


def test_lru_order_updated_on_get() -> None:
    cache = LRUCache(capacity=2)
    cache.put("a", "url-a")
    cache.put("b", "url-b")
    cache.get("a")  # access "a" so it's now most recent
    cache.put("c", "url-c")  # should evict "b" (LRU), not "a"
    assert cache.get("a") == "url-a"
    assert cache.get("b") is None


def test_ttl_expiration() -> None:
    cache = LRUCache(capacity=10, ttl=5.0)
    cache.put("a", "url-a")

    # Mock time to simulate expiration
    with patch("app.cache.time.monotonic", return_value=time.monotonic() + 10):
        assert cache.get("a") is None


def test_put_updates_existing_key() -> None:
    cache = LRUCache(capacity=2)
    cache.put("a", "old")
    cache.put("a", "new")
    assert cache.get("a") == "new"
    assert cache.size == 1


def test_invalidate() -> None:
    cache = LRUCache(capacity=10)
    cache.put("a", "url-a")
    cache.invalidate("a")
    assert cache.get("a") is None


def test_clear() -> None:
    cache = LRUCache(capacity=10)
    cache.put("a", "url-a")
    cache.put("b", "url-b")
    cache.clear()
    assert cache.size == 0
