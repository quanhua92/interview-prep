"""Pydantic request/response schemas for the URL shortener API."""

from pydantic import BaseModel


class ShortenRequest(BaseModel):
    long_url: str
    custom_alias: str | None = None


class ShortenResponse(BaseModel):
    short_url: str
    alias: str


class ResolveResponse(BaseModel):
    long_url: str


class ErrorResponse(BaseModel):
    detail: str


class AnalyticsResponse(BaseModel):
    alias: str
    clicks: int


class TopUrlsResponse(BaseModel):
    urls: list[AnalyticsResponse]
