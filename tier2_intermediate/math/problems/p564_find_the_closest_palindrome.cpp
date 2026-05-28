/*
 * P564: Find the Closest Palindrome [PREMIUM] (Hard)
 * https://leetcode.com/problems/find-the-closest-palindrome/
 * Topics: Math, String
 *
 * Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
 * The closest is defined as the absolute difference minimized between two integers.
 * Example 1:
 *     Input: n = "123"
 *     Output: "121"
 *
 * Example 2:
 *     Input: n = "1"
 *     Output: "0"
 *     Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
 *
 * Constraints:
 *     - 1 <= n.length <= 18
 *     - n consists of only digits.
 *     - n does not have leading zeros.
 *     - n is representing an integer in the range [1, 1018 - 1].
 *
 * Hint: Will brute force work for this problem? Think of something else.
 * Hint: Take some examples like 1234, 999,1000, etc and check their closest palindromes. How many different cases are possible?
 * Hint: Do we have to consider only left half or right half of the string or both?
 * Hint: Try to find the closest palindrome of these numbers- 12932, 99800, 12120. Did you observe something?
 *
 * Template (python3):
 *     class Solution:
 *         def nearestPalindromic(self, n: str) -> str:
 */


#include "io.h"
#include <algorithm>
#include <set>
#include <string>

using namespace std;
using ll = long long;

static ll pow10(int n) { ll r = 1; for (int i = 0; i < n; i++) r *= 10; return r; }

string make_pal(ll prefix, int total_len) {
    string p = to_string(prefix);
    string rev = p;
    int rev_start = total_len % 2 == 0 ? (int)p.size() - 1 : (int)p.size() - 2;
    for (int i = rev_start; i >= 0; i--) rev += p[i];
    return rev;
}

string nearestPalindromic(string n) {
    ll num = stoll(n);
    int len = (int)n.size();
    set<ll> cands;
    int half = (len + 1) / 2;
    ll prefix = stoll(n.substr(0, half));
    for (ll d = -1; d <= 1; d++) cands.insert(stoll(make_pal(prefix + d, len)));
    if (len > 1) cands.insert(pow10(len - 1) - 1);
    cands.insert(pow10(len) + 1);
    cands.erase(num);
    ll best = -1, best_diff = -1;
    for (ll c : cands) {
        if (c < 0) continue;
        ll diff = c > num ? c - num : num - c;
        if (best_diff < 0 || diff < best_diff || (diff == best_diff && c < best)) {
            best = c; best_diff = diff;
        }
    }
    return to_string(best);
}

int main() {
    abort();
}
