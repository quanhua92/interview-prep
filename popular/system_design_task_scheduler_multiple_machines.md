# Task Scheduler with Cooldown and Multiple Machines

- **Category**: Coding & High-Performance System Design
- **Difficulty**: Hard
- **Target Role**: Systems Architect / Infrastructure Engineer / AI Platform Engineer
- **Source**: LeetCode 621 (Extension), Onsite Design Loops
- **Flashcards**: [System Design deck](flash_cards/design/system_design.md)

---

## Overview

In advanced systems interviews, you are often asked to scale standard algorithmic problems to distributed settings. This guide covers **both the algorithmic coding extension** and the **high-availability distributed system design** for scheduling tasks with a cooldown constraint across multiple machines.

### The Core Constraints
1.  **Multiple Machines ($M$):** We have $M$ identical worker machines (or CPU cores/GPU streams) that can execute tasks concurrently.
2.  **Global Cooldown ($N$):** If a task of type `T` is executed at time step $t$, the next occurrence of a task of type `T` can only be scheduled at or after time $t + N + 1$. This cooldown is global—no two tasks of type `T` can run within $N$ cycles of each other, regardless of which machines they run on.

---

## Part 1: Algorithmic Coding (M Machines with Cooldown)

### The Problem
Given a list of tasks represented by characters (e.g., `['A', 'A', 'A', 'B', 'B', 'B']`), a cooldown period `n`, and the number of machines `m` ($m \ge 1$), find the minimum number of time steps (cycles) required to complete all tasks.

### Algorithmic Approach
1.  **Max-Heap for Frequency:** To minimize total time, we use a greedy approach, prioritizing the tasks with the highest remaining frequency. We store these frequencies in a Max-Heap.
2.  **Wait Queue for Cooldown:** When a task of type `T` is scheduled at time step `t`, it is removed from the heap, its frequency is decremented, and it is pushed into a wait queue with its release timestamp `t + n + 1`.
3.  **Step Execution:** At each time step `t`, we can schedule up to `m` tasks. We poll up to `m` available tasks from the Max-Heap.
4.  **Releasing Cooled Tasks:** At the end of each step, any tasks in the wait queue whose release time is $\le t + 1$ are pushed back into the Max-Heap.
5.  **Fast-Forward Idle Cycles:** If the Max-Heap is empty but the wait queue is not, the machines must sit idle. Instead of stepping time by $1$, we fast-forward `t` directly to the earliest release time in the wait queue to optimize performance.

### C++ Implementation

```cpp
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>

struct CooledTask {
    int remaining_count;
    int release_time;
};

class MultiMachineTaskScheduler {
public:
    int leastInterval(const std::vector<char>& tasks, int n, int m) noexcept {
        if (tasks.empty()) return 0;
        if (m <= 0) return 0;

        // Step 1: Count task frequencies
        std::unordered_map<char, int> freq_map;
        for (char task : tasks) {
            freq_map[task]++;
        }

        // Step 2: Push frequencies to Max-Heap
        std::priority_queue<int> max_heap;
        for (auto const& [task, count] : freq_map) {
            max_heap.push(count);
        }

        // Wait queue: stores {remaining_count, release_time}
        std::queue<CooledTask> wait_queue;
        int time = 0;

        // Step 3: Run the simulation
        while (!max_heap.empty() || !wait_queue.empty()) {
            // Release cooled tasks whose release time is <= current time
            while (!wait_queue.empty() && wait_queue.front().release_time <= time) {
                max_heap.push(wait_queue.front().remaining_count);
                wait_queue.pop();
            }

            if (max_heap.empty()) {
                // Fast-forward time to the release time of the earliest cooled task
                time = wait_queue.front().release_time;
                continue;
            }

            // In this cycle, we can schedule up to 'm' tasks
            std::vector<int> current_batch;
            int limit = std::min(m, static_cast<int>(max_heap.size()));
            
            for (int i = 0; i < limit; ++i) {
                current_batch.push_back(max_heap.top());
                max_heap.pop();
            }

            // Process tasks scheduled in this time step
            for (int count : current_batch) {
                if (count - 1 > 0) {
                    // Task still has remaining executions, put into wait queue
                    wait_queue.push({count - 1, time + n + 1});
                }
            }

            time++; // Move to the next cycle
        }

        return time;
    }
};
```

### Python Implementation

```python
from collections import Counter
import heapq

def least_interval_multi_machine(tasks: list[str], n: int, m: int) -> int:
    if not tasks:
        return 0
    if m <= 0:
        return 0

    # Step 1: Count task frequencies
    counts = Counter(tasks)
    
    # Python has min-heaps, store negative values to simulate max-heap
    max_heap = [-count for count in counts.values()]
    heapq.heapify(max_heap)
    
    # Wait queue elements: (release_time, remaining_count)
    # Using a list as a queue; queue is sorted by release_time
    wait_queue = []
    time = 0

    while max_heap or wait_queue:
        # Move cooled tasks back to max_heap
        while wait_queue and wait_queue[0][0] <= time:
            release_time, count = wait_queue.pop(0)
            heapq.heappush(max_heap, count)
            
        if not max_heap:
            # Fast-forward time to next cooled task's release
            time = wait_queue[0][0]
            continue
            
        # We can execute up to 'm' tasks at this step
        batch_limit = min(m, len(max_heap))
        current_batch = []
        for _ in range(batch_limit):
            # Extract highest frequency tasks (remembering counts are negative)
            current_batch.append(heapq.heappop(max_heap))
            
        for neg_count in current_batch:
            remaining = neg_count + 1 # Decrement frequency (closer to 0)
            if remaining < 0:
                wait_queue.append((time + n + 1, remaining))
                
        # Keep wait_queue sorted by release_time
        wait_queue.sort(key=lambda x: x[0])
        time += 1
        
    return time
```

### Algorithmic Complexity
*   **Time Complexity:** $\mathcal{O}(T \log K)$, where $T$ is the number of tasks, and $K$ is the number of unique task types (at most $26$ for alphabets, meaning $\log K$ is effectively $\mathcal{O}(1)$).
*   **Space Complexity:** $\mathcal{O}(K)$ to store the frequency map, max-heap, and wait queue.

---

## Part 2: Distributed System Design

In a real production environment (like a batch processing cluster, an LLM evaluation runner, or a GPU rendering farm), we cannot run a simple in-memory simulation. We must coordinate multiple physical server nodes.

### System Architecture Diagram

```
                        +----------------------+
                        |    Client / Cron     |
                        +----------------------+
                                   |
                                   v
                        +----------------------+
                        |  API Gateway & Auth  |
                        +----------------------+
                                   |
                                   v
                        +----------------------+
                        |  Database (Queue)    |
                        |                      |
                        | Table: task_queue    |
                        | - task_id (UUID)     |
                        | - task_type (String) |
                        | - payload (JSON)     |
                        | - run_at (Timestamp) |
                        | - status (Enum)      |
                        +----------------------+
                          /        |         \
                         /         |          \
                        v          v           v
                  +----------+ +----------+ +----------+
                  | Worker 1 | | Worker 2 | | Worker 3 |  <-- Distributed Nodes
                  +----------+ +----------+ +----------+
                        \          |          /
                         \         |         /
                          v        v        v
                        +----------------------+
                        |  Redis (Coordination)|
                        |                      |
                        | - Key: type_cooldown |
                        | - Locks / TTL        |
                        +----------------------+
```

### Core Components & Mechanics

#### 1. DB-Backed Queue Table
We store tasks in a relational database (e.g., PostgreSQL) with indexing on `(run_at, status)` to support high-throughput worker queries. 

#### 2. Worker Polling & Locking Loop
Workers continuously query the database for pending jobs. To prevent multiple workers from picking up tasks of the same type that violate the cooldown constraint, we perform **Database Locking + Cooldown Checks**.

We execute the following transaction using `SKIP LOCKED` to prevent worker contention:

```sql
-- Step A: Lock a candidate task that is ready to run
BEGIN;

SELECT task_id, task_type 
FROM task_queue
WHERE status = 'PENDING' AND run_at <= NOW()
ORDER BY run_at ASC
FOR UPDATE SKIP LOCKED
LIMIT 1;
```

#### 3. Enforcing Cooldown with Redis
Once a worker obtains a lock on a task of type `T` from the database, it must verify the global cooldown status.

*   **Mechanism:** Workers query a shared Redis instance.
*   **Key Design:** `lock:task_type:{T}` is set with a Time-To-Live (TTL) equal to `cooldown_seconds`.
*   **Execution Flow:**
    1.  Worker issues a `SET` command to Redis with the `NX` (Not Exists) and `EX` (Expire) flags:
        `SET lock:task_type:A 1 NX EX 60` (sets a 60-second cooldown for task type A).
    2.  **Success:** If Redis returns `OK`, the worker changes the database status of the task to `RUNNING`, commits the transaction, and executes the task.
    3.  **Failure:** If Redis returns `NIL` (cooldown active), the worker rolls back the database transaction. It then updates the task's database `run_at` timestamp to `NOW() + remaining_cooldown_from_redis` so it won't be queried immediately again.

```
                  Worker Lock & Cooldown Flow
                  
   +---------------+
   | Poll DB task  |
   | (SKIP LOCKED) |
   +---------------+
           |
           v
   +---------------+      Success      +--------------------+
   | Acquire Redis |------------------>| Set status RUNNING |
   | lock with TTL |                   | Commit DB Trans.   |
   +---------------+                   +--------------------+
           |                                     |
           | Failure                             v
           v                           +--------------------+
   +--------------------+              |   Execute Task &   |
   | Rollback DB Trans  |              |   Post-cleanup     |
   | Update task's      |              +--------------------+
   | run_at += cooldown |
   +--------------------+
```

---

## Pro-Tip: How to Impress the Interviewer

1.  **Differentiate Concurrency vs. Cooldown:** Clarify that a lock with TTL represents *both* mutual exclusion (no two workers run task type A simultaneously) and cooldown (no worker runs task type A for $N$ seconds after completion). If a task takes $E$ seconds to execute, the Redis TTL must be set to $E + N$ seconds upon start, OR updated dynamically to $N$ seconds *upon completion*.
2.  **Distributed Lock Expiry (Redlock / Leases):** If a worker node crashes mid-execution, the Redis lock will eventually expire based on its TTL, preventing deadlocks. Explain that workers should use a **Heartbeat / Lease Renewal thread** to extend the lock TTL dynamically if the task takes longer than expected, ensuring the cooldown starts exactly when the task finishes.
3.  **Optimizing DB Throughput:** If database polling is a bottleneck, discuss using **Redis Sorted Sets (ZSET)** as the priority queue scheduler. The score represents the `run_at` timestamp. Workers execute a lua script to pop ready items and acquire the cooldown lock atomically.

---

## Advanced Follow-Up Questions

*   **Q: What if the Redis coordinator goes down?**
    *   *A:* Use a fallback cluster configuration (Redis Sentinel or Redis Cluster). If Redis is completely unreachable, fall back to transactional lock checks in SQL using a dedicated `cooldown_registry` database table, maintaining consistency at the cost of higher DB write latencies.
*   **Q: How do you handle clock drift across the worker machines?**
    *   *A:* Clock drift can corrupt cooldown checks if workers rely on their local system times. To prevent this, query the central database server time (`SELECT NOW()`) or NTP synchronized time sources, and use relative TTL durations in Redis rather than absolute Unix timestamps.
