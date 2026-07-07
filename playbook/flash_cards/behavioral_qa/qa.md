# QA & Verification (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Debug an intermittent GPU TDR / kernel panic across the HW-SW stack</b></summary>

Topic: Hardware-Software Integration Debugging
Key concepts:
- Isolate by layer: user space (PyTorch/TensorRT app) → user-mode driver (`libcuda.so`) → OS kernel boundary → kernel-mode driver (`nvidia.ko`, MMIO/DMA, MSI-X) → GPU firmware/silicon. Walk the stack top-down to find where it breaks.
- OS TDR watchdog fires when a GPU task exceeds its time slice; PCIe AER status flags and XID telemetry in `dmesg`/driver logs pinpoint link errors, invalid memory access, or ECC faults at the hardware layer.
- Methodology: reproduce, capture a timeline profile (Nsight Systems), bisect via known-good kernels/builds, read the register/waveform trace the silicon sees — first-principles, not guessing.
File: [qa_debug_hardware_software_integration.md](../../qa_debug_hardware_software_integration.md)
</details>

<details><summary><b>Isolate whether a pipeline is CPU-bound or GPU-bound</b></summary>

Topic: CPU vs. GPU Bottleneck Isolation
Key concepts:
- Hierarchy to know: host CPU → PCIe Gen5 x16 (~63 GB/s) → L2 cache (~30-60 cycles) → HBM3/GDDR6 (~2-3 TB/s, ~300 ns). Compute intimacy means knowing where data and execution contexts transition.
- CPU-bound signs: kernel launch overhead, host-side preprocessing, thread sync stalls, low GPU occupancy. GPU-bound signs: low SM occupancy, memory-bandwidth saturation, warp stalls. Use Nsight Systems (timeline) + Nsight Compute (per-kernel).
- NVML API exposes GPU utilization, memory usage, power, ECC errors; correlate with CPU profiling to attribute the 10 ms SLA miss to the right side and optimize accordingly.
File: [qa_cpu_gpu_bottleneck_isolation.md](../../qa_cpu_gpu_bottleneck_isolation.md)
</details>

<details><summary><b>Automate GPU test environment control (devices, isolation, leak checks)</b></summary>

Topic: Test Environment Automation
Key concepts:
- Verify `/dev/nvidia0`, `/dev/nvidiacctrl`, `/dev/nvidia-uvm` character device nodes exist with correct read/write permissions for the test user; these are the kernel module (`nvidia.ko`, `nvidia-uvm.ko`) control surfaces.
- Isolate execution to a target GPU via env variables (`CUDA_VISIBLE_DEVICES`) and confirm container-level cgroup device constraints actually limit visibility; enforce strict timeouts on the workload.
- After completion, sweep for orphan processes holding GPU contexts and detect memory leaks (VRAM not released) — clean them up so the next run starts from a known-clean state.
File: [qa_automate_test_environment.md](../../qa_automate_test_environment.md)
</details>

<details><summary><b>ASIC verification: SystemVerilog deep vs. shallow copy, UVM, waveforms</b></summary>

Topic: Hardware Verification (Vietnam DV loop)
Key concepts:
- Shallow copy duplicates only class properties; nested object handles are shared between original and copy. Deep copy recursively allocates new nested instances — required for UVM factory-compliant transactions so two sequence items don't alias.
- UVM testbench architecture: sequencer → driver → DUT, plus monitor → scoreboard, with coverage and assertions. The scoreboard compares DUT outputs against a reference model every transaction.
- Debug via waveform trace (VCD/FSDM in Verdi): inspect signal transitions cycle-by-cycle to find where RTL behavior diverges from the spec.
File: [qa_vietnam_hardware_verification.md](../../qa_vietnam_hardware_verification.md)
</details>

---

[Flashcard Index](../README.md)
