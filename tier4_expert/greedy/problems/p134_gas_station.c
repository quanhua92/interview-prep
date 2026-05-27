/*
 * P134: Gas Station (Medium)
 * https://leetcode.com/problems/gas-station/
 * Topics: Array, Greedy
 *
 * Hint: Track total_surplus and current_surplus. If current_surplus < 0, reset start to next station.
 */


#include "ctest.h"

int canCompleteCircuit(int *gas, int *cost, int n) {
    abort();
}

int main(void) {
    int gas_n, cost_n;
    int *gas = read_ints(&gas_n);
    int *cost = read_ints(&cost_n);
    int result = canCompleteCircuit(gas, cost, gas_n);
    write_int(result);
    free(gas);
    free(cost);
    return 0;
}
