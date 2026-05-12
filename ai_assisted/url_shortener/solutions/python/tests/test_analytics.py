"""Unit tests for analytics tracker."""

from app.analytics import AnalyticsTracker


def test_record_and_get_clicks() -> None:
    tracker = AnalyticsTracker()
    tracker.record_click("abc")
    tracker.record_click("abc")
    tracker.record_click("abc")
    assert tracker.get_clicks("abc") == 3


def test_get_clicks_missing_alias() -> None:
    tracker = AnalyticsTracker()
    assert tracker.get_clicks("missing") == 0


def test_get_top_returns_sorted() -> None:
    tracker = AnalyticsTracker()
    for _ in range(5):
        tracker.record_click("first")
    for _ in range(3):
        tracker.record_click("second")
    tracker.record_click("third")

    top = tracker.get_top(n=3)
    assert top[0] == ("first", 5)
    assert top[1] == ("second", 3)
    assert top[2] == ("third", 1)


def test_buffer_flush() -> None:
    tracker = AnalyticsTracker()
    tracker.record_click("a")
    # Buffer hasn't been flushed yet, but get_clicks flushes automatically
    assert tracker.get_clicks("a") == 1


def test_get_top_fewer_than_n() -> None:
    tracker = AnalyticsTracker()
    tracker.record_click("only")
    top = tracker.get_top(n=10)
    assert len(top) == 1
