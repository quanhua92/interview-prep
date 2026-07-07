# High-Performance Systems & Speech LLM Interview Preparation Toolkit

Two ways to use this directory:

- **Speed Run (7 days)** — A cherry-picked ~50-item subset drawn from this folder **and** [`tiers/`](tiers/), optimized for maximum interview yield in minimum time. High-frequency patterns first; niche problems and role-specific files are deferred to a "Future" bucket. See [Speed Run](#speed-run-7-day-cherry-pick) below.
- **Full Suite** — The complete reference: 34 deep interview question files (Sections 1–6 below) plus 145 LeetCode problems in [`tiers/`](tiers/). Each deep file is self-contained, with optimal C++/Python/SystemVerilog/Triton implementations, complexity analysis, and systems-level / compiler / hardware optimization details. Use this for deep, role-targeted study once the Speed Run is done.

---

## Speed Run: 7-Day Cherry-Pick

**Scope:** ~50 items from `popular/` root + `popular/tiers/`. Total ~26 hours (~4 h/day).
**Goal:** Pattern recognition + 1 working solution per high-frequency pattern. Not mastery.
**Skip rule:** If a file is not for your target role, drop it and reclaim the time for drilling cold solves on Day 7.

### Per-file protocol (5 minutes max)

1. Read **Question Description** + approach paragraph only.
2. Write **pattern name + 1-line trigger** to a flashcard (this is the real deliverable).
3. Skim the solution code just enough to verify your mental model. Stop.
4. Skip Q&A sections, deep systems highlights, and complexity proofs unless role-critical.

### Day 1 — Linear structures: Two Pointers + Sliding Window

- [ ] [tiers/foundation/coding_two_sum.md](tiers/foundation/coding_two_sum.md) — Two Sum II (sorted two-pointer)
- [ ] [tiers/foundation/coding_three_sum.md](tiers/foundation/coding_three_sum.md) — 3Sum (sort + two-pointer + skip duplicates)
- [ ] [tiers/foundation/coding_container_water.md](tiers/foundation/coding_container_water.md) — Container With Most Water (greedy shrink)
- [ ] [tiers/foundation/coding_longest_substring.md](tiers/foundation/coding_longest_substring.md) — Longest Substring No Repeats (variable window)
- [ ] [tiers/foundation/coding_find_anagrams.md](tiers/foundation/coding_find_anagrams.md) — Find All Anagrams (fixed-width window)
- [ ] [tiers/foundation/coding_longest_repeating_char.md](tiers/foundation/coding_longest_repeating_char.md) — Longest Repeating Char Replacement
- [ ] [tiers/foundation/coding_permutation_in_string.md](tiers/foundation/coding_permutation_in_string.md) — Permutation in String (freq match)

### Day 2 — Intervals + Hashmap + BFS/DFS on grids

- [ ] [tiers/foundation/coding_merge_intervals.md](tiers/foundation/coding_merge_intervals.md)
- [ ] [tiers/foundation/coding_insert_interval.md](tiers/foundation/coding_insert_interval.md)
- [ ] [tiers/foundation/coding_meeting_rooms.md](tiers/foundation/coding_meeting_rooms.md) — Meeting Rooms II (sweep line + heap)
- [ ] [tiers/foundation/coding_level_order.md](tiers/foundation/coding_level_order.md) — Binary Tree Level Order
- [ ] [tiers/foundation/coding_rotting_oranges.md](tiers/foundation/coding_rotting_oranges.md) — Multi-source BFS
- [ ] [tiers/intermediate/coding_number_of_islands.md](tiers/intermediate/coding_number_of_islands.md) — DFS/BFS on grid
- [ ] [tiers/foundation/coding_linked_list_cycle.md](tiers/foundation/coding_linked_list_cycle.md) — Floyd's cycle detection

### Day 3 — Binary Search + DP + Stack + Top K

- [ ] [tiers/intermediate/coding_binary_search.md](tiers/intermediate/coding_binary_search.md)
- [ ] [tiers/intermediate/coding_first_bad_version.md](tiers/intermediate/coding_first_bad_version.md)
- [ ] [tiers/advanced/coding_koko_bananas.md](tiers/advanced/coding_koko_bananas.md) — Binary search on the answer
- [ ] [tiers/intermediate/coding_climbing_stairs.md](tiers/intermediate/coding_climbing_stairs.md) — 1D DP
- [ ] [tiers/intermediate/coding_house_robber.md](tiers/intermediate/coding_house_robber.md)
- [ ] [tiers/intermediate/coding_coin_change.md](tiers/intermediate/coding_coin_change.md) — Unbounded DP
- [ ] [tiers/intermediate/coding_valid_parentheses.md](tiers/intermediate/coding_valid_parentheses.md) — Stack
- [ ] [tiers/intermediate/coding_min_stack.md](tiers/intermediate/coding_min_stack.md)
- [ ] [tiers/intermediate/coding_kth_largest.md](tiers/intermediate/coding_kth_largest.md) — Heap
- [ ] [tiers/intermediate/coding_top_k_frequent.md](tiers/intermediate/coding_top_k_frequent.md) — Bucket sort / heap

### Day 4 — Subsets + Trie + Graph + Greedy + Monotonic Stack

- [ ] [tiers/advanced/coding_subsets.md](tiers/advanced/coding_subsets.md) — Cascading backtracking
- [ ] [tiers/advanced/coding_permutations.md](tiers/advanced/coding_permutations.md)
- [ ] [tiers/advanced/coding_combination_sum.md](tiers/advanced/coding_combination_sum.md)
- [ ] [tiers/advanced/coding_implement_trie.md](tiers/advanced/coding_implement_trie.md)
- [ ] [tiers/advanced/coding_word_search_ii.md](tiers/advanced/coding_word_search_ii.md) — Trie + DFS
- [ ] [tiers/expert/coding_course_schedule.md](tiers/expert/coding_course_schedule.md) — Topological sort
- [ ] [tiers/expert/coding_course_schedule_ii.md](tiers/expert/coding_course_schedule_ii.md)
- [ ] [tiers/expert/coding_jump_game.md](tiers/expert/coding_jump_game.md) — Greedy
- [ ] [tiers/expert/coding_gas_station.md](tiers/expert/coding_gas_station.md)
- [ ] [tiers/expert/coding_daily_temperatures.md](tiers/expert/coding_daily_temperatures.md) — Monotonic stack

### Day 5 — Core deep files (role-agnostic)

- [ ] [hackerrank_and_inperson_coding.md](hackerrank_and_inperson_coding.md) — OA + onsite playbook
- [ ] [behavioral_star_intellectual_honesty.md](behavioral_star_intellectual_honesty.md)
- [ ] [behavioral_star_one_team.md](behavioral_star_one_team.md)
- [ ] [coding_lru_cache.md](coding_lru_cache.md) — Design + custom linked list
- [ ] [coding_merge_intervals.md](coding_merge_intervals.md) — Deep C++/Python analysis
- [ ] [coding_number_of_islands.md](coding_number_of_islands.md) — Deep version
- [ ] [system_lowlevel_python_gil_concurrency.md](system_lowlevel_python_gil_concurrency.md)
- [ ] [system_lowlevel_python_memory_gc.md](system_lowlevel_python_memory_gc.md)

### Day 6 — System design + role-specific (pick 4–6 by role)

Default set (general SWE / AI infra):

- [ ] [system_design_task_scheduler_multiple_machines.md](system_design_task_scheduler_multiple_machines.md)
- [ ] [system_design_triton_inference_server.md](system_design_triton_inference_server.md)
- [ ] [system_design_gpu_microservices_bottleneck.md](system_design_gpu_microservices_bottleneck.md)
- [ ] [system_lowlevel_concurrency_producer_consumer.md](system_lowlevel_concurrency_producer_consumer.md)
- [ ] [system_lowlevel_memory_aligned_malloc.md](system_lowlevel_memory_aligned_malloc.md)
- [ ] [system_lowlevel_python_c_bindings_ctypes.md](system_lowlevel_python_c_bindings_ctypes.md)

Role swaps:

- **GPU / CUDA role:** swap in [system_lowlevel_cuda_warp_divergence.md](system_lowlevel_cuda_warp_divergence.md) + [system_lowlevel_cuda_global_memory_coalescing.md](system_lowlevel_cuda_global_memory_coalescing.md) + [system_design_distributed_gpu_training.md](system_design_distributed_gpu_training.md).
- **Speech / voice role:** swap in [speech_llm_voice_agent_architecture.md](speech_llm_voice_agent_architecture.md) + [speech_llm_latency_optimization.md](speech_llm_latency_optimization.md) + [speech_llm_nemo_riva_stack.md](speech_llm_nemo_riva_stack.md).
- **AV / robotics role:** swap in [system_design_autonomous_driving_perception.md](system_design_autonomous_driving_perception.md) + [system_design_realtime_video_analytics.md](system_design_realtime_video_analytics.md).
- **DL infra role:** swap in [system_lowlevel_pytorch_systems_optimization.md](system_lowlevel_pytorch_systems_optimization.md) + [system_design_distributed_gpu_training.md](system_design_distributed_gpu_training.md).
- **QA role:** swap in [qa_automate_test_environment.md](qa_automate_test_environment.md) + [qa_cpu_gpu_bottleneck_isolation.md](qa_cpu_gpu_bottleneck_isolation.md) + [qa_debug_hardware_software_integration.md](qa_debug_hardware_software_integration.md).
- **ASIC / verification role:** swap in [qa_vietnam_hardware_verification.md](qa_vietnam_hardware_verification.md) + [system_lowlevel_concurrency_lock_free_queue.md](system_lowlevel_concurrency_lock_free_queue.md).

### Day 7 — Drill + review (no new reading)

- [ ] Pick **5 problems** from Days 1–4 and solve them cold using the repo's stubs (`tiers/<tier>/problems/`) — do not peek at the solution first. Verify with `docker exec interview-prep uv run python run.py <pattern> --problems`.
- [ ] Review every flashcard from Days 1–6. Mark the ones you forgot and re-skim only those files.
- [ ] Practice both STAR stories out loud, timed to 2 minutes each.
- [ ] Re-read just the MCQ section of [hackerrank_and_inperson_coding.md](hackerrank_and_inperson_coding.md) once.

### Future bucket (defer until after the 7-day run)

Low interview yield or highly specialized. Return only with spare time, or if the file matches your role exactly.

**Coding (niche / low frequency):**

- *Math puzzles:* `coding_largest_palindrome_product`, `coding_smallest_good_base`, `coding_perfect_rectangle`, `coding_find_the_closest_palindrome`, `coding_optimal_division`
- *Randomized / probability:* `coding_random_pick_index`, `coding_random_pick_with_weight`, `coding_random_point_in_non_overlapping_rectangles`, `coding_random_flip_matrix`, `coding_linked_list_random_node`, `coding_implement_rand10_using_rand7`, `coding_poor_pigs`, `coding_generate_random_point_in_a_circle`
- *Esoteric hards:* `coding_zuma_game`, `coding_super_egg_drop`, `coding_freedom_trail`, `coding_russian_doll_envelopes`, `coding_count_the_repetitions`, `coding_frog_jump`, `coding_out_of_boundary_paths`, `coding_unique_substrings_in_wraparound_string`, `coding_reverse_pairs`, `coding_student_attendance_record_ii`
- *Low-yield easies:* `coding_detect_capital`, `coding_keyboard_row`, `coding_license_key_formatting`, `coding_number_of_segments_in_a_string`, `coding_longest_uncommon_subsequence_i`, `coding_longest_uncommon_subsequence_ii`, `coding_distribute_candies`, `coding_number_of_boomerangs`, `coding_teemo_attacking`

**Deep files (specialized):** any role-specific file you did **not** pick on Day 6 — typically all `speech_llm_*` (non-speech), all `system_lowlevel_cuda_*` (non-GPU), `system_design_autonomous_driving_perception` (non-AV), `system_lowlevel_pytorch_systems_optimization` (non-DL-infra), `qa_vietnam_hardware_verification` (non-ASIC), and `system_lowlevel_concurrency_lock_free_queue` (unless explicitly required).

---

## 1. Coding & Algorithms (7 Questions)
These files focus on data structures and algorithms commonly encountered in technical coding loops. The answers contain optimal implementations in **both C++ and Python**, with detailed analyses of runtime, memory, and CPython interpreter characteristics.

| File Name & Link | Topic / LeetCode Equivalent | Difficulty | Target Role | Key Systems & Python Highlights |
| :--- | :--- | :--- | :--- | :--- |
| [hackerrank_and_inperson_coding.md](hackerrank_and_inperson_coding.md) | **OA & Onsite Coding Playbook** | Medium-Hard | All Software Roles | Structure of HackerRank OA, sample MCQs on OS/Architecture/C++, and concurrent C++ sharded cache design. |
| [coding_lru_cache.md](coding_lru_cache.md) | LRU Cache (LC 146) | Medium | Software / Low-Level Engineer | Custom C++ pointer nodes vs. `collections.OrderedDict`, `__slots__` memory savings, Segmented Caching. |
| [coding_search_rotated_array.md](coding_search_rotated_array.md) | Search in Rotated Sorted Array (LC 33/81) | Medium | Software Engineer | Branch prediction penalties, warp divergence on GPUs, floor division precision loss, list slice copying. |
| [coding_number_of_islands.md](coding_number_of_islands.md) | Number of Islands (LC 200) | Medium | Software / AI Engineer | Recursion depth limits, iterative BFS queues, garbage collection optimization via 1D index mapping. |
| [coding_merge_intervals.md](coding_merge_intervals.md) | Merge Intervals (LC 56) | Medium | Software Engineer | Move semantics vs. object reference copies, Timsort vs. Introsort, key sort C-optimizations. |
| [coding_course_schedule.md](coding_course_schedule.md) | Course Schedule (LC 207) | Medium | Software / compiler Engineer | Kahn's algorithm, pre-allocated adjacencies vs. defaultdict overhead, CSR representation. |
| [coding_trie.md](coding_trie.md) | Implement Trie (LC 208) | Medium | Software / Networking | unique_ptr trees vs. nested dicts, `setdefault()` performance trap, deep recursion deallocator leaks. |

---

## 2. Low-Level Systems, Concurrency & Hardware (6 Questions)
These files address CPU/GPU microarchitectures, concurrency semantics, memory hierarchies, and close-to-hardware C++/CUDA programming, with integrated sections explaining how these concepts behave or are bypassed in Python.

| File Name & Link | Core Technical Topic | Difficulty | Target Role | Key Concept Explored |
| :--- | :--- | :--- | :--- | :--- |
| [system_lowlevel_cuda_warp_divergence.md](system_lowlevel_cuda_warp_divergence.md) | Warp Divergence | Hard | GPU Software Engineer | SIMT model, warp schedulers, Volta ITS, predication, Numba `@cuda.jit` GIL release. |
| [system_lowlevel_cuda_bank_conflicts.md](system_lowlevel_cuda_bank_conflicts.md) | Shared Memory Bank Conflicts | Hard | GPU Software Engineer | 32-bank structures, conflict maths, padded shared memory in Numba, NumPy strided transposes. |
| [system_lowlevel_cuda_global_memory_coalescing.md](system_lowlevel_cuda_global_memory_coalescing.md) | Global Memory Coalescing | Hard | GPU Software Engineer | GDDR6/HBM3 bus layouts, PCIe Gen5/NVLink bandwidths, NumPy/CuPy stride alignment, SoA layouts. |
| [system_lowlevel_concurrency_producer_consumer.md](system_lowlevel_concurrency_producer_consumer.md) | Producer-Consumer Pattern | Medium | Systems / Driver Software | Circular buffers, C++ condition variables, GIL thread locks in `queue.Queue`, `multiprocessing` bypass. |
| [system_lowlevel_concurrency_lock_free_queue.md](system_lowlevel_concurrency_lock_free_queue.md) | Lock-Free SPSC Queue | Hard | Systems / Concurrency Developer | Atomics, acquire-release semantics, MESI/MOESI cache line bouncing, C++ pybind11 thread spawning. |
| [system_lowlevel_memory_aligned_malloc.md](system_lowlevel_memory_aligned_malloc.md) | Aligned Malloc & Free | Medium | OS / Low-level Developer | Custom memory allocation using bitwise masks, PyMalloc blocks/arenas, NumPy `ALIGNED` flag, pybind11 capsules. |

---

## 3. Low-Level Python & PyTorch Internals (4 Questions)
These files focus on CPython internals, memory arenas, PyTorch distributed engines, compiled graphs (`torch.compile`), foreign function interfaces (FFI), and wrapping high-performance custom C++/Triton operators.

| File Name & Link | Core Technical Topic | Difficulty | Target Role | Key Concept Explored |
| :--- | :--- | :--- | :--- | :--- |
| [system_lowlevel_python_gil_concurrency.md](system_lowlevel_python_gil_concurrency.md) | Python GIL & Concurrency | Hard | AI Infrastructure / Systems | GIL mutex implementation, switch intervals, free-threaded Python (PEP 703), zero-copy IPC via `shared_memory`. |
| [system_lowlevel_python_memory_gc.md](system_lowlevel_python_memory_gc.md) | Python Memory & GC | Hard | Software / AI Infrastructure | Reference counting, generational cyclic GC, PyMalloc allocator arenas, PyTorch CUDA memory leak debugging. |
| [system_lowlevel_python_c_bindings_ctypes.md](system_lowlevel_python_c_bindings_ctypes.md) | C-Bindings & Interoperability | Hard | AI Systems / Driver Software | FFI comparisons (ctypes, cffi, pybind11, Cython), raw pointer exchange, custom RAII wrappers for memory safety. |
| [system_lowlevel_pytorch_systems_optimization.md](system_lowlevel_pytorch_systems_optimization.md) | PyTorch Systems Optimization | Hard | Deep Learning / AI Engineer | FSDP/DDP/ZeRO sharding, `torch.compile` capture paths, CUDA Graphs playbacks, custom Triton/C++ operators. |

---

## 4. Speech LLM & Voice Agent Engineering (5 Questions)
These files target speech and conversational AI engineering for voice-first systems, focusing on low-latency streaming audio pipelines, memory bottlenecks, model fine-tuning (NeMo), and high-performance serving (Riva/Triton NIMs).

| File Name & Link | Core Technical Topic | Difficulty | Target Role | Key Concept Explored |
| :--- | :--- | :--- | :--- | :--- |
| [speech_llm_voice_agent_architecture.md](speech_llm_voice_agent_architecture.md) | Voice Agent Pipeline | Hard | Speech LLM / AI Engineer | Streaming VAD/ASR/TTS, interruption (barge-in) handling, dual-model responders, async Python orchestrator. |
| [speech_llm_latency_optimization.md](speech_llm_latency_optimization.md) | Latency Profiling & Optimizations | Hard | Speech LLM / AI Engineer | WER/RTF/TTFA metrics, roofline memory bound computations, TensorRT-LLM in-flight batching, FP8 quantization. |
| [speech_llm_nemo_riva_stack.md](speech_llm_nemo_riva_stack.md) | NVIDIA Speech Stack & Guardrails | Hard | Speech LLM / AI Engineer | FastConformer/FastPitch customization, Riva NIM Triton compile paths, NeMo Guardrails Colang policy designs. |
| [speech_llm_multimodal_audio_language_models.md](speech_llm_multimodal_audio_language_models.md) | Multimodal Speech LLMs | Hard | Speech LLM / AI Engineer | Speech tokenization, RVQ EnCodec vectors, Whispers/AST encoders, projection matrices, vocoders (BigVGAN/Vocos). |
| [speech_llm_agent_benchmarking_evaluation.md](speech_llm_agent_benchmarking_evaluation.md) | Voice Agent Benchmarking | Hard | Speech LLM / AI Engineer | Speech quality metrics (PESQ, MCD, ViSQOL), WER/CER, latency metrics (TTFT, TTFA), dynamic simulator code. |

---

## 5. High-Performance System Design (6 Questions)
These files cover larger architectures and data flows, focusing on pipelines where GPU computation and multi-node throughput are critical bottleneck components.

| File Name & Link | System Architecture Topic | Difficulty | Target Role | Design Highlights |
| :--- | :--- | :--- | :--- | :--- |
| [system_design_autonomous_driving_perception.md](system_design_autonomous_driving_perception.md) | Autonomous Driving Perception | Hard | AV System Architect / Robotics | Sensor sync (PTP, Frame-Sync), zero-copy IPC, CPU/GPU/DLA task mapping, BEV fusion. |
| [system_design_distributed_gpu_training.md](system_design_distributed_gpu_training.md) | Distributed Training Cluster | Hard | Infrastructure / AI Platform | NVLink/NVSwitch, InfiniBand/RoCE, collective NCCL calls, GPUDirect RDMA & Storage, 3D Parallelism (TP/PP/DP + ZeRO-3). |
| [system_design_realtime_video_analytics.md](system_design_realtime_video_analytics.md) | Real-Time Video Analytics | Medium | Video Platform / AI Engineer | Hardware video decoders, dynamic batching, zero-copy memory pointers, shared memory IPC. |
| [system_design_triton_inference_server.md](system_design_triton_inference_server.md) | Scalable Inference Server | Hard | AI Systems / MLOps | Dynamic batching tuning, in-flight/continuous batching, Paged KV Cache management, business logic pipelines. |
| [system_design_gpu_microservices_bottleneck.md](system_design_gpu_microservices_bottleneck.md) | GPU Microservices Bottlenecks | Medium | Infrastructure / Cloud Software | Host-to-Device (H2D) PCIe bottlenecks, GPU multi-tenancy (MIG vs. MPS), backpressure queues, pinned memory optimization. |
| [system_design_task_scheduler_multiple_machines.md](system_design_task_scheduler_multiple_machines.md) | **Task Scheduler / Multiple Machines** | Hard | Systems / AI Platforms | Cooldown bounds, max-heap execution, SKIP LOCKED DB queues, Redis leases with lock TTL bounds. |

---

## 6. Behavioral, QA & Verification Focus (6 Questions)
These files address organizational values, troubleshooting methodology for hardware-software boundary layers, test environment automation, and ASIC verification topics.

| File Name & Link | Core Focus Area | Difficulty | Target Role | Key Concept Explored |
| :--- | :--- | :--- | :--- | :--- |
| [behavioral_star_intellectual_honesty.md](behavioral_star_intellectual_honesty.md) | Intellectual Honesty (Value) | Medium | All Roles (SWE / QA / HW) | STAR scenario showing response to a failed optimization hypothesis; admitting mistakes and pivoting fast. |
| [behavioral_star_one_team.md](behavioral_star_one_team.md) | One Team (Value) | Medium | All Roles (SWE / QA / HW) | STAR scenario solving a major cross-functional interface bottleneck; team collaboration and conflict resolution. |
| [qa_debug_hardware_software_integration.md](qa_debug_hardware_software_integration.md) | Hardware-Software Debugging | Hard | QA / Software Test Engineer | Tracking driver, kernel-space, and user-space issues; profiling tools, bus diagnostics, custom python wraps. |
| [qa_cpu_gpu_bottleneck_isolation.md](qa_cpu_gpu_bottleneck_isolation.md) | Profiling & Bottlenecks | Hard | Performance / QA Engineer | CPU vs. GPU bottleneck isolation using diagnostic tools; automation of metrics collection in Python. |
| [qa_automate_test_environment.md](qa_automate_test_environment.md) | Test Environment Control | Medium | QA / Software Test Engineer | Auditing device nodes/permissions, process isolation using device visible environment variables, detecting memory leaks. |
| [qa_vietnam_hardware_verification.md](qa_vietnam_hardware_verification.md) | ASIC Hardware Verification | Hard | ASIC Verification Engineer | SystemVerilog deep vs. shallow copy, UVM testbench design (sequencer, driver, monitor, scoreboard), waveform trace. |

---

## How to Prepare Using These Resources

1. **For Speech LLM & Voice Agent Roles:**
   - Focus on Section 4 (**Speech LLM & Voice Agent Engineering**), Section 3 (**Low-Level Python & PyTorch Internals**), and Section 1 (**Coding & Algorithms**).
   - Pay close attention to how you stream audio buffers asynchronously and handle sudden user interruptions.

2. **For Systems & Low-Level Roles:**
   - Focus on Section 2 (**Low-Level Systems & Hardware**) and Section 5 (**High-Performance System Design**).
   - Trace memory alignment and synchronization behaviors on CPU vs. GPU. Be ready to explain compiler/CPU reordering and CPU-GPU transfer speeds.

3. **For Software & QA Test Engineer Roles:**
   - Focus on Section 6 (**Behavioral, QA & Verification Focus**) and Section 1 (**Coding & Algorithms**).
   - Ensure you are comfortable talking about how you troubleshoot hardware-software boundaries, test pipeline automation scripts in Python, and how you manage device driver files/permissions in Linux.

4. **For Behavioral Preparation:**
   - Prepare your own STAR stories aligned with the core values. Use `behavioral_star_intellectual_honesty.md` and `behavioral_star_one_team.md` as templates to structure your responses.

---

## 📈 Study Roadmap: Progressive Difficulty Levels

Follow this roadmap to structure your preparation from foundational coding and culture, up to complex low-level concurrency and expert system architectures.

### Phase 1: Core Fundamentals & Culture (Easy to Medium)
*Goal: Understand the hiring loop format, align your behavioral stories with key core values, and solidify basic algorithm/scripting blocks.*
*   [ ] [hackerrank_and_inperson_coding.md](hackerrank_and_inperson_coding.md) — *Assessments & Onsite Interview Playbook*
*   [ ] [behavioral_star_intellectual_honesty.md](behavioral_star_intellectual_honesty.md) — *STAR Story: Admitting failures & pivoting*
*   [ ] [behavioral_star_one_team.md](behavioral_star_one_team.md) — *STAR Story: Silo-free collaboration & co-debugging*
*   [ ] [coding_search_rotated_array.md](coding_search_rotated_array.md) — *Rotated binary search, branch predictions, float division*
*   [ ] [coding_number_of_islands.md](coding_number_of_islands.md) — *DFS recursion depth limits, 1D mapping to optimize GC*
*   [ ] [coding_merge_intervals.md](coding_merge_intervals.md) — *Timsort mechanics, move semantics, array locality*
*   [ ] [qa_automate_test_environment.md](qa_automate_test_environment.md) — *Character device nodes, visible devices, orphan sweep scripting*

### Phase 2: Advanced Systems Coding & Interoperability (Medium to Hard)
*Goal: Implement custom allocations, thread synchronization, and master C/C++ to Python binding boundaries.*
*   [ ] [coding_lru_cache.md](coding_lru_cache.md) — *Custom pointer linked-lists, slots, Segmented Cache locks*
*   [ ] [coding_course_schedule.md](coding_course_schedule.md) — *Kahn's BFS vs. 3-state DFS, CSR graph layout optimization*
*   [ ] [coding_trie.md](coding_trie.md) — *Prefix trees, recursive destructor stack overflows, setdefault trap*
*   [ ] [system_lowlevel_memory_aligned_malloc.md](system_lowlevel_memory_aligned_malloc.md) — *Bitwise alignment masks, pointer offsets, SIMD faults*
*   [ ] [system_lowlevel_concurrency_producer_consumer.md](system_lowlevel_concurrency_producer_consumer.md) — *C++ thread-safe circular buffers, GIL locks*
*   [ ] [system_lowlevel_python_gil_concurrency.md](system_lowlevel_python_gil_concurrency.md) — *GIL internals, switch intervals, zero-copy shared memory IPC*
*   [ ] [system_lowlevel_python_c_bindings_ctypes.md](system_lowlevel_python_c_bindings_ctypes.md) — *Foreign function interface, raw pointers, RAII wrapper gc*
*   [ ] [qa_cpu_gpu_bottleneck_isolation.md](qa_cpu_gpu_bottleneck_isolation.md) — *Nsight telemetry, memory hierarchies, NVML API profiling*

### Phase 3: GPU Hardware & Lock-Free Execution (Hard)
*Goal: Master SIMT execution limits, coalescing mechanics, lock-free memory transitions, and deep system diagnostics.*
*   [ ] [system_lowlevel_cuda_warp_divergence.md](system_lowlevel_cuda_warp_divergence.md) — *SIMT scheduling, Volta ITS, register predication*
*   [ ] [system_lowlevel_cuda_bank_conflicts.md](system_lowlevel_cuda_bank_conflicts.md) — *Shared memory mapping, column conflicts, TILE padding*
*   [ ] [system_lowlevel_cuda_global_memory_coalescing.md](system_lowlevel_cuda_global_memory_coalescing.md) — *DRAM segments, coalesced copies, stride calculations, SoA*
*   [ ] [system_lowlevel_concurrency_lock_free_queue.md](system_lowlevel_concurrency_lock_free_queue.md) — *SPSC queues, MESI cache transitions, thread core isolation*
*   [ ] [system_lowlevel_python_memory_gc.md](system_lowlevel_python_memory_gc.md) — *Reference counting, cyclic GC sweep, PyMalloc arenas, leaks*
*   [ ] [qa_vietnam_hardware_verification.md](qa_vietnam_hardware_verification.md) — *SystemVerilog deep copy clones, UVM Scoreboards, assertions*
*   [ ] [qa_debug_hardware_software_integration.md](qa_debug_hardware_software_integration.md) — *OS TDR watchdogs, PCIe AER status flags, XID telemetry*

### Phase 4: High-Performance System Design & Voice AI (Hard to Expert)
*Goal: Scale deep learning models across clusters, design low-latency multimedia pipelines, and serve multimodal agents.*
*   [ ] [system_lowlevel_pytorch_systems_optimization.md](system_lowlevel_pytorch_systems_optimization.md) — *FSDP sharding, compile graphs, Triton kernels*
*   [ ] [speech_llm_nemo_riva_stack.md](speech_llm_nemo_riva_stack.md) — *FastConformer/FastPitch custom tuning, Colang guardrails*
*   [ ] [speech_llm_voice_agent_architecture.md](speech_llm_voice_agent_architecture.md) — *Low-latency voice streams, async barge-in cancellation*
*   [ ] [speech_llm_latency_optimization.md](speech_llm_latency_optimization.md) — *Roofline models, memory-bound decodes, Triton dynamic batching*
*   [ ] [speech_llm_multimodal_audio_language_models.md](speech_llm_multimodal_audio_language_models.md) — *RVQ EnCodec, Whisper encoders, MLP projection, BigVGAN vocoders*
*   [ ] [speech_llm_agent_benchmarking_evaluation.md](speech_llm_agent_benchmarking_evaluation.md) — *PESQ/ViSQOL quality, latency percentiles, noise simulators*
*   [ ] [system_design_autonomous_driving_perception.md](system_design_autonomous_driving_perception.md) — *ISP/DLA pipelines, BEV fusion, safety microcontrollers*
*   [ ] [system_design_distributed_gpu_training.md](system_design_distributed_gpu_training.md) | [system_design_triton_inference_server.md](system_design_triton_inference_server.md) — *NCCL cluster topology vs. KV cache serving*
*   [ ] [system_design_realtime_video_analytics.md](system_design_realtime_video_analytics.md) | [system_design_gpu_microservices_bottleneck.md](system_design_gpu_microservices_bottleneck.md) — *GStreamer GPU paths vs. MIG/MPS multi-tenancy*
*   [ ] [system_design_task_scheduler_multiple_machines.md](system_design_task_scheduler_multiple_machines.md) — *Distributed cooldown locks, SKIP LOCKED DB queues, Redis leases*

