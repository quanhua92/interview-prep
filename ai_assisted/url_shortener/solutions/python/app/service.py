"""Business logic layer orchestrating storage, cache, and analytics."""

from app.analytics import AnalyticsTracker
from app.cache import LRUCache
from app.storage import URLStorage

BASE_SHORT_URL = "https://short.url"


class URLShortenerService:
    def __init__(self) -> None:
        self.storage = URLStorage()
        self.cache = LRUCache(capacity=10_000, ttl=300.0)
        self.analytics = AnalyticsTracker()

    def shorten(self, long_url: str, custom_alias: str | None = None) -> str:
        """Create or retrieve a short alias for the given URL."""
        # Check idempotency first
        existing = self.storage.url_to_alias.get(long_url)
        if existing:
            return existing

        if custom_alias:
            alias = self.storage.store_custom(long_url, custom_alias)
        else:
            alias = self.storage.store(long_url)

        # Warm the cache immediately
        self.cache.put(alias, long_url)
        return alias

    def resolve(self, alias: str) -> str | None:
        """Resolve alias to long URL, checking cache then storage."""
        # Check cache first
        cached = self.cache.get(alias)
        if cached is not None:
            self.analytics.record_click(alias)
            return cached

        # Fall through to storage
        long_url = self.storage.retrieve(alias)
        if long_url is not None:
            self.cache.put(alias, long_url)
            self.analytics.record_click(alias)
            return long_url

        return None

    def get_analytics(self, alias: str) -> int:
        return self.analytics.get_clicks(alias)

    def get_top_urls(self, n: int = 10) -> list[tuple[str, int]]:
        return self.analytics.get_top(n)
