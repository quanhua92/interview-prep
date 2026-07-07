# QA/Testing: Debugging Hardware-Software Integration Issues

- **Category**: QA & Testing
- **Difficulty**: Hard
- **Target Role**: QA & Test Engineer / Systems Developer / Embedded Developer / Silicon Validation Engineer
- **Source**: Glassdoor, Taro, NVIDIA Interview Experience
- **Flashcards**: [QA deck](flash_cards/behavioral_qa/qa.md)

---

## Question Description
> *"How do you debug an intermittent system hang or crash—specifically a GPU Timeout Detection and Recovery (TDR) or kernel panic—in a newly integrated hardware-software platform? How do you systematically isolate whether the root cause is in the hardware silicon, GPU firmware, the OS kernel driver, or the user-space application/libraries?"*

Debugging at the hardware-software boundary is a standard task at NVIDIA. The interviewer wants to see a structured, first-principles troubleshooting methodology rather than random guessing.

---

## Hardware-Software Interface Architecture

```
┌────────────────────────────────────────────────────────────────────────┐
│                        User Space Application                          │
│          (PyTorch / TensorRT / Custom CUDA Kernel Pipelines)          │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │ CUDA Toolkit API
┌───────────────────────────────────▼────────────────────────────────────┐
│                  NVIDIA User-Mode Driver (libcuda.so)                 │
│              (Context Creation, Command Buffer Assembly)               │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │ ioctl / Syscalls
====================================│===================================== OS Kernel Boundary
                                    ▼
┌────────────────────────────────────────────────────────────────────────┐
│                NVIDIA Kernel-Mode Driver (nvidia.ko)                   │
│          (Memory Mapping MMIO/DMA, Interrupt Handling, MSI-X)          │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │ PCIe Bus / BAR0 MMIO Registers
┌───────────────────────────────────▼────────────────────────────────────┐
│                 GPU System Processor (GSP) Firmware                   │
│              (GPU Power Management, Engine Scheduling)                 │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │ Microcode Commands
┌───────────────────────────────────▼────────────────────────────────────┐
│                    Silicon Hardware Engines                            │
│           (CUDA Cores, NVDEC/NVENC, HBM/GDDR Controller)               │
└────────────────────────────────────────────────────────────────────────┘
```

---

## Detailed TDR and Watchdog Mechanisms

### Windows: Timeout Detection & Recovery (TDR)
On Windows, the OS Graphic Kernel (`dxgkrnl.sys`) monitors the execution of command packets on the GPU.
* **Mechanism**: If a single command sequence takes longer than `TdrDelay` (default: **2 seconds**), the OS schedules a driver reset.
* **Triggering System**: The OS attempts to reinitialize the display driver by calling `DdiResetEngine` and `DdiReconstituteQueue`.
* **Registry Keys**: In QA environments, we tune `TdrDelay` and `TdrDdiDelay` (e.g., setting them to 10 seconds or disabling them via registry to capture JTAG traces of the hung state).

### Linux: GPU Watchdog & Reset Paths
On Linux, there is no system-wide TDR. Instead:
* **Driver Watchdog**: The `nvidia.ko` kernel driver schedules a polling timer. If a channel command queue is blocked (e.g., host-to-device FIFO progress stalls), the driver identifies the hung channel and outputs a specific **XID Error** to `/var/log/messages` or `dmesg`.
* **GPU Recovery**: The driver attempts to recover the channel. If recovery fails, it attempts a **GPU Reset** (Function Level Reset - FLR, Secondary Bus Reset - SBR, or PM cold reset). If the reset path hangs, the kernel driver stalls, leading to a host kernel panic or CPU soft lockup.

---

## Systematic Debugging & Isolation Workflow

### Phase 1: Data Collection & Environmental Auditing
When an intermittent hang occurs, the first step is to capture the system state immediately prior to and during the crash:
1. **System Logs**: 
   - **Linux**: Execute the native troubleshooting utility:
     ```bash
     sudo nvidia-bug-report.sh
     ```
     This script compresses GPU registers, driver status, thermal history, and OS logs into `nvidia-bug-report.log.gz`.
2. **Crash Dump Analysis**:
   - Enable `kdump` (Linux kernel core dump) to capture memory status during a panic.
   - For Windows, inspect the Minidump directory for `VIDEO_TDR_FAILURE` (Bug Check `0x116` or `0x117`) dump files and analyze using WinDbg:
     ```text
     !analyze -v
     lmvm nvlddmkm   # Inspect the exact build time and state of the NVIDIA driver
     ```

---

### Phase 2: Isolating the Layers (Step-by-Step)

#### Step 1: Isolate the Application Layer (User-Space)
Determine if the crash is caused by memory corruption or API misuse in user space.
* **Action**: Run the application under **NVIDIA Compute Sanitizer** to check for out-of-bounds access, race conditions, or uninitialized memory in CUDA kernels:
  ```bash
  compute-sanitizer --tool memcheck --leak-check full ./my_cuda_app
  ```
* **Analysis**: 
  - If `compute-sanitizer` reports an **Illegal Address Access** or **Hardware Stack Overflow**, the bug is in the **User-Space CUDA Kernel** (software).
  - If the run fails without memory violations, check for host/device synchronization bugs using:
    ```bash
    compute-sanitizer --tool synccheck ./my_cuda_app
    ```

#### Step 2: Isolate the Kernel Driver vs. Hardware Firmware
If the system hangs, or a GPU timeout occurs, determine if the driver lost connection to the hardware.
* **Action**: Check the PCIe register state and PCIe Advanced Error Reporting (AER) status:
  ```bash
  # Check if the GPU is visible on the PCIe bus
  lspci -d 10de:* 
  # Check PCIe link status (current speed vs. target capabilities)
  sudo lspci -vvv -d 10de:* | grep -i -E "LnkSta:|LnkCap:"
  ```
* **Analysis**:
  - If the GPU disappears completely from `lspci`, the issue is **Hardware/Silicon-level** (e.g., physical PCIe link drop, board-level power rail sag, or GPU GSP firmware crash).
  - Inspect `/var/log/dmesg` for NVIDIA **XID Errors**:
    - **XID 31 (GPU Memory Page Fault)**: Software driver/MMU page-table configuration issue, or invalid virtual address reference.
    - **XID 45 (Engine Scheduler Timeout)**: Preemption failed. A long-running kernel is blocking the scheduler. Often solved by dividing kernels into smaller work blocks.
    - **XID 79 (GPU Fallen off Bus)**: The PCIe link dropped. Likely thermal shutdown, PCIe clock stability issue, or voltage droop on the power rail.
    - **XID 92 (GSP RPC Timeout)**: The communication link between the Host Driver and GSP (GPU System Processor) microcode timed out. Points to a GSP firmware lockup.

#### Step 3: Isolate Hardware Silicon vs. Firmware
If the issue is suspected to be hardware, differentiate between transient hardware noise (signal integrity) and firmware bugs.
* **Action**: 
  - Downclock the GPU core and memory clocks using `nvidia-smi` to reduce signal noise and heat:
    ```bash
    sudo nvidia-smi -pm 1 # Enable persistence mode
    sudo nvidia-smi -lgc 1000,1200 # Lock GPU clocks to low frequency (e.g., 1000-1200 MHz)
    ```
  - Force PCIe Link Speed degradation to rule out PCIe Gen4/Gen5 signal integrity issues:
    ```bash
    # Boot kernel with pci=noaer or limit PCIe speed in GRUB: pcie_aspm=off
    ```
* **Analysis**:
  - If downclocking the GPU or downgrading PCIe link speed (e.g., forcing Gen3 instead of Gen5) resolves the intermittent hang, it indicates a **Hardware / Silicon Stability** issue (marginal power delivery network (PDN), bad board-level decoupling capacitors, high clock jitter, or thermal/silicon aging).
  - If the issue persists at low clocks and the GSP firmware register dumps show a stuck RPC queue, it is a **Firmware Bug**.

---

## Test Automation Diagnostic Script (Python)

Below is an automated, production-grade test diagnostic script. It launches a specified workload, monitors system logs, probes PCIe status via `/sys`, and pulls full diagnostics if a GPU failure is detected.

```python
import subprocess
import time
import os
import sys
import re

LOG_DIR = "/var/log/gpu_diagnostics"
os.makedirs(LOG_DIR, exist_ok=True)

def run_command(cmd, timeout=15):
    try:
        result = subprocess.run(
            cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=timeout
        )
        return result.stdout.strip(), result.stderr.strip(), result.returncode
    except subprocess.TimeoutExpired:
        return "TIMEOUT", "TIMEOUT", -1

def get_pcie_aer_errors():
    """Inspects sysfs directly to check for PCIe Advanced Error Reporting status."""
    pcie_devices = "/sys/bus/pci/devices"
    aer_report = []
    if not os.path.exists(pcie_devices):
        return "sysfs PCI devices not accessible"
        
    for device in os.listdir(pcie_devices):
        if not device.startswith("0000:"): # Match standard domain prefix
            continue
        aer_path = os.path.join(pcie_devices, device, "aer_dev_correctable")
        if os.path.exists(aer_path):
            try:
                with open(aer_path, "r") as f:
                    val = f.read().strip()
                    if val != "0" and val != "":
                        aer_report.append(f"Device {device} Correctable Errors: {val}")
            except IOError:
                pass
    return "\n".join(aer_report) if aer_report else "No PCIe AER errors flagged in sysfs."

def check_gpu_health():
    """Returns 'HEALTHY', 'HUNG_DRIVER', or 'HARDWARE_DISCONNECTED'."""
    stdout, stderr, code = run_command("nvidia-smi --query-gpu=name,temperature.gpu,power.draw --format=csv,noheader")
    
    if stdout == "TIMEOUT":
        return "HUNG_DRIVER"
    if code != 0 or "lost connection" in stderr.lower():
        # Double check PCIe availability
        lspci_out, _, lspci_code = run_command("lspci -d 10de:*")
        if not lspci_out or lspci_code != 0:
            return "HARDWARE_DISCONNECTED"
        return "HUNG_DRIVER"
    
    return "HEALTHY"

def collect_debug_payload(reason):
    timestamp = int(time.time())
    log_prefix = f"{LOG_DIR}/gpu_crash_{timestamp}"
    print(f"[!] Critical degradation detected: {reason}. Gathering diagnostic payload...")

    # 1. Capture Kernel Dmesg
    dmesg_stdout, _, _ = run_command("dmesg | tail -n 250")
    with open(f"{log_prefix}_dmesg.log", "w") as f:
        f.write(dmesg_stdout)

    # 2. Extract PCIe AER Stats from Sysfs
    aer_stats = get_pcie_aer_errors()
    with open(f"{log_prefix}_pcie_aer.log", "w") as f:
        f.write(aer_stats)

    # 3. Check Interrupt Distribution
    interrupts, _, _ = run_command("grep -i -E 'nvidia|msi' /proc/interrupts")
    with open(f"{log_prefix}_interrupts.log", "w") as f:
        f.write(interrupts)

    # 4. Generate Official NVIDIA Bug Report
    print("[*] Launching nvidia-bug-report.sh...")
    run_command(f"sudo nvidia-bug-report.sh --output-file {log_prefix}_nvidia-bug-report.log.gz", timeout=90)
    
    print(f"[+] Diagnostics successfully packaged under: {LOG_DIR}")

def monitor_workload(workload_cmd):
    print(f"[*] Starting QA Workload: {workload_cmd}")
    process = subprocess.Popen(workload_cmd, shell=True)
    
    try:
        while True:
            ret_code = process.poll()
            if ret_code is not None:
                if ret_code != 0:
                    print(f"[!] Workload exited with code {ret_code}.")
                    collect_debug_payload(f"Workload failure (Exit Code: {ret_code})")
                    sys.exit(1)
                else:
                    print("[+] Workload run completed. Re-triggering execution...")
                    process = subprocess.Popen(workload_cmd, shell=True)
            
            # Check physical and driver level health
            health_status = check_gpu_health()
            if health_status != "HEALTHY":
                print(f"[!!!] GPU instablity detected: {health_status}")
                process.terminate()
                try:
                    process.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    process.kill()
                collect_debug_payload(health_status)
                sys.exit(2)
                
            time.sleep(2)
    except KeyboardInterrupt:
        process.terminate()
        print("[*] Monitoring stopped by user.")

if __name__ == "__main__":
    # Point this to the target executable or script under test
    monitor_workload("./stress_test_gpu_app")
```

---

## Pro-Tip: How to Impress the Interviewer

> [!IMPORTANT]
> **Talk about register-level diagnostics and JTAG debugging**
> Explain that when debugging a hard-locked platform (where even kernel logs are unavailable), you hook up a JTAG debugger (e.g., Lauterbach) directly to the SoC/GPU. You dump the **BAR0 register space** (specifically the interrupt status and execution pointer registers) to see what command queue buffer index the GPU pipeline is stuck on. Mentioning this hardware-level debugging capability separates junior testers from elite systems validation engineers.

---

## Common Follow-Up Questions & How to Answer

### Q1: "What are the common root causes of PCIe Advanced Error Reporting (AER) errors like 'Uncorrectable (Fatal)' or 'Correctable' errors?"
**Answer:**
"PCIe AER errors are categorized into:
1. **Correctable Errors**: These are handled automatically by the PCIe hardware layer (via LCRC checksums and packet retransmission). High rates of correctable errors indicate marginal signal integrity (e.g., poor board routing, bad PCIe riser card connection, or electromagnetic interference (EMI) from neighboring high-power rails).
2. **Uncorrectable Errors (Fatal)**: These cause the link to drop immediately. They are typically caused by:
   - **Receiver Overflow**: The physical receiver's internal buffer overflowed because Flow Control (FC) credits were not returned or tracked correctly.
   - **Malformed TLP (Transaction Layer Packet)**: The driver wrote an invalid configuration to the MMIO BAR space, causing the hardware to receive a packet with invalid routing, size, or alignment.
   - **Completer Abort (CA)**: The software attempted to access a non-existent or disabled physical address on the device."

### Q2: "How would you handle a driver crash that only occurs in a multi-threaded CPU application utilizing CUDA?"
**Answer:**
"Multi-threaded CUDA app crashes usually point to context management bugs or synchronization races:
1. **Context Migration**: The driver requires a CUDA context to be active on a thread before launching a kernel. If Thread A creates the context and Thread B launches a kernel on it without calling `cudaCtxSetCurrent()`, the kernel launch fails or executes in the wrong context.
2. **Device Pointers Lifetime**: A race condition where Thread A frees a GPU buffer (`cudaFree`) while Thread B is executing a kernel that references that same pointer, causing a GPU page fault (XID 31).
3. **Debugging Strategy**: I would run the application under `compute-sanitizer --tool threadcheck` to detect lock-step synchronization errors and CPU/GPU memory access races."
