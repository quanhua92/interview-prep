"""Hash-based URL storage — aliases derived from SHA-256 of the URL itself."""

import hashlib
from threading import Lock

from app import base62


def _hash_url(url: str, salt: int = 0) -> str:
    """Hash a URL (optionally salted) to a 7-character Base62 alias."""
    data = url.encode()
    if salt > 0:
        data += str(salt).encode()
    digest = hashlib.sha256(data).digest()
    num = int.from_bytes(digest[:8]) % (base62.BASE ** base62.ALIAS_LENGTH)
    return base62.encode(num)


class HashURLStorage:
    """Storage where the alias is derived from the URL's hash.

    Key difference from auto-increment storage:
    - No url_to_alias dict needed — idempotency is implicit (same URL → same hash).
    - Only one dict (alias_to_url) instead of two.
    - Collision handling via deterministic salt-based retry.
    - Lock scope is smaller: only needed for insert, not for idempotency detection.
    """

    def __init__(self) -> None:
        self.alias_to_url: dict[str, str] = {}
        self._lock = Lock()

    def store(self, long_url: str) -> str:
        """Store a URL using its hash as alias. Retries with salt on collision."""
        with self._lock:
            salt = 0
            while True:
                alias = _hash_url(long_url, salt)
                if alias not in self.alias_to_url:
                    self.alias_to_url[alias] = long_url
                    return alias
                if self.alias_to_url[alias] == long_url:
                    return alias  # idempotent — same URL, same slot
                salt += 1  # collision with a different URL, retry

    def retrieve(self, alias: str) -> str | None:
        return self.alias_to_url.get(alias)

    def store_custom(self, long_url: str, alias: str) -> str:
        """Store a custom alias. Idempotent if same URL, raises on collision."""
        with self._lock:
            if alias in self.alias_to_url:
                if self.alias_to_url[alias] == long_url:
                    return alias  # idempotent
                msg = f"Alias '{alias}' is already taken"
                raise ValueError(msg)
            self.alias_to_url[alias] = long_url
            return alias

    def exists(self, alias: str) -> bool:
        return alias in self.alias_to_url
