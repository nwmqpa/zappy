"""Unit tests."""


def inc(x) -> int:
    return x + 1


def test_answer() -> None:
    assert inc(3) == 4
