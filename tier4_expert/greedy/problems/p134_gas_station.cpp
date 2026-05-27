/*
 * P134: Gas Station (Medium)
 * https://leetcode.com/problems/gas-station/
 * Topics: Array, Greedy
 *
 * Hint: Track total_surplus and current_surplus. If current_surplus < 0, reset start to next station.
 */


#include "cpptest.h"

int canCompleteCircuit(const std::vector<int> &gas, const std::vector<int> &cost) {
    abort();
}

int main() {
    std::vector<int> gas = read_ints();
    std::vector<int> cost = read_ints();
    int result = canCompleteCircuit(gas, cost);
    write_int(result);
    return 0;
}
