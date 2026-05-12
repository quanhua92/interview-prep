"""Unit tests for URLShortenerService business logic."""

from app.service import URLShortenerService


def test_shorten_and_resolve() -> None:
    svc = URLShortenerService()
    alias = svc.shorten("https://example.com")
    assert svc.resolve(alias) == "https://example.com"


def test_idempotency() -> None:
    svc = URLShortenerService()
    a1 = svc.shorten("https://example.com")
    a2 = svc.shorten("https://example.com")
    assert a1 == a2


def test_resolve_unknown_returns_none() -> None:
    svc = URLShortenerService()
    assert svc.resolve("unknown") is None


def test_custom_alias() -> None:
    svc = URLShortenerService()
    alias = svc.shorten("https://custom.com", custom_alias="mylink")
    assert alias == "mylink"
    assert svc.resolve("mylink") == "https://custom.com"


def test_custom_alias_collision_raises() -> None:
    svc = URLShortenerService()
    svc.shorten("https://first.com", custom_alias="taken")
    import pytest

    with pytest.raises(ValueError, match="already taken"):
        svc.shorten("https://second.com", custom_alias="taken")


def test_cache_hit_skips_storage() -> None:
    svc = URLShortenerService()
    alias = svc.shorten("https://cached.com")

    # First resolve populates cache
    svc.resolve(alias)
    # Remove from storage to verify cache is hit
    del svc.storage.alias_to_url[alias]

    # Should still resolve via cache
    assert svc.resolve(alias) == "https://cached.com"


def test_cache_miss_falls_through_to_storage() -> None:
    svc = URLShortenerService()
    alias = svc.shorten("https://miss.com")

    # Clear cache to force miss
    svc.cache.clear()

    # Should still resolve via storage
    assert svc.resolve(alias) == "https://miss.com"


def test_analytics_tracking() -> None:
    svc = URLShortenerService()
    alias = svc.shorten("https://tracked.com")

    for _ in range(5):
        svc.resolve(alias)

    assert svc.get_analytics(alias) == 5


def test_top_urls() -> None:
    svc = URLShortenerService()
    a1 = svc.shorten("https://a.com")
    a2 = svc.shorten("https://b.com")

    for _ in range(10):
        svc.resolve(a1)
    for _ in range(3):
        svc.resolve(a2)

    top = svc.get_top_urls(n=2)
    assert top[0][0] == a1
    assert top[0][1] == 10
    assert top[1][0] == a2
    assert top[1][1] == 3
