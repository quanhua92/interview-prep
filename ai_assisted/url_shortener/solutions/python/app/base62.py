"""Base62 encoding/decoding for URL alias generation."""

CHARSET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
BASE = len(CHARSET)
CHAR_TO_VAL = {c: i for i, c in enumerate(CHARSET)}
ALIAS_LENGTH = 7


def encode(num: int) -> str:
    """Encode a non-negative integer to a zero-padded 7-character Base62 string."""
    if num < 0:
        msg = f"encode() requires a non-negative integer, got {num}"
        raise ValueError(msg)
    if num == 0:
        return "0" * ALIAS_LENGTH

    chars: list[str] = []
    while num > 0:
        chars.append(CHARSET[num % BASE])
        num //= BASE

    result = "".join(reversed(chars))
    return result.zfill(ALIAS_LENGTH)


def decode(s: str) -> int:
    """Decode a Base62 string back to an integer."""
    result = 0
    for c in s:
        result = result * BASE + CHAR_TO_VAL[c]
    return result
