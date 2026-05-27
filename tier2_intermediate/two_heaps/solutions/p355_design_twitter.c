/*
 * P355: Design Twitter [PREMIUM] (Medium)
 * https://leetcode.com/problems/design-twitter/
 * Topics: Hash Table, Linked List, Design, Heap (Priority Queue)
 *
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.
 * Implement the Twitter class:
 * Example 1:
 *     Input
 * Example 1:
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 505
#define MAX_TWEETS 30005
#define FEED_SIZE 10

typedef struct { int tweet_id; int time; int next; } TweetNode;

static TweetNode pool[MAX_TWEETS];
static int pool_cnt;
static int head[MAX_USERS];
static int following[MAX_USERS][MAX_USERS];
static int global_time;

static void twitter_init(void)
{
    pool_cnt = 0;
    global_time = 0;
    memset(head, -1, sizeof(head));
    memset(following, 0, sizeof(following));
}

static void post_tweet(int user_id, int tweet_id)
{
    pool[pool_cnt] = (TweetNode){tweet_id, ++global_time, head[user_id]};
    head[user_id] = pool_cnt++;
}

typedef struct { int tweet_id; int time; int next_node; int user_id; } HeapEntry;

static void heap_push(HeapEntry *h, int *hsz, HeapEntry e)
{
    int i = (*hsz)++;
    h[i] = e;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[p].time < h[i].time) { HeapEntry t = h[p]; h[p] = h[i]; h[i] = t; i = p; }
        else break;
    }
}

static HeapEntry heap_pop(HeapEntry *h, int *hsz)
{
    HeapEntry top = h[0];
    h[0] = h[--(*hsz)];
    int i = 0;
    while (1) {
        int s = i, l = 2*i+1, r = 2*i+2;
        if (l < *hsz && h[l].time > h[s].time) s = l;
        if (r < *hsz && h[r].time > h[s].time) s = r;
        if (s != i) { HeapEntry t = h[s]; h[s] = h[i]; h[i] = t; i = s; }
        else break;
    }
    return top;
}

static void get_news_feed(int user_id, int *feed, int *feed_size)
{
    HeapEntry heap[MAX_USERS];
    int hsz = 0;
    int iter[MAX_USERS];

    int users[MAX_USERS];
    int ucnt = 0;
    users[ucnt++] = user_id;
    for (int u = 1; u < MAX_USERS; u++) {
        if (following[user_id][u]) users[ucnt++] = u;
    }

    for (int ui = 0; ui < ucnt; ui++) {
        int u = users[ui];
        if (head[u] != -1) {
            iter[ui] = head[u];
            heap_push(heap, &hsz, (HeapEntry){pool[head[u]].tweet_id, pool[head[u]].time, head[u], u});
        }
    }

    *feed_size = 0;
    while (hsz > 0 && *feed_size < FEED_SIZE) {
        HeapEntry top = heap_pop(heap, &hsz);
        feed[(*feed_size)++] = top.tweet_id;
        int next = pool[top.next_node].next;
        if (next != -1) {
            heap_push(heap, &hsz, (HeapEntry){pool[next].tweet_id, pool[next].time, next, top.user_id});
        }
    }
}

static void do_follow(int follower_id, int followee_id)
{
    following[follower_id][followee_id] = 1;
}

static void do_unfollow(int follower_id, int followee_id)
{
    following[follower_id][followee_id] = 0;
}

int main(void)
{
    twitter_init();

    int num_ops = read_int();
    for (int i = 0; i < num_ops; i++) {
        char *op = read_line();
        int arg_count = read_int();
        int args[4];
        for (int j = 0; j < arg_count; j++) {
            args[j] = read_int();
        }
        free(op);

        if (strcmp(op, "postTweet") == 0) {
            post_tweet(args[0], args[1]);
        } else if (strcmp(op, "getNewsFeed") == 0) {
            int feed[FEED_SIZE];
            int feed_size = 0;
            get_news_feed(args[0], feed, &feed_size);
            write_ints(feed, feed_size);
        } else if (strcmp(op, "follow") == 0) {
            do_follow(args[0], args[1]);
        } else if (strcmp(op, "unfollow") == 0) {
            do_unfollow(args[0], args[1]);
        }
    }

    return 0;
}
