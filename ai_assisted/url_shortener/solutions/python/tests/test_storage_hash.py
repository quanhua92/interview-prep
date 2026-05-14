"""Tests for hash-based URL storage."""

import pytest

from app.storage_hash import HashURLStorage


def test_store_returns_7_char_alias() -> None:
    s = HashURLStorage()
    alias = s.store("https://example.com")
    assert len(alias) == 7
    assert alias.isalnum()


def test_idempotent_same_url_same_alias() -> None:
    s = HashURLStorage()
    a1 = s.store("https://example.com")
    a2 = s.store("https://example.com")
    assert a1 == a2


def test_different_urls_different_aliases() -> None:
    s = HashURLStorage()
    a1 = s.store("https://a.com")
    a2 = s.store("https://b.com")
    assert a1 != a2


def test_retrieve_stored_url() -> None:
    s = HashURLStorage()
    alias = s.store("https://example.com")
    assert s.retrieve(alias) == "https://example.com"


def test_retrieve_unknown_returns_none() -> None:
    s = HashURLStorage()
    assert s.retrieve("missing") is None


def test_custom_alias() -> None:
    s = HashURLStorage()
    alias = s.store_custom("https://custom.com", "mylink")
    assert alias == "mylink"
    assert s.retrieve("mylink") == "https://custom.com"


def test_custom_alias_collision_raises() -> None:
    s = HashURLStorage()
    s.store_custom("https://first.com", "taken")
    with pytest.raises(ValueError, match="already taken"):
        s.store_custom("https://second.com", "taken")


def test_custom_alias_idempotent_same_url() -> None:
    s = HashURLStorage()
    a1 = s.store_custom("https://same.com", "mylink")
    a2 = s.store_custom("https://same.com", "mylink")
    assert a1 == a2


def test_no_url_to_alias_dict_needed() -> None:
    """Hash storage only uses alias_to_url — no reverse mapping dict."""
    s = HashURLStorage()
    assert not hasattr(s, "url_to_alias")
    s.store("https://example.com")
    assert len(s.alias_to_url) == 1


def test_hash_service_integration() -> None:
    """Full shorten→resolve flow using hash-based storage via service."""
    from app.service import URLShortenerService

    svc = URLShortenerService(storage=HashURLStorage())
    alias = svc.shorten("https://hash-service.test")
    assert svc.resolve(alias) == "https://hash-service.test"

    # Idempotent
    a2 = svc.shorten("https://hash-service.test")
    assert a2 == alias

    # Custom alias
    svc.shorten("https://custom.test", custom_alias="mine")
    assert svc.resolve("mine") == "https://custom.test"
