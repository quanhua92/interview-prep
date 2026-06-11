/*
 * P09: Buffer Pool Allocator
 *
 * Implement a simple buffer pool that reuses fixed-size buffers
 * to minimize allocations in a high-throughput system.
 *
 * Input: pool_size (number of buffers), buffer_capacity (bytes per buffer)
 *        then operations until "END":
 *   - ALLOC: allocate a buffer (returns buffer id)
 *   - WRITE id size: write `size` bytes to buffer (returns remaining capacity)
 *   - FREE id: return buffer to pool
 *   - STATS: print pool utilization
 *
 * Output: Result of each operation
 *
 * Skills: VecDeque pool, capacity tracking, allocation patterns
 */

use wasm_libs::*;

struct Buffer {
    id: usize,
    used: usize,
    capacity: usize,
}

struct BufferPool {
    buffers: Vec<Buffer>,
    free_ids: std::collections::VecDeque<usize>,
    next_id: usize,
}

impl BufferPool {
    fn new(pool_size: usize, buffer_capacity: usize) -> Self {
        todo!();
    }

    fn alloc(&mut self) -> Option<usize> {
        todo!();
    }

    fn write(&mut self, id: usize, size: usize) -> Option<usize> {
        todo!();
    }

    fn free(&mut self, id: usize) -> bool {
        todo!();
    }

    fn stats(&self) -> (usize, usize, usize) {
        todo!();
    }
}

fn main() {
    let params = read_ints();
    let pool_size = params[0] as usize;
    let buffer_capacity = params[1] as usize;
    let mut pool = BufferPool::new(pool_size, buffer_capacity);

    loop {
        let line = read_line();
        if line == "END" { break; }
        let parts: Vec<&str> = line.split_whitespace().collect();
        match parts[0] {
            "ALLOC" => {
                match pool.alloc() {
                    Some(id) => write_string(&format!("ALLOC {}", id)),
                    None => write_string("ALLOC FULL"),
                }
            }
            "WRITE" => {
                let id: usize = parts[1].parse().unwrap();
                let size: usize = parts[2].parse().unwrap();
                match pool.write(id, size) {
                    Some(remaining) => write_string(&format!("WRITE {} {}", id, remaining)),
                    None => write_string(&format!("WRITE {} OVERFLOW", id)),
                }
            }
            "FREE" => {
                let id: usize = parts[1].parse().unwrap();
                if pool.free(id) {
                    write_string(&format!("FREE {} OK", id));
                } else {
                    write_string(&format!("FREE {} INVALID", id));
                }
            }
            "STATS" => {
                let (total, used, free) = pool.stats();
                write_string(&format!("STATS total={} used={} free={}", total, used, free));
            }
            _ => {}
        }
    }
    std::process::exit(0);
}
