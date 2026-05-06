"""Union-Find (Disjoint Set Union) template with three variants.

Variant 1: Union-Find with path compression + union by rank (standard)
Variant 2: Union-Find with size tracking (for component sizes)
Variant 3: Union-Find with component counting (for tracking number of groups)
"""


# ── Variant 1: Union-Find with path compression + union by rank ──────────────


class UnionFind:
    """Standard union-find with path compression and union by rank.

    Attributes:
        parent: parent[i] is the representative of element i's set.
        rank: rank[i] is an upper bound on the height of i's subtree.
    """

    def __init__(self, n: int) -> None:
        self.parent: list[int] = list(range(n))
        self.rank: list[int] = [0] * n

    def find(self, x: int) -> int:
        """Find the representative of x's set with path compression."""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        """Merge the sets containing x and y.

        Returns:
            True if the sets were different (merge happened),
            False if x and y were already in the same set.
        """
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False
        if self.rank[rx] < self.rank[ry]:
            rx, ry = ry, rx
        self.parent[ry] = rx
        if self.rank[rx] == self.rank[ry]:
            self.rank[rx] += 1
        return True

    def connected(self, x: int, y: int) -> bool:
        """Check whether x and y are in the same set."""
        return self.find(x) == self.find(y)


# ── Variant 2: Union-Find with size tracking ────────────────────────────────


class UnionFindBySize:
    """Union-find that tracks the size of each component.

    Useful when you need to know how many elements are in each connected group,
    e.g. "largest component size" problems.
    """

    def __init__(self, n: int) -> None:
        self.parent: list[int] = list(range(n))
        self.size: list[int] = [1] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False
        # Attach smaller tree under larger tree
        if self.size[rx] < self.size[ry]:
            rx, ry = ry, rx
        self.parent[ry] = rx
        self.size[rx] += self.size[ry]
        return True

    def get_size(self, x: int) -> int:
        """Return the size of the component containing x."""
        return self.size[self.find(x)]


# ── Variant 3: Union-Find with component counting ────────────────────────────


class UnionFindByCount:
    """Union-find that maintains a count of disjoint components.

    Useful when you need to answer "how many connected components exist"
    after processing a sequence of union operations.
    """

    def __init__(self, n: int) -> None:
        self.parent: list[int] = list(range(n))
        self.rank: list[int] = [0] * n
        self.count: int = n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False
        if self.rank[rx] < self.rank[ry]:
            rx, ry = ry, rx
        self.parent[ry] = rx
        if self.rank[rx] == self.rank[ry]:
            self.rank[rx] += 1
        self.count -= 1
        return True

    def get_count(self) -> int:
        """Return the current number of disjoint components."""
        return self.count
