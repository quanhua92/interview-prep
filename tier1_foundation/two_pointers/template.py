"""Two Pointers pattern templates.

Three common variants of the two-pointer technique:

1. Two pointers from opposite ends: Find a pair with a target sum in a sorted array.
2. Two pointers from the same end (fast/slow): Remove elements in-place without extra space.
3. Two pointers from opposite ends (greedy): Maximize area/volume by moving the shorter pointer.
"""


def two_sum_sorted(numbers: list[int], target: int) -> list[int]:
    """Variant 1: Two pointers from opposite ends.

    Given a sorted array, find two numbers that add up to target.
    Return their 1-based indices.

    Time:  O(n) -- each step eliminates one element
    Space: O(1) -- only two pointers

    Args:
        numbers: Sorted array of integers (1-indexed in the original problem).
        target: The desired sum.

    Returns:
        1-based indices of the two numbers that add up to target.

    Example:
        >>> two_sum_sorted([2, 7, 11, 15], 9)
        [1, 2]
    """
    left, right = 0, len(numbers) - 1
    while left < right:
        current = numbers[left] + numbers[right]
        if current == target:
            return [left + 1, right + 1]  # 1-based
        elif current < target:
            left += 1
        else:
            right -= 1
    return []


def remove_duplicates(nums: list[int]) -> int:
    """Variant 2: Two pointers from the same end (fast/slow).

    Remove duplicates from a sorted array in-place such that each element
    appears at most once. Return the new length.

    Time:  O(n) -- single pass
    Space: O(1) -- in-place modification

    Args:
        nums: Sorted array (modified in-place).

    Returns:
        New length of the array after removing duplicates.

    Example:
        >>> nums = [1, 1, 2]
        >>> k = remove_duplicates(nums)
        >>> nums[:k]
        [1, 2]
    """
    if not nums:
        return 0
    write = 1  # slow pointer -- next position to write a unique value
    for read in range(1, len(nums)):  # fast pointer -- scans ahead
        if nums[read] != nums[read - 1]:
            nums[write] = nums[read]
            write += 1
    return write


def max_area(height: list[int]) -> int:
    """Variant 3: Two pointers from opposite ends (greedy).

    Find two lines that together with the x-axis form a container that
    holds the most water. The area is min(height[i], height[j]) * (j - i).

    Greedy insight: Moving the shorter pointer inward is the only way to
    potentially increase the area, because the width always decreases.

    Time:  O(n) -- each step moves one pointer
    Space: O(1) -- only two pointers

    Args:
        height: Array of non-negative integers representing line heights.

    Returns:
        Maximum area of water the container can hold.

    Example:
        >>> max_area([1, 8, 6, 2, 5, 4, 8, 3, 7])
        49
    """
    left, right = 0, len(height) - 1
    max_water = 0
    while left < right:
        area = min(height[left], height[right]) * (right - left)
        max_water = max(max_water, area)
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1
    return max_water


if __name__ == "__main__":
    # Quick smoke tests
    assert two_sum_sorted([2, 7, 11, 15], 9) == [1, 2]
    assert two_sum_sorted([2, 3, 4], 6) == [1, 3]

    nums = [1, 1, 2]
    assert remove_duplicates(nums) == 2
    assert nums[:2] == [1, 2]

    assert max_area([1, 8, 6, 2, 5, 4, 8, 3, 7]) == 49
    print("All template smoke tests passed.")
