"""FastAPI application with URL shortener routes."""

from fastapi import FastAPI, HTTPException
from fastapi.responses import RedirectResponse

from app.models import (
    AnalyticsResponse,
    ErrorResponse,
    ResolveResponse,
    ShortenRequest,
    ShortenResponse,
    TopUrlsResponse,
)
from app.service import URLShortenerService

BASE_SHORT_URL = "https://short.url"

app = FastAPI(title="URL Shortener", version="1.0.0")
app.state.service = URLShortenerService()


@app.post("/shorten", response_model=ShortenResponse, responses={409: {"model": ErrorResponse}})
async def shorten_url(req: ShortenRequest) -> ShortenResponse:
    """Create a short alias for a long URL."""
    if not req.long_url.strip():
        raise HTTPException(status_code=422, detail="long_url must not be empty")

    if req.custom_alias and (len(req.custom_alias) > 7 or not req.custom_alias.isalnum()):
        raise HTTPException(
            status_code=422,
            detail="custom_alias must be alphanumeric and at most 7 characters",
        )

    service: URLShortenerService = app.state.service

    try:
        alias = service.shorten(req.long_url, custom_alias=req.custom_alias)
    except ValueError as exc:
        raise HTTPException(status_code=409, detail=str(exc)) from exc

    return ShortenResponse(short_url=f"{BASE_SHORT_URL}/{alias}", alias=alias)


# --- Specific routes MUST be defined before the catch-all /{alias} route ---


@app.get("/info/{alias}", response_model=ResolveResponse, responses={404: {"model": ErrorResponse}})
async def resolve_url(alias: str) -> ResolveResponse:
    """Return the original long URL as JSON (no redirect)."""
    service: URLShortenerService = app.state.service
    long_url = service.resolve(alias)

    if long_url is None:
        raise HTTPException(status_code=404, detail="Alias not found")

    return ResolveResponse(long_url=long_url)


@app.get("/analytics/top", response_model=TopUrlsResponse)
async def get_top_urls() -> TopUrlsResponse:
    """Return the top URLs ranked by click count."""
    service: URLShortenerService = app.state.service
    top = service.get_top_urls(n=10)
    return TopUrlsResponse(
        urls=[AnalyticsResponse(alias=a, clicks=c) for a, c in top]
    )


@app.get(
    "/analytics/{alias}",
    response_model=AnalyticsResponse,
    responses={404: {"model": ErrorResponse}},
)
async def get_analytics(alias: str) -> AnalyticsResponse:
    """Return click count for a given alias."""
    service: URLShortenerService = app.state.service

    if not service.storage.exists(alias):
        raise HTTPException(status_code=404, detail="Alias not found")

    clicks = service.get_analytics(alias)
    return AnalyticsResponse(alias=alias, clicks=clicks)


@app.get("/{alias}")
async def redirect_url(alias: str) -> RedirectResponse:
    """Redirect to the original long URL."""
    service: URLShortenerService = app.state.service
    long_url = service.resolve(alias)

    if long_url is None:
        raise HTTPException(status_code=404, detail="Alias not found")

    return RedirectResponse(url=long_url, status_code=302)
