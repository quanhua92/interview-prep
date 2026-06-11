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
use std::collections::VecDeque;

struct Buffer {
    id: usize,
    used: usize,
    capacity: usize,
}

struct BufferPool {
    buffers: Vec<Buffer>,
    free_ids: VecDeque<usize>,
    next_id: usize,
}

impl BufferPool {
    fn new(pool_size: usize, buffer_capacity: usize) -> Self {
        let mut free_ids = VecDeque::with_capacity(pool_size);
        for i in 0..pool_size {
            free_ids.push_back(i);
        }
        let buffers = (0..pool_size)
            .map(|i| Buffer { id: i, used: 0, capacity: buffer_capacity })
            .collect();
        BufferPool { buffers, free_ids, next_id: pool_size }
    }

    fn alloc(&mut self) -> Option<usize> {
        self.free_ids.pop_front().map(|id| {
            self.buffers[id].used = 0;
            id
        })
    }

    fn write(&mut self, id: usize, size: usize) -> Option<usize> {
        if id >= self.buffers.len() { return None; }
        let buf = &mut self.buffers[id];
        if buf.used + size > buf.capacity { return None; }
        buf.used += size;
        Some(buf.capacity - buf.used)
    }

    fn free(&mut self, id: usize) -> bool {
        if id >= self.buffers.len() { return false; }
        if self.free_ids.contains(&id) { return false; }
        self.buffers[id].used = 0;
        self.free_ids.push_back(id);
        true
    }

    fn stats(&self) -> (usize, usize, usize) {
        let total = self.buffers.len();
        let free = self.free_ids.len();
        (total, total - free, free)
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
