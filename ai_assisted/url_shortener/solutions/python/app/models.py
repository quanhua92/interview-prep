"""Pydantic request/response schemas for the URL shortener API."""

from pydantic import BaseModel, field_validator


class ShortenRequest(BaseModel):
    long_url: str
    custom_alias: str | None = None

    @field_validator("long_url")
    @classmethod
    def validate_long_url(cls, v: str) -> str:
        v = v.strip()
        if not v:
            msg = "long_url must not be empty"
            raise ValueError(msg)
        if not v.startswith(("http://", "https://")):
            msg = "long_url must start with http:// or https://"
            raise ValueError(msg)
        return v


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
