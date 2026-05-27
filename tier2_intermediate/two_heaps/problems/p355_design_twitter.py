"""
P355: Design Twitter [PREMIUM] (Medium)
https://leetcode.com/problems/design-twitter/
Topics: Hash Table, Linked List, Design, Heap (Priority Queue)

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.
Implement the Twitter class:
Example 1:
    Input
    ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
    [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
    Output
    [null, null, [5], null, null, [6, 5], null, [5]]

    Explanation
    Twitter twitter = new Twitter();
    twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
    twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
    twitter.follow(1, 2);    // User 1 follows user 2.
    twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
    twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
    twitter.unfollow(1, 2);  // User 1 unfollows user 2.
    twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.

Constraints:
    - 1 <= userId, followerId, followeeId <= 500
    - 0 <= tweetId <= 104
    - All the tweets have unique IDs.
    - At most 3 * 104 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
    - A user cannot follow himself.

Template (python3):
    class Twitter:
        def __init__(self):

        def postTweet(self, userId: int, tweetId: int) -> None:

        def getNewsFeed(self, userId: int) -> List[int]:

        def follow(self, followerId: int, followeeId: int) -> None:

        def unfollow(self, followerId: int, followeeId: int) -> None:

    # Your Twitter object will be instantiated and called as such:
    # obj = Twitter()
    # obj.postTweet(userId,tweetId)
    # param_2 = obj.getNewsFeed(userId)
    # obj.follow(followerId,followeeId)
    # obj.unfollow(followerId,followeeId)
"""

from src.wasm_libs.py.io import *


def solve(num_ops: int) -> None:
    raise NotImplementedError


if __name__ == "__main__":
    num_ops = read_int()
    solve(num_ops)
