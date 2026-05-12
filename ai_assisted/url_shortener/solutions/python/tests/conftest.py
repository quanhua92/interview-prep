"""Shared test fixtures."""

import pytest_asyncio
from httpx import ASGITransport, AsyncClient

from app.main import app
from app.service import URLShortenerService


@pytest_asyncio.fixture
async def client() -> AsyncClient:
    """Provide an httpx AsyncClient wired to the FastAPI app."""
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as ac:
        yield ac


@pytest_asyncio.fixture(autouse=True)
async def _reset_service():
    """Reset app state between tests for isolation."""
    app.state.service = URLShortenerService()
    yield
