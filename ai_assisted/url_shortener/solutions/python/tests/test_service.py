"""Unit tests for URLShortenerService business logic."""

from concurrent.futures import ThreadPoolExecutor, as_completed

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


def test_concurrent_same_url_returns_single_alias() -> None:
    """Many threads shorten the same URL concurrently — must all get the same alias."""
    svc = URLShortenerService()
    url = "https://race.test/concurrent"
    num_threads = 50

    with ThreadPoolExecutor(max_workers=num_threads) as pool:
        futures = [pool.submit(svc.shorten, url) for _ in range(num_threads)]
        aliases = [f.result() for f in as_completed(futures)]

    # Every call must return the same alias (idempotency under contention)
    assert len(set(aliases)) == 1
    # No orphan entries — reverse mapping points to the one alias
    assert svc.storage.url_to_alias[url] == aliases[0]
    # Forward mapping is correct
    assert svc.resolve(aliases[0]) == url


def test_concurrent_custom_alias_only_one_wins() -> None:
    """Two threads race to claim the same custom alias — exactly one must win."""
    svc = URLShortenerService()
    num_threads = 50
    errors: list[Exception] = []
    successes: list[str] = []

    with ThreadPoolExecutor(max_workers=num_threads) as pool:
        futures = [
            pool.submit(
                svc.shorten,
                f"https://thread-{i}.test",
                custom_alias="contended",
            )
            for i in range(num_threads)
        ]
        for f in as_completed(futures):
            try:
                successes.append(f.result())
            except ValueError as exc:
                errors.append(exc)

    # Exactly one thread should have succeeded
    assert len(successes) == 1
    assert successes[0] == "contended"
    # All others must have gotten a ValueError
    assert len(errors) == num_threads - 1
    assert all("already taken" in str(e) for e in errors)
    # The winning URL is correctly stored
    assert svc.resolve("contended") is not None


def test_concurrent_different_urls_get_unique_aliases() -> None:
    """Many threads shorten different URLs — each must get a unique alias."""
    svc = URLShortenerService()
    num_threads = 100

    with ThreadPoolExecutor(max_workers=num_threads) as pool:
        futures = [
            pool.submit(svc.shorten, f"https://unique-{i}.test")
            for i in range(num_threads)
        ]
        aliases = [f.result() for f in as_completed(futures)]

    # All aliases must be unique (no counter collision)
    assert len(set(aliases)) == num_threads
