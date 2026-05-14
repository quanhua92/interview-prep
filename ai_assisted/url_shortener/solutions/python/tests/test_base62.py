"""Unit tests for Base62 encoding/decoding."""

import pytest

from app.base62 import ALIAS_LENGTH, decode, encode


def test_encode_zero() -> None:
    assert encode(0) == "0" * ALIAS_LENGTH


def test_encode_positive() -> None:
    result = encode(1)
    assert result == "0000001"


def test_encode_always_7_chars() -> None:
    for n in [0, 1, 61, 62, 100, 999_999, 3_500_000_000_000]:
        assert len(encode(n)) == 7


def test_encode_decode_roundtrip() -> None:
    for n in [0, 1, 42, 62, 3844, 100_000, 999_999_999]:
        assert decode(encode(n)) == n


def test_decode_all_charsets() -> None:
    # 'a' = 10, 'Z' = 61
    assert decode("000000a") == 10
    assert decode("000000Z") == 61
    assert decode("0000010") == 62


def test_encode_negative_raises() -> None:
    with pytest.raises(ValueError, match="non-negative"):
        encode(-1)
