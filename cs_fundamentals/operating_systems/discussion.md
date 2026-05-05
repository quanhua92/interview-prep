# Operating Systems

Processes, threads, scheduling, memory management, file systems, and deadlock prevention for SWE interviews.

## Key Concepts

- **Process vs Thread**: A process is an independent execution unit with its own memory space, file descriptors, and resources. A thread is a lightweight sub-unit of a process that shares memory and resources with other threads in the same process but has its own stack and program counter.
- **Process Scheduling**: The OS scheduler decides which process runs on the CPU using algorithms like Round Robin, FCFS, Priority Scheduling, and Completely Fair Scheduler (CFS) in Linux. Context switching between processes is expensive due to memory space swaps.
- **Virtual Memory**: An abstraction that gives each process the illusion of having its own dedicated memory. It maps virtual addresses to physical addresses via page tables, enabling memory isolation and allowing the OS to use disk as overflow (swap space).
- **Paging**: Memory is divided into fixed-size blocks called pages (typically 4KB). The OS maintains a page table to translate virtual page numbers to physical frame numbers. A page fault occurs when a requested page is not in physical memory and must be loaded from disk.
- **Segmentation**: Memory is divided into variable-sized logical segments (code, data, stack) rather than fixed-size pages. Segments are identified by a segment number and offset, providing better logical organization but suffering from external fragmentation.
- **Deadlock**: A state where two or more processes are each waiting for a resource held by the other, resulting in none making progress. The four necessary conditions are mutual exclusion, hold and wait, no preemption, and circular wait.

## Common Questions with Brief Answer Outlines

**Q: What is the difference between a process and a thread?**
- Processes are isolated with separate memory spaces; threads share memory within a process.
- Thread creation and context switching are cheaper than process creation and switching.
- A crash in one thread can affect other threads in the same process, but not separate processes.
- IPC between processes requires mechanisms like pipes or shared memory; threads communicate directly via shared memory.

**Q: How does virtual memory work?**
- Each process gets its own virtual address space, managed via page tables.
- The MMU (Memory Management Unit) translates virtual addresses to physical addresses at runtime.
- Pages not in RAM trigger a page fault; the OS loads them from disk into a free frame.
- TLB (Translation Lookaside Buffer) caches recent translations to speed up address resolution.

**Q: What are the four conditions for deadlock and how can you prevent them?**
- Mutual exclusion: at least one resource must be non-shareable.
- Hold and wait: a process holds a resource while waiting for another.
- No preemption: resources cannot be forcibly taken from a process.
- Circular wait: a cycle of processes each waiting for a resource held by the next.
- Prevention strategies include allowing preemption, requiring processes to request all resources upfront, or ordering resource types to break circular wait.

**Q: Explain demand paging and its relationship to page replacement algorithms.**
- Demand paging loads pages into memory only when they are accessed, not in advance.
- When physical memory is full, a page must be evicted using a replacement algorithm.
- LRU (Least Recently Used) approximates optimal replacement by evicting the least recently accessed page.
- FIFO is simpler but can suffer from Belady's anomaly where more frames lead to more page faults.
- Clock algorithm is a practical approximation of LRU with lower overhead.

**Q: What is the difference between paging and segmentation?**
- Paging uses fixed-size blocks, avoiding external fragmentation but causing internal fragmentation.
- Segmentation uses variable-size blocks based on logical divisions, avoiding internal fragmentation but risking external fragmentation.
- Paging is transparent to the programmer; segmentation often requires explicit management.
- Modern systems combine both: segmentation for logical organization and paging for physical allocation.

**Q: What is a zombie process and how can it be prevented?**
- A zombie process is a child process that has finished execution but still has an entry in the process table because its parent has not yet called wait() to read its exit status.
- Zombies do not consume CPU or memory for execution, but they do consume a process table entry; if too many accumulate, the system may run out of PIDs.
- Prevention: the parent process must call wait() or waitpid() to reap the child. Alternatively, use signal handlers (SIGCHLD) to automatically reap children, or double-fork so the init process adopts the orphaned child.
- A zombie differs from an orphan process: an orphan is still running but its parent has exited (it gets reparented to init/PID 1).

**Q: What is the difference between monolithic kernels and microkernels?**
- Monolithic kernels (Linux, traditional UNIX) run all OS services (file systems, device drivers, networking) in kernel space. This provides high performance due to no context-switch overhead between services but means a bug in any component can crash the entire system.
- Microkernels (MINIX, seL4, QNX) run only the bare minimum in kernel space (IPC, scheduling, basic memory management); other services run as user-space processes. This improves reliability and security (a buggy driver crash does not bring down the kernel) but introduces IPC overhead that can reduce performance.
- Hybrid kernels (Windows NT, macOS XNU) combine elements of both: core services in kernel space but some services like drivers in user space.

**Q: What is the fork/exec/wait lifecycle?**
- fork() creates a new process by duplicating the calling process; the child gets a copy of the parent's address space, file descriptors, and execution context. The return value differs: parent gets the child's PID, child gets 0.
- exec() (or one of its variants like execve) replaces the current process's memory space with a new program. The PID stays the same but the code, data, heap, and stack are replaced.
- wait() / waitpid() is called by the parent to block until a child exits and retrieve its exit status; this also reaps the zombie process.
- The common pattern: fork to create a child, the child calls exec to run a new program, the parent calls wait to reap the child.

**Q: How do interrupts and system calls work?**
- An interrupt is a signal to the CPU that an event needs immediate attention. Hardware interrupts come from devices (disk I/O complete, timer, keyboard); software interrupts (traps) are triggered by programs (division by zero, page fault).
- A system call is the mechanism by which a user-space program requests a service from the kernel (e.g., read, write, fork, mmap). The program triggers a software interrupt (or uses a dedicated CPU instruction like syscall/sysenter) to switch from user mode to kernel mode.
- The CPU saves the current context, switches to kernel mode using a privilege level change, executes the kernel handler, returns the result, and switches back to user mode.
- The distinction between user space and kernel space is crucial for security and stability: user programs cannot directly access hardware or other processes' memory.

## Quick Reference Table

| Concept | Process | Thread |
|---|---|---|
| Memory | Separate address space | Shared address space |
| Creation cost | High | Low |
| Context switch | Slow (flush TLB, swap page tables) | Fast (same page table) |
| Communication | IPC required (pipes, sockets, shared memory) | Direct via shared memory |
| Failure isolation | Independent; crash does not affect others | One thread crash can kill entire process |
| Scheduling | Kernel-level scheduling | Can be kernel or user-level |
