"""Matrix traversal template with three variants.

Variant 1: Spiral order traversal (clockwise)
Variant 2: Rotate image 90 degrees clockwise (in-place)
Variant 3: Diagonal traversal
"""


# ── Variant 1: Spiral order traversal ────────────────────────────────────────


def spiral_order(matrix: list[list[int]]) -> list[int]:
    """Traverse an m x n matrix in clockwise spiral order.

    Uses four boundary pointers that move inward after each side is traversed.

    Time: O(m * n), Space: O(1) extra (output list is O(m * n))
    """
    if not matrix or not matrix[0]:
        return []
    result: list[int] = []
    top, bottom = 0, len(matrix) - 1
    left, right = 0, len(matrix[0]) - 1

    while top <= bottom and left <= right:
        # Traverse right across the top row
        for c in range(left, right + 1):
            result.append(matrix[top][c])
        top += 1

        # Traverse down the right column
        for r in range(top, bottom + 1):
            result.append(matrix[r][right])
        right -= 1

        # Traverse left across the bottom row (if still valid)
        if top <= bottom:
            for c in range(right, left - 1, -1):
                result.append(matrix[bottom][c])
            bottom -= 1

        # Traverse up the left column (if still valid)
        if left <= right:
            for r in range(bottom, top - 1, -1):
                result.append(matrix[r][left])
            left += 1

    return result


# ── Variant 2: Rotate image 90 degrees clockwise ────────────────────────────


def rotate_image(matrix: list[list[int]]) -> list[list[int]]:
    """Rotate an n x n matrix 90 degrees clockwise in-place.

    Algorithm: transpose (swap matrix[i][j] with matrix[j][i] for i < j),
    then reverse each row.

    Time: O(n^2), Space: O(1)
    """
    n = len(matrix)
    # Transpose
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    # Reverse each row
    for row in matrix:
        row.reverse()
    return matrix


# ── Variant 3: Diagonal traversal ────────────────────────────────────────────


def diagonal_traverse(matrix: list[list[int]]) -> list[int]:
    """Traverse an m x n matrix in diagonal zigzag order.

    Elements on the same diagonal have the same (row + col) sum.
    Even-numbered diagonals go upward, odd-numbered go downward.

    Time: O(m * n), Space: O(1) extra
    """
    if not matrix or not matrix[0]:
        return []
    m, n = len(matrix), len(matrix[0])
    result: list[int] = []
    for d in range(m + n - 1):
        if d % 2 == 0:
            # Going up: row decreases, col increases
            row = min(d, m - 1)
            col = d - row
            while row >= 0 and col < n:
                result.append(matrix[row][col])
                row -= 1
                col += 1
        else:
            # Going down: row increases, col decreases
            col = min(d, n - 1)
            row = d - col
            while col >= 0 and row < m:
                result.append(matrix[row][col])
                row += 1
                col -= 1
    return result
