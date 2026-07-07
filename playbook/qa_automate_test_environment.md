# QA/Testing: Automating GPU Test Environments and OS Controls

- **Category**: QA & Testing
- **Difficulty**: Medium to Hard
- **Target Role**: QA & Test Engineer / Systems Developer / DevOps Engineer / Infrastructure Architect
- **Source**: Glassdoor, Taro, NVIDIA Interview Experience
- **Flashcards**: [QA deck](flash_cards/behavioral_qa/qa.md)

---

## Question Description
> *"You need to automate test execution on a multi-GPU Linux test runner. Write a Python test automation harness that:
  1. Verifies that the required NVIDIA device files `/dev/nvidia*` exist and have correct permissions (e.g., read/write access for the test user).
  2. Programmatically isolates the test execution to a target GPU using env variables and verifies container-level device cgroup constraints.
  3. Executes the test workload and monitors execution under strict timeouts.
  4. Checks for GPU memory leaks or leftover orphan processes after the workload completes, cleaning them up if necessary."*

This question evaluates your system-level understanding of the Linux kernel, device nodes, process lifecycles, and environment isolation.

---

## Linux GPU Device Driver & Kernel Interface

NVIDIA drivers expose hardware control interfaces to the OS user space via character device files managed by the kernel modules (`nvidia.ko`, `nvidia-uvm.ko`, and `nvidia-modeset.ko`).

```
┌─────────────────────────────────────────────────────────────────────────┐
│                              User Space                                 │
│                                                                         │
│  [CUDA App] ──> [libcuda.so]                                            │
│                       │                                                 │
│                       ├──────> R/W access ──> /dev/nvidia0 (GPU 0 Node) │
│                       ├──────> R/W access ──> /dev/nvidiactl (Ctrl)     │
│                       └──────> R/W access ──> /dev/nvidia-uvm (UVM)     │
└───────────────────────╪─────────────────────────────────────────────────┘
                        │ System Call Interface (ioctl / mmap)
========================╪================================================== Kernel Boundary
                        ▼
┌─────────────────────────────────────────────────────────────────────────┐
│                             Kernel Space                                │
│                                                                         │
│   [nvidia-uvm.ko]               [nvidia.ko]       [nvidia-modeset.ko]   │
│   Unified Memory              Core GPU Driver     Display Management    │
└─────────────────────────────────────────────────────────────────────────┘
```

### 1. Primary Device Nodes
* `/dev/nvidiactl`: The master control node. Used by the user-mode driver (`libcuda.so`) to query GPU capabilities, topology, and allocate GPU instances.
* `/dev/nvidia-uvm`: The Unified Virtual Memory manager. Responsible for page faulting, CPU-GPU memory migration, and memory allocation mapping. Essential for all CUDA workloads.
* `/dev/nvidia[0-7]`: Character devices mapped to specific physical GPUs (Major number 195). The user process must have read/write access to the specific node it intends to use.

### 2. Device Container Isolation via Cgroups
In Docker and Kubernetes environments, GPUs are isolated using **Control Groups (cgroups)**:
* **cgroups v1 (Device Controller)**: Managed via the rules file at `/sys/fs/cgroup/devices/`. To allow GPU access, the container runtime writes to the `devices.allow` file:
  - `c 195:* rwm` (Allow all character devices with major number 195 - core GPUs and nvidiactl).
  - `c 235:* rwm` (Allow Unified Virtual Memory driver - dynamically assigned major number, typically 235/236 or check `/proc/devices`).
* **cgroups v2**: Uses eBPF programs of type `BPF_PROG_TYPE_CGROUP_DEVICE` to inspect and filter device read/write (`ioctl`) syscalls.

---

## Complete, Robust Python Test Harness

The script below verifies device nodes, checks cgroup boundaries, monitors test execution, and handles post-run cleanup of memory leaks and orphan processes using `pynvml` (with a subprocess fallback).

```python
import os
import stat
import subprocess
import sys
import time
import signal

try:
    import pynvml
    pynvml.nvmlInit()
    HAS_NVML = True
except ImportError:
    HAS_NVML = False

# Configuration
TARGET_GPU_INDEX = 0
WORKLOAD_CMD = [
    "python3", "-c", 
    "import torch; print(f'Torch executing on GPU: {torch.cuda.current_device()}'); x = torch.randn(2048, 2048, device='cuda')"
]
EXECUTION_TIMEOUT_SEC = 45

def verify_device_nodes(gpu_index):
    """Checks that critical device nodes exist and are readable/writable by the current user."""
    print("[*] Phase 1: Verifying NVIDIA device files and permissions...")
    required_paths = [
        "/dev/nvidiactl",
        "/dev/nvidia-uvm",
        f"/dev/nvidia{gpu_index}"
    ]
    
    # Verify physical file attributes
    for path in required_paths:
        if not os.path.exists(path):
            print(f"[!] Critical Error: Device node {path} does not exist. Check if driver is loaded.")
            return False
            
        # Verify read-write capability
        if not (os.access(path, os.R_OK) and os.access(path, os.W_OK)):
            mode = os.stat(path).st_mode
            print(f"[!] Access Denied: No R/W access to {path}. Permissions: {oct(mode)}")
            return False
            
        print(f"    [+] {path} - Verified R/W access.")
    return True

def verify_cgroup_access():
    """Inspects cgroups v1 /sys files to ensure container is not blocking GPU nodes."""
    print("[*] Phase 2: Verifying Container cgroup device rules...")
    cgroup_path = "/sys/fs/cgroup/devices/devices.list"
    if os.path.exists(cgroup_path):
        try:
            with open(cgroup_path, "r") as f:
                rules = f.read()
                # Check for major 195 (NVIDIA) and 235-240 (Dynamic UVM major range)
                if "195:" not in rules and "a *:* rwm" not in rules:
                    print("    [!] Warning: Cgroup devices.list may restrict access to Major 195 (NVIDIA).")
                    return False
        except IOError:
            print("    [!] Could not read devices.list (non-root or restricted). Skipping.")
    print("    [+] Cgroups check passed (or v2 default active).")
    return True

def get_gpu_memory_used(gpu_index):
    """Queries GPU memory usage in MiB."""
    if HAS_NVML:
        try:
            handle = pynvml.nvmlDeviceGetHandleByIndex(gpu_index)
            info = pynvml.nvmlDeviceGetMemoryInfo(handle)
            return int(info.used / (1024 * 1024))
        except Exception as e:
            print(f"    [!] NVML memory query failed: {e}")
    # Fallback to nvidia-smi
    try:
        cmd = f"nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits -i {gpu_index}"
        out = subprocess.check_output(cmd, shell=True, text=True, stderr=subprocess.DEVNULL)
        return int(out.strip())
    except Exception:
        return 0

def run_isolated_workload(gpu_index, command, timeout):
    """Executes the command isolated to the selected GPU using environment configuration."""
    print(f"\n[*] Phase 3: Launching workload. Isolating execution to GPU {gpu_index}...")
    
    # CUDA_VISIBLE_DEVICES makes only the specified physical GPU visible to the CUDA runtime, 
    # remapping its index to logical GPU 0 within the application context.
    custom_env = os.environ.copy()
    custom_env["CUDA_VISIBLE_DEVICES"] = str(gpu_index)
    
    start_time = time.time()
    try:
        process = subprocess.Popen(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            env=custom_env,
            text=True,
            preexec_fn=os.setsid # Launch in a new process group to capture child processes
        )
        
        stdout, stderr = process.communicate(timeout=timeout)
        elapsed = time.time() - start_time
        print(f"    [+] Workload finished execution in {elapsed:.2f}s (Exit Code: {process.returncode})")
        if stdout:
            print(f"    [+] Stdout:\n{stdout.strip()}")
        if stderr:
            print(f"    [!] Stderr:\n{stderr.strip()}")
        return process.returncode
    except subprocess.TimeoutExpired:
        print(f"    [!!!] Workload exceeded timeout limit ({timeout}s). Terminating process group...")
        # Kill the entire process group (prevents orphan child runs)
        os.killpg(os.getpgid(process.pid), signal.SIGKILL)
        return -9

def cleanup_leftovers(gpu_index, baseline_mem):
    """Finds and kills leftover orphan processes and verifies memory release."""
    print(f"\n[*] Phase 4: Sweeping for resource leaks on GPU {gpu_index}...")
    time.sleep(3) # Wait for driver context teardown
    
    current_mem = get_gpu_memory_used(gpu_index)
    mem_delta = current_mem - baseline_mem
    print(f"    [+] Memory: Baseline = {baseline_mem} MiB, Current = {current_mem} MiB, Delta = {mem_delta} MiB")
    
    # Identify active PIDs on the target GPU
    active_pids = []
    if HAS_NVML:
        try:
            handle = pynvml.nvmlDeviceGetHandleByIndex(gpu_index)
            # Check for compute and graphics processes
            procs = pynvml.nvmlDeviceGetComputeRunningProcesses(handle)
            active_pids.extend([p.pid for p in procs])
            procs_graphics = pynvml.nvmlDeviceGetGraphicsRunningProcesses(handle)
            active_pids.extend([p.pid for p in procs_graphics])
        except Exception as e:
            print(f"    [!] NVML processes query failed: {e}")
    else:
        # Fallback parsing
        try:
            cmd = f"nvidia-smi --query-computes=pid --format=csv,noheader -i {gpu_index}"
            out = subprocess.check_output(cmd, shell=True, text=True, stderr=subprocess.DEVNULL)
            active_pids = [int(p.strip()) for p in out.splitlines() if p.strip().isdigit()]
        except Exception:
            pass

    # Process Cleanup and Audit
    if active_pids:
        print(f"    [!] Active/Orphan PIDs found on GPU {gpu_index}: {active_pids}")
        for pid in active_pids:
            try:
                # Read process info from /proc
                with open(f"/proc/{pid}/cmdline", "r") as f:
                    cmdline = f.read().replace('\x00', ' ').strip()
                print(f"        -> Orphan PID: {pid} ({cmdline})")
                
                # Check if it has parent PID 1 (orphaned and adopted)
                with open(f"/proc/{pid}/status", "r") as f:
                    ppid_line = [line for line in f if line.startswith("PPid:")]
                    ppid = int(ppid_line[0].split()[1]) if ppid_line else -1
                
                if ppid == 1:
                    print(f"           [!] Verified orphan (PPID 1). Sending SIGKILL to {pid}...")
                    os.kill(pid, signal.SIGKILL)
            except IOError:
                # Process might have ended in the meantime
                pass
    else:
        print("    [+] Process check: Clean. No orphan runs found.")
        
    if mem_delta > 15:
        print(f"    [!] Leak Alert: GPU memory remains {mem_delta} MiB above baseline!")
        return False
        
    print("    [+] Memory check: Clean.")
    return True

def main():
    if not verify_device_nodes(TARGET_GPU_INDEX):
        print("[!] Device check failed. Terminating.")
        sys.exit(1)
        
    verify_cgroup_access()
    
    baseline_mem = get_gpu_memory_used(TARGET_GPU_INDEX)
    exit_code = run_isolated_workload(TARGET_GPU_INDEX, WORKLOAD_CMD, EXECUTION_TIMEOUT_SEC)
    
    if exit_code != 0:
        print(f"[!] Workload failure detected (Exit Code: {exit_code}).")
        
    cleanup_leftovers(TARGET_GPU_INDEX, baseline_mem)

if __name__ == "__main__":
    try:
        main()
    finally:
        if HAS_NVML:
            pynvml.nvmlShutdown()
```

---

## Pro-Tip: How to Impress the Interviewer

> [!IMPORTANT]
> **Highlight Process Group Isolation and cgroups**
> When asked about process termination in automation, emphasize that simply calling `kill()` on a parent python script is insufficient. The workload may spawn child processes that get reparented to PID 1 (systemd) upon parent termination. Mention that your script uses `os.setsid` in the `preexec_fn` parameter to launch the workload in a unique **Process Group**. If a timeout occurs, you send `SIGKILL` to the entire group (`os.killpg(pgid, SIGKILL)`), ensuring that all descendant children are terminated and do not leak GPU memory.

---

## Common Follow-Up Questions & How to Answer

### Q1: "If the test workload has ended, but `nvidia-smi` shows GPU memory is still allocated, why does this occur, and how do you resolve it?"
**Answer:**
"This occurs due to one of three issues:
1. **Orphan Processes**: The application spawned child processes (helper workers) which are still alive, holding their own CUDA contexts. This keeps the memory allocated. They can be found and terminated using the `nvidia-smi --query-computes=pid` interface or inspecting the `/proc` directory.
2. **Zombie Processes**: The main process exited but remains in a zombie state (`Z`) because the parent process has not read its exit status (`waitpid`). The OS cannot release the resources (including driver file descriptors) until the parent reaps the zombie.
3. **Driver Context Cache**: Sometimes the NVIDIA driver holds onto memory allocations briefly to avoid reallocation latency for immediate subsequent runs. Resolving this requires forcing driver state clearance or reloading the kernel module (`sudo rmmod nvidia_uvm && sudo modprobe nvidia_uvm`) if the lock is severe."

### Q2: "How would you automate GPU configuration inside a Docker container without mapping the entire host `/dev` namespace?"
**Answer:**
"Using the **NVIDIA Container Toolkit** (`nvidia-container-runtime`), you do not need to manually mount `/dev/nvidia*` nodes. You isolate the GPU at container launch using environment flags:
```bash
docker run --gpus device=1 -e NVIDIA_VISIBLE_DEVICES=1 my_test_image
```
Under the hood, the toolkit intercepts container creation, queries NVML, configures the cgroups device access list to permit access only to major/minor IDs of GPU 1 and `/dev/nvidiactl` / `/dev/nvidia-uvm`, and dynamically injects the appropriate GPU device nodes into the container's private `/dev` namespace before running the application."
