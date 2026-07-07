# QA/Testing: Isolating CPU vs. GPU Performance Bottlenecks

- **Category**: QA & Testing
- **Difficulty**: Hard
- **Target Role**: QA & Test Engineer / Performance Engineer / AI Engineer / CUDA Systems Engineer
- **Source**: Glassdoor, Taro, LeetCode Discuss
- **Flashcards**: [QA deck](flash_cards/behavioral_qa/qa.md)

---

## Question Description
> *"A deep learning inference pipeline utilizing TensorRT/CUDA is failing to meet its 10ms latency SLA. How do you systematically profile the system to isolate whether the bottleneck is CPU-bound (e.g., host-side data preprocessing, driver kernel launch overhead, thread synchronization) or GPU-bound (e.g., memory bandwidth, compute capability, warp occupancy)?"*

NVIDIA systems engineers must possess "compute intimacy"—a precise understanding of how data and execution contexts transition between the host CPU and the GPU. This question tests your ability to analyze hardware telemetry, read timeline profiles, and optimize low-level pipelines.

---

## GPU Compute & Memory Architecture Foundations

To isolate bottlenecks, you must understand the hardware execution model:

```
                  ┌──────────────────────────────────────────────┐
                  │                 Host CPU                     │
                  └──────────────────────┬───────────────────────┘
                                         │ PCIe Gen5 x16 (63 GB/s)
                  ┌──────────────────────▼───────────────────────┘
                  │             GPU L2 Cache (40-96 MB)          │
                  │             Latency: ~30-60 Cycles           │
                  └──────────────────────┬───────────────────────┘
                                         │ Wide DRAM Bus (e.g., 5120-bit)
                  ┌──────────────────────▼───────────────────────┘
                  │         Device Memory (HBM3 / GDDR6)         │
                  │        Bandwidth: ~2-3 TB/s, Latency: ~300ns │
                  └──────────────────────┬───────────────────────┘
                                         │ Cache Line Load (128-byte)
                  ┌──────────────────────▼───────────────────────┘
                  │             Streaming Multiprocessors        │
                  │          ┌────────────────────────┐          │
                  │          │     SMem/L1 Cache      │          │
                  │          │ Latency: ~10-20 Cycles │          │
                  │          └───────────┬────────────┘          │
                  │                      ▼                       │
                  │          ┌────────────────────────┐          │
                  │          │     Warp Scheduler     │          │
                  │          └───────────┬────────────┘          │
                  │                      ▼                       │
                  │          ┌────────────────────────┐          │
                  │          │ FP32 / INT / Tensor Cores│        │
                  │          └────────────────────────┘          │
                  └──────────────────────────────────────────────┘
```

### 1. Warp Scheduling and Instruction Latency
* Each Streaming Multiprocessor (SM) contains multiple **Warp Schedulers**.
* A warp consists of 32 threads executing in SIMT (Single Instruction, Multiple Threads) fashion.
* Every clock cycle, a warp scheduler selects an active warp whose instruction operands are ready (not stalled on memory or dependency execution) and dispatches it to the execution units (ALUs, FPUs, or Tensor Cores).
* If a warp is waiting for a memory load from device memory (HBM3/GDDR6, taking $\sim 200\text{ to }400\text{ clock cycles}$), it is stalled. The scheduler must hide this latency by context-switching to another active, ready warp in $\mathcal{O}(1)$ time. If there are not enough active warps (low occupancy), the SM stalls, indicating a memory-latency bottleneck.

### 2. Memory Coalescing & Cache Line Transactions
* The GPU memory controller retrieves data in **32-byte** or **128-byte** aligned segments.
* **Coalesced Memory Access**: When all 32 threads in a warp access a contiguous block of memory (e.g., 32 consecutive 4-byte floats), the memory hardware coalesces this into a single 128-byte transaction. 
* **Uncoalesced Memory Access**: If the threads access scattered addresses, the transfer cannot be coalesced, forcing the memory system to execute up to 32 separate transactions to retrieve the same amount of data, wasting up to 96% of the available memory bandwidth.

---

## Systematic Isolation Workflow

### Step 1: High-Level Resource Monitoring (Coarse-Grained)
Run concurrent system-level monitors under realistic load.
1. **CPU Tracking**: Monitor CPU load per core. If a single core is pinned at 100% while others are idle, the application is likely serialized on a single host thread (e.g., Python OpenCV image resizing or JSON parsing).
2. **GPU Telemetry**: Run high-frequency GPU query loops:
   ```bash
   nvidia-smi --query-gpu=utilization.gpu,utilization.memory,power.draw,clocks.current.graphics --format=csv -l 1
   ```
   * **utilization.gpu**: The percentage of time over the past sample period during which one or more kernels were executing on the GPU.
   * **utilization.memory**: The percentage of time during which the memory controller was reading from or writing to device memory.

#### Analysis Matrix:
* **High CPU, Low GPU (< 30%)**: The pipeline is **Host CPU-bound**. The GPU is starving because the host cannot dispatch memory copies or kernel execution blocks fast enough.
* **Low CPU, High GPU (> 80%)**: The pipeline is **Device GPU-bound**. The GPU is fully active.
* **Low CPU, Low GPU**: The system is stalled on **Synchronous API overhead** (e.g., `cudaDeviceSynchronize()` stalling host threads) or physical disk/network I/O.

---

### Step 2: System-Level Timeline Profiling (Nsight Systems)
Capture an end-to-end trace with **NVIDIA Nsight Systems** (`nsys`) to analyze CPU-GPU overlap:
```bash
nsys profile --trace=cuda,osrt,nvtx,stdio \
             --sample=cpu \
             --output=nsys_report \
             --export=sqlite \
             ./my_inference_app
```

Open `nsys_report.nsys-rep` in the Nsight Systems GUI:
1. **Look for Gaps**: Inspect the **GPU Solves (Kernels)** row. If you see large blank intervals between kernels, measure the gap duration. If the gaps match the duration of host-side NVTX ranges (e.g., `PreProcessImage`), the host is the bottleneck.
2. **Check API Runtime Calls**: Sort the CUDA API calls. If `cudaMalloc` or `cudaFree` are called repeatedly during the execution loop, this introduces synchronous driver locks. If `cudaMemcpy` (synchronous) is used instead of `cudaMemcpyAsync`, it forces the CPU thread to block until the copy completes, destroying pipeline concurrency.

```
Nsight Systems Timeline Analysis:

Good Pipeline Overlap:
CPU: [Kernel Launch 1][Kernel Launch 2][Kernel Launch 3]
GPU: ░░░[Memcpy H2D 1][Kernel 1][Memcpy H2D 2][Kernel 2][Memcpy H2D 3][Kernel 3]░░░

Bad Pipeline Overlap (Synchronous / CPU-Bound):
CPU: [Memcpy H2D 1]------(Blocks)------[Kernel 1]------(Blocks)------
GPU:              [Memcpy H2D 1]               [Kernel 1]
```

---

### Step 3: Kernel-Level Deep-Dive (Nsight Compute)
If the GPU is saturated, identify the limiting execution hardware inside the worst-performing kernels using **NVIDIA Nsight Compute** (`ncu`):
```bash
ncu --section SpeedOfLight --metrics sm__throughput.percent.gpu,dram__throughput.percent.gpu,smsp__warp_issue_active.avg ./my_inference_app
```

Identify the bottleneck category based on the **Speed of Light (SOL)** metrics:
* **Compute Bound**: `sm__throughput.percent.gpu` is high (e.g., >80%) and significantly higher than `dram__throughput.percent.gpu`.
  - *Mitigation*: Enable Mixed Precision (FP16/BF16/INT8 Tensor Cores), optimize compiler parameters, and use register bounds (`__launch_bounds__`) to prevent register spilling.
* **Memory Bound**: `dram__throughput.percent.gpu` is high (e.g., >80%).
  - *Mitigation*: Coalesce memory writes, use Shared Memory as a user-managed cache to reuse data across threads in a block, and avoid redundant global memory reads.
* **Warp Latency Bound**: Both SOL throughputs are low, but the kernel executes slowly. Look at the stall reasons (e.g., `Stall Barrier`, `Stall MIO` (Memory Input/Output)).
  - *Mitigation*: Increase grid size to launch more blocks, or restructure the code to reduce instruction dependency latency.

---

## Automated Bottleneck Detector Script (Python)

This script automates resource collection. It uses the `pynvml` (NVIDIA Management Library) bindings for low-overhead telemetry, with a fallback to `nvidia-smi` parser if not installed.

```python
import subprocess
import time
import psutil
import threading
import sys

# Try importing pynvml for optimized GPU queries
try:
    import pynvml
    pynvml.nvmlInit()
    HAS_NVML = True
except ImportError:
    HAS_NVML = False

MONITOR_INTERVAL = 0.2  # Seconds
MONITOR_DURATION = 8.0  # Seconds

cpu_samples = []
gpu_samples = []
mem_samples = []

def get_gpu_metrics():
    """Retrieves (gpu_utilization, memory_controller_utilization) from NVML or nvidia-smi."""
    if HAS_NVML:
        try:
            # Assumes Device 0
            handle = pynvml.nvmlDeviceGetHandleByIndex(0)
            rates = pynvml.nvmlDeviceGetUtilizationRates(handle)
            return float(rates.gpu), float(rates.memory)
        except Exception:
            return 0.0, 0.0
    else:
        # Fallback to nvidia-smi parsing
        try:
            cmd = "nvidia-smi --query-gpu=utilization.gpu,utilization.memory --format=csv,noheader,nounits"
            out = subprocess.check_output(cmd, shell=True, text=True, stderr=subprocess.DEVNULL)
            gpu, mem = out.strip().split(",")
            return float(gpu), float(mem)
        except Exception:
            return 0.0, 0.0

def monitor_loop(stop_event):
    while not stop_event.is_set():
        cpu = psutil.cpu_percent(interval=None)
        gpu, mem = get_gpu_metrics()
        
        cpu_samples.append(cpu)
        gpu_samples.append(gpu)
        mem_samples.append(mem)
        time.sleep(MONITOR_INTERVAL)

def analyze_diagnostics():
    if not cpu_samples:
        print("[!] No data captured.")
        return
        
    avg_cpu = sum(cpu_samples) / len(cpu_samples)
    avg_gpu = sum(gpu_samples) / len(gpu_samples)
    avg_mem = sum(mem_samples) / len(mem_samples)
    
    print("\n" + "="*50)
    print("      GPU/CPU BOTTENECK DETECTOR DIAGNOSTICS      ")
    print("="*50)
    print(f"Captured Samples: {len(cpu_samples)}")
    print(f"Average CPU Load:  {avg_cpu:.2f}%")
    print(f"Average GPU Core:  {avg_gpu:.2f}%")
    print(f"Average GPU Mem:   {avg_mem:.2f}%")
    print("-"*50)
    
    # Isolation Rules
    if avg_gpu < 35.0 and avg_cpu > 70.0:
        print("[!] DIAGNOSIS: HOST CPU-BOUND BOTTLE-NECK DETECTED.")
        print("    - Reasons: The host CPU is heavily loaded while the GPU sits idle.")
        print("    - Action Items:")
        print("      1. Profile CPU host code for heavy operations (e.g. data decoding, image parsing).")
        print("      2. Ensure you are utilizing pinned memory (cudaHostAlloc) to optimize transfers.")
        print("      3. Offload data preprocessing to the GPU (e.g., using NVIDIA DALI).")
        
    elif avg_gpu > 75.0 and avg_mem > 70.0:
        print("[!] DIAGNOSIS: DEVICE MEMORY BANDWIDTH-BOUND BOTTLE-NECK DETECTED.")
        print("    - Reasons: High GPU and High Memory controller utilization.")
        print("    - Action Items:")
        print("      1. Audit memory access patterns for uncoalesced memory reads/writes.")
        print("      2. Use Shared Memory caches to reduce global device memory transactions.")
        print("      3. Try compressing the model or using lower-precision quantization (FP16/INT8).")
        
    elif avg_gpu > 75.0 and avg_mem <= 35.0:
        print("[!] DIAGNOSIS: DEVICE COMPUTE-BOUND BOTTLE-NECK DETECTED.")
        print("    - Reasons: High GPU Core activity but low memory controller utilization.")
        print("    - Action Items:")
        print("      1. Verify if Tensor Cores are active (mixed precision arithmetic).")
        print("      2. Run Nsight Compute to analyze execution stalls (e.g. math dependencies).")
        
    elif avg_gpu < 25.0 and avg_cpu < 25.0:
        print("[!] DIAGNOSIS: SYNCHRONIZATION OR I/O STALL DETECTED.")
        print("    - Reasons: Both processors are idling. The system is likely blocked on synchronous calls.")
        print("    - Action Items:")
        print("      1. Scan your source files for blocking calls like cudaDeviceSynchronize().")
        print("      2. Optimize disk I/O, dataset loader queues, or network ingress queues.")
    else:
        print("[+] DIAGNOSIS: Balanced pipeline. System resources are distributed evenly.")
    print("="*50 + "\n")

if __name__ == "__main__":
    stop_event = threading.Event()
    monitor_thread = threading.Thread(target=monitor_loop, args=(stop_event,))
    
    print(f"[*] Beginning telemetry capture loop for {MONITOR_DURATION} seconds...")
    monitor_thread.start()
    
    try:
        time.sleep(MONITOR_DURATION)
    except KeyboardInterrupt:
        print("[*] Aborting trace early...")
    finally:
        stop_event.set()
        monitor_thread.join()
        
    analyze_diagnostics()
    
    if HAS_NVML:
        pynvml.nvmlShutdown()
