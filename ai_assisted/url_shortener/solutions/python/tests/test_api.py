"""Integration tests for HTTP endpoints."""

import pytest
from httpx import AsyncClient


@pytest.mark.asyncio
async def test_shorten_returns_valid_alias(client: AsyncClient) -> None:
    resp = await client.post("/shorten", json={"long_url": "https://example.com"})
    assert resp.status_code == 200
    data = resp.json()
    assert "alias" in data
    assert len(data["alias"]) == 7
    assert data["short_url"].endswith(data["alias"])


@pytest.mark.asyncio
async def test_shorten_idempotent(client: AsyncClient) -> None:
    resp1 = await client.post("/shorten", json={"long_url": "https://example.com"})
    resp2 = await client.post("/shorten", json={"long_url": "https://example.com"})
    assert resp1.json()["alias"] == resp2.json()["alias"]


@pytest.mark.asyncio
async def test_redirect_returns_302(client: AsyncClient) -> None:
    create = await client.post("/shorten", json={"long_url": "https://example.com"})
    alias = create.json()["alias"]
    resp = await client.get(f"/{alias}", follow_redirects=False)
    assert resp.status_code == 302
    assert resp.headers["location"] == "https://example.com"


@pytest.mark.asyncio
async def test_redirect_unknown_returns_404(client: AsyncClient) -> None:
    resp = await client.get("/zzzzzzz", follow_redirects=False)
    assert resp.status_code == 404


@pytest.mark.asyncio
async def test_custom_alias(client: AsyncClient) -> None:
    resp = await client.post(
        "/shorten",
        json={"long_url": "https://custom.com", "custom_alias": "mylink"},
    )
    assert resp.status_code == 200
    assert resp.json()["alias"] == "mylink"


@pytest.mark.asyncio
async def test_custom_alias_collision_returns_409(client: AsyncClient) -> None:
    await client.post(
        "/shorten",
        json={"long_url": "https://first.com", "custom_alias": "taken"},
    )
    resp = await client.post(
        "/shorten",
        json={"long_url": "https://second.com", "custom_alias": "taken"},
    )
    assert resp.status_code == 409


@pytest.mark.asyncio
async def test_analytics_click_count(client: AsyncClient) -> None:
    create = await client.post("/shorten", json={"long_url": "https://clicks.com"})
    alias = create.json()["alias"]

    # Click 3 times via redirect
    for _ in range(3):
        await client.get(f"/{alias}", follow_redirects=False)

    resp = await client.get(f"/analytics/{alias}")
    assert resp.status_code == 200
    assert resp.json()["clicks"] == 3


@pytest.mark.asyncio
async def test_analytics_top_urls(client: AsyncClient) -> None:
    a1 = await client.post("/shorten", json={"long_url": "https://a.com"})
    a2 = await client.post("/shorten", json={"long_url": "https://b.com"})
    alias1 = a1.json()["alias"]
    alias2 = a2.json()["alias"]

    # alias1 gets 5 clicks, alias2 gets 2
    for _ in range(5):
        await client.get(f"/{alias1}", follow_redirects=False)
    for _ in range(2):
        await client.get(f"/{alias2}", follow_redirects=False)

    resp = await client.get("/analytics/top")
    assert resp.status_code == 200
    urls = resp.json()["urls"]
    assert len(urls) >= 2
    assert urls[0]["alias"] == alias1
    assert urls[0]["clicks"] == 5


@pytest.mark.asyncio
async def test_info_returns_json(client: AsyncClient) -> None:
    create = await client.post("/shorten", json={"long_url": "https://info.com"})
    alias = create.json()["alias"]
    resp = await client.get(f"/info/{alias}")
    assert resp.status_code == 200
    assert resp.json()["long_url"] == "https://info.com"


@pytest.mark.asyncio
async def test_empty_url_returns_422(client: AsyncClient) -> None:
    resp = await client.post("/shorten", json={"long_url": "  "})
    assert resp.status_code == 422
