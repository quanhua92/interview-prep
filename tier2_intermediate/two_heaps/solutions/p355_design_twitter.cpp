/*
 * P355: Design Twitter [PREMIUM] (Medium)
 * https://leetcode.com/problems/design-twitter/
 * Topics: Hash Table, Linked List, Design, Heap (Priority Queue)
 *
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.
 * Implement the Twitter class:
 * Example 1:
 *     Input
 *     ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
 *     [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
 *     Output
 *     [null, null, [5], null, null, [6, 5], null, [5]]
 *
 *     Explanation
 *     Twitter twitter = new Twitter();
 *     twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
 *     twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
 *     twitter.follow(1, 2);    // User 1 follows user 2.
 *     twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
 *     twitter.getNewsFeed(1);  // User 1's news feed should return a list with 2 tweet ids -> [6, 5]. Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
 *     twitter.unfollow(1, 2);  // User 1 unfollows user 2.
 *     twitter.getNewsFeed(1);  // User 1's news feed should return a list with 1 tweet id -> [5], since user 1 is no longer following user 2.
 *
 * Constraints:
 *     - 1 <= userId, followerId, followeeId <= 500
 *     - 0 <= tweetId <= 104
 *     - All the tweets have unique IDs.
 *     - At most 3 * 104 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
 *     - A user cannot follow himself.
 *
 * Template (python3):
 *     class Twitter:
 *         def __init__(self):
 *
 *
 *         def postTweet(self, userId: int, tweetId: int) -> None:
 *
 *
 *         def getNewsFeed(self, userId: int) -> List[int]:
 *
 *
 *         def follow(self, followerId: int, followeeId: int) -> None:
 *
 *
 *         def unfollow(self, followerId: int, followeeId: int) -> None:
 *
 *
 *     # Your Twitter object will be instantiated and called as such:
 *     # obj = Twitter()
 *     # obj.postTweet(userId,tweetId)
 *     # param_2 = obj.getNewsFeed(userId)
 *     # obj.follow(followerId,followeeId)
 *     # obj.unfollow(followerId,followeeId)
 */


#include "io.h"
#include <queue>
#include <vector>
#include <unordered_set>
#include <string>

class Twitter {
    struct Tweet { int tweet_id; int time; int next; };
    std::vector<Tweet> pool;
    std::vector<int> head;
    std::vector<std::unordered_set<int>> following;
    int clock;
public:
    Twitter() : head(505, -1), following(505), clock(0) {}

    void postTweet(int userId, int tweetId) {
        pool.push_back({tweetId, ++clock, head[userId]});
        head[userId] = (int)pool.size() - 1;
    }

    std::vector<int> getNewsFeed(int userId) {
        using E = std::tuple<int, int, int>;
        std::priority_queue<E, std::vector<E>, std::less<E>> pq;
        std::vector<int> users;
        users.push_back(userId);
        for (int u = 1; u < 505; u++) {
            if (following[userId].count(u)) users.push_back(u);
        }
        std::vector<int> iters(users.size());
        for (size_t i = 0; i < users.size(); i++) {
            iters[i] = head[users[i]];
            if (iters[i] != -1) pq.push({pool[iters[i]].time, pool[iters[i]].tweet_id, iters[i]});
        }
        std::vector<int> res;
        while (!pq.empty() && (int)res.size() < 10) {
            auto [time, tid, idx] = pq.top(); pq.pop();
            res.push_back(tid);
            int next = pool[idx].next;
            if (next != -1) pq.push({pool[next].time, pool[next].tweet_id, next});
        }
        return res;
    }

    void follow(int followerId, int followeeId) { following[followerId].insert(followeeId); }
    void unfollow(int followerId, int followeeId) { following[followerId].erase(followeeId); }
};

int main(void)
{
    Twitter tw;

    int num_ops = read_ints()[0];
    for (int i = 0; i < num_ops; i++) {
        std::string op = read_line();
        int arg_count = read_ints()[0];
        std::vector<int> args(arg_count);
        for (int j = 0; j < arg_count; j++) {
            args[j] = read_ints()[0];
        }

        if (op == "postTweet") {
            tw.postTweet(args[0], args[1]);
        } else if (op == "getNewsFeed") {
            std::vector<int> feed = tw.getNewsFeed(args[0]);
            write_ints(feed);
        } else if (op == "follow") {
            tw.follow(args[0], args[1]);
        } else if (op == "unfollow") {
            tw.unfollow(args[0], args[1]);
        }
    }

    return 0;
}
