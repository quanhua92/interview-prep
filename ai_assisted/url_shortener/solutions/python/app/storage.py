"""In-memory URL storage with auto-increment IDs and idempotency."""

from threading import Lock

from app import base62


class URLStorage:
    def __init__(self) -> None:
        self.alias_to_url: dict[str, str] = {}
        self.url_to_alias: dict[str, str] = {}
        self._counter: int = 0
        self._lock = Lock()

    def _next_id(self) -> int:
        """Increment counter under lock. Called from within store() which holds the lock."""
        self._counter += 1
        return self._counter

    def store(self, long_url: str) -> str:
        """Store a long URL and return its alias. Idempotent for same URL.

        The check-and-insert is atomic under a single lock, preventing
        two concurrent requests for the same URL from creating different aliases.
        """
        with self._lock:
            if long_url in self.url_to_alias:
                return self.url_to_alias[long_url]

            alias = base62.encode(self._next_id())
            self.alias_to_url[alias] = long_url
            self.url_to_alias[long_url] = alias
            return alias

    def retrieve(self, alias: str) -> str | None:
        """Look up a long URL by alias. Returns None if not found."""
        return self.alias_to_url.get(alias)

    def store_custom(self, long_url: str, alias: str) -> str:
        """Store a user-provided custom alias. Raises on collision.

        The check-and-insert is atomic under a single lock, preventing
        two concurrent requests from claiming the same custom alias.
        """
        with self._lock:
            if alias in self.alias_to_url:
                msg = f"Alias '{alias}' is already taken"
                raise ValueError(msg)

            self.alias_to_url[alias] = long_url
            self.url_to_alias[long_url] = alias
            return alias

    def exists(self, alias: str) -> bool:
        return alias in self.alias_to_url
