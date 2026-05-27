/*
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 */

#include "io.h"

int main(void) {
    int n;
    int *nums = read_ints(&n);
    char visited[100001] = {0};
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int count = 0, j = i;
            while (!visited[j]) {
                visited[j] = 1;
                j = nums[j];
                count++;
            }
            if (count > max_len) max_len = count;
        }
    }
    write_int(max_len);
    free(nums);
    return 0;
}
