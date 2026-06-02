/**
 * P355: Design Twitter [PREMIUM] (Medium)
 * https://leetcode.com/problems/design-twitter/
 * Topics: Hash Table, Linked List, Design, Heap (Priority Queue)
 *
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.
 * Implement the Twitter class:
 * Example 1:
 *     ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
 *     [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
 *     Output: [null, null, [5], null, null, [6, 5], null, [5]]
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

import { readLine, readInts, readInt, writeInts } from '../../wasm_libs/js/io.mjs';

class Twitter {
  constructor() {
    this.timestamp = 0;
    this.tweets = new Map();
    this.following = new Map();
  }

  postTweet(userId, tweetId) {
    if (!this.tweets.has(userId)) this.tweets.set(userId, []);
    this.tweets.get(userId).push([tweetId, this.timestamp++]);
  }

  getNewsFeed(userId) {
    const heap = new MinHeap();
    const followees = this.following.get(userId) || new Set();
    followees.add(userId);
    for (const followeeId of followees) {
      const tweetList = this.tweets.get(followeeId) || [];
      const idx = tweetList.length - 1;
      if (idx >= 0) {
        heap.push([-(tweetList[idx][1]), tweetList[idx][0], followeeId, idx]);
      }
    }
    const result = [];
    while (heap.size > 0 && result.length < 10) {
      const [, tweetId, followeeId, idx] = heap.pop();
      result.push(tweetId);
      if (idx > 0) {
        const tweetList = this.tweets.get(followeeId);
        const newIdx = idx - 1;
        heap.push([-(tweetList[newIdx][1]), tweetList[newIdx][0], followeeId, newIdx]);
      }
    }
    return result;
  }

  follow(followerId, followeeId) {
    if (!this.following.has(followerId)) this.following.set(followerId, new Set());
    this.following.get(followerId).add(followeeId);
  }

  unfollow(followerId, followeeId) {
    if (this.following.has(followerId)) {
      this.following.get(followerId).delete(followeeId);
    }
  }
}

class MinHeap {
  constructor() { this.data = []; }
  get size() { return this.data.length; }
  push(val) { this.data.push(val); this._bubbleUp(this.data.length - 1); }
  pop() {
    const top = this.data[0];
    const last = this.data.pop();
    if (this.data.length > 0) { this.data[0] = last; this._sinkDown(0); }
    return top;
  }
  _bubbleUp(i) {
    while (i > 0) {
      const parent = (i - 1) >> 1;
      if (this.data[parent][0] <= this.data[i][0]) break;
      [this.data[parent], this.data[i]] = [this.data[i], this.data[parent]];
      i = parent;
    }
  }
  _sinkDown(i) {
    const n = this.data.length;
    while (true) {
      let smallest = i;
      const left = 2 * i + 1, right = 2 * i + 2;
      if (left < n && this.data[left][0] < this.data[smallest][0]) smallest = left;
      if (right < n && this.data[right][0] < this.data[smallest][0]) smallest = right;
      if (smallest === i) break;
      [this.data[smallest], this.data[i]] = [this.data[i], this.data[smallest]];
      i = smallest;
    }
  }
}

const numOps = readInt();
const twitter = new Twitter();
for (let i = 0; i < numOps; i++) {
  const opName = readLine();
  const argCount = readInt();
  const args = [];
  for (let j = 0; j < argCount; j++) {
    args.push(readInt());
  }
  if (opName === "postTweet") {
    twitter.postTweet(args[0], args[1]);
  } else if (opName === "getNewsFeed") {
    writeInts(twitter.getNewsFeed(args[0]));
  } else if (opName === "follow") {
    twitter.follow(args[0], args[1]);
  } else if (opName === "unfollow") {
    twitter.unfollow(args[0], args[1]);
  }
}
