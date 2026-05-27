/*
 * P134: Gas Station (Medium)
 * https://leetcode.com/problems/gas-station/
 * Topics: Array, Greedy
 *
 * Hint: Track total_surplus and current_surplus. If current_surplus < 0, reset start to next station.
 */


fn can_complete_circuit(gas: &[i32], cost: &[i32]) -> i32 {
    todo!()
}

fn main() {
    let gas = wasm_libs::read_ints();
    let cost = wasm_libs::read_ints();
    let result = can_complete_circuit(&gas, &cost);
    wasm_libs::write_int(result);
}
