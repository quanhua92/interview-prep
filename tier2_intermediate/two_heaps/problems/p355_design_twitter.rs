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
 *     - 0 <= tweetId <= 10^4
 *     - All the tweets have unique IDs.
 *     - At most 3 * 10^4 calls will be made to postTweet, getNewsFeed, follow, and unfollow.
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

use wasm_libs::*;
use std::collections::{BinaryHeap, HashSet};
use std::cmp::Ordering;

#[derive(Clone, Copy, PartialEq, Eq)]
struct FeedEntry {
    time: i32,
    tweet_id: i32,
    idx: usize,
}

impl PartialOrd for FeedEntry {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
    todo!();
}
}

impl Ord for FeedEntry {
    fn cmp(&self, other: &Self) -> Ordering {
    todo!();
}
}

struct Tweet {
    tweet_id: i32,
    time: i32,
    next: Option<usize>,
}

struct Twitter {
    pool: Vec<Tweet>,
    head: Vec<Option<usize>>,
    following: Vec<HashSet<i32>>,
    clock: i32,
}

impl Twitter {
    fn new() -> Self {
    todo!();
}

    fn post_tweet(&mut self, user_id: usize, tweet_id: i32) {
    todo!();
}

    fn get_news_feed(&self, user_id: usize) -> Vec<i32> {
    todo!();
}

    fn follow(&mut self, follower: usize, followee: usize) {
    todo!();
}

    fn unfollow(&mut self, follower: usize, followee: usize) {
    todo!();
}
}

fn main() {
    let mut tw = Twitter::new();

    let num_ops = read_int();
    for _ in 0..num_ops {
        let op = read_line();
        let arg_count = read_int();
        let mut args = Vec::new();
        for _ in 0..arg_count {
            args.push(read_int());
        }

        match op.as_str() {
            "postTweet" => tw.post_tweet(args[0] as usize, args[1]),
            "getNewsFeed" => {
                let feed = tw.get_news_feed(args[0] as usize);
                write_ints(&feed);
            }
            "follow" => tw.follow(args[0] as usize, args[1] as usize),
            "unfollow" => tw.unfollow(args[0] as usize, args[1] as usize),
            _ => {}
        }
    }

    std::process::exit(0);
}
