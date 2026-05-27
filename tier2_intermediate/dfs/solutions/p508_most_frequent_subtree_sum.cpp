/*
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
 */

#include "io.h"
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

static TreeNode *from_list(const std::vector<int>& vals) {
    if (vals.empty()) return nullptr;
    TreeNode *root = new TreeNode(vals[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode *node = q.front(); q.pop();
        if (i < vals.size()) {
            if (vals[i] != 2147483647) { node->left = new TreeNode(vals[i]); q.push(node->left); }
            i++;
        }
        if (i < vals.size()) {
            if (vals[i] != 2147483647) { node->right = new TreeNode(vals[i]); q.push(node->right); }
            i++;
        }
    }
    return root;
}

static int subtree_sum(TreeNode *node, std::unordered_map<int, int>& freq) {
    if (!node) return 0;
    int s = node->val + subtree_sum(node->left, freq) + subtree_sum(node->right, freq);
    freq[s]++;
    return s;
}

int main() {
    auto line = read_line();
    std::vector<int> vals;
    size_t pos = 0;
    while (pos < line.size()) {
        while (pos < line.size() && line[pos] == ' ') pos++;
        size_t end = line.find(' ', pos);
        if (end == std::string::npos) end = line.size();
        std::string tok = line.substr(pos, end - pos);
        pos = end;
        if (tok == "null") vals.push_back(2147483647);
        else vals.push_back(std::stoi(tok));
    }
    TreeNode *root = from_list(vals);
    std::unordered_map<int, int> freq;
    subtree_sum(root, freq);
    int max_freq = 0;
    for (auto& [k, v] : freq) max_freq = std::max(max_freq, v);
    std::vector<int> result;
    for (auto& [k, v] : freq) {
        if (v == max_freq) result.push_back(k);
    }
    std::sort(result.begin(), result.end());
    write_ints(result);
    return 0;
}
