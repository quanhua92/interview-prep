# Vietnam Interview Focus: Hardware Verification (UVM & SystemVerilog)

- **Category**: QA & Testing (ASIC Verification)
- **Difficulty**: Hard
- **Target Role**: ASIC Verification Engineer / Design Verification (DV) Developer
- **Source**: Voz, Glassdoor (Vietnam Loop), Hardware Verification Experience

---

## Overview: NVIDIA Vietnam DV Hiring Context
NVIDIA’s engineering site in Ho Chi Minh City, Vietnam, focuses heavily on advanced ASIC/SoC Design and Verification. The interview loop for verification engineers tests deep command of **SystemVerilog**, **UVM (Universal Verification Methodology)**, and physical/architectural logic analysis (ASIC fundamentals).

This document outlines three key technical challenges frequently asked in NVIDIA Vietnam verification interview loops.

---

## Scenario 1: SystemVerilog OOP - Deep vs. Shallow Copy & UVM-Compliant Copying

### Question
> *"What is the difference between a shallow copy and a deep copy in SystemVerilog? Implement a UVM factory-compliant transaction class that implements a true deep copy. Explain why this difference is critical when designing transactional testbenches."*

### Concept Explainers
*   **Shallow Copy**: Creates a new object copy but only duplicates the class properties. If the class contains handles (pointers) to other objects, only the *handles* are copied. Consequently, both the original and copied objects point to the same nested object instance.
*   **Deep Copy**: Creates a copy of the class properties AND recursively allocates new instances of all nested objects, copying their values.

```
Shallow Copy:
[Original Packet] ──> [Payload Data]
  │
  └─> [Header Handle] ───┐
                         ▼
p2 = new p1;      [Shared Header Object]
                         ▲
[Copied Packet p2] ──────┘

Deep Copy:
[Original Packet] ──> [Payload Data]
  │
  └─> [Header Handle] ──> [Header Object A]

[Copied Packet p3] ──> [Payload Data]
  │
  └─> [Header Handle] ──> [Header Object B (Newly Allocated)]
```

### Production UVM Implementation
In production UVM, rather than creating custom copying methods, we override the virtual `do_copy()` method inherited from `uvm_object`. This ensures the transaction works seamlessly with UVM's `copy()` API and respects factory overrides.

```systemverilog
import uvm_pkg::*;
`include "uvm_macros.svh"

// 1. Nested Header Class
class header_item extends uvm_object;
    rand bit [7:0] src_id;
    rand bit [7:0] dest_id;

    `uvm_object_utils_begin(header_item)
        `uvm_field_int(src_id, UVM_DEFAULT)
        `uvm_field_int(dest_id, UVM_DEFAULT)
    `uvm_object_utils_end

    function new(string name = "header_item");
        super.new(name);
    endfunction
endclass

// 2. Main Packet Class
class packet_item extends uvm_sequence_item;
    rand bit [31:0] payload;
    header_item hdr; // Nested object handle

    `uvm_object_utils_begin(packet_item)
        `uvm_field_int(payload, UVM_DEFAULT)
        `uvm_field_object(hdr, UVM_DEFAULT)
    `uvm_object_utils_end

    function new(string name = "packet_item");
        super.new(name);
        hdr = header_item::type_id::create("hdr");
    endfunction

    // Standard UVM-compliant Deep Copy Implementation
    virtual function void do_copy(uvm_object rhs);
        packet_item rhs_cast;
        if (rhs == null) begin
            `uvm_fatal("DO_COPY", "Received null source object")
            return;
        end
        
        // Safely cast generic uvm_object base pointer to packet_item
        if (!$cast(rhs_cast, rhs)) begin
            `uvm_error("DO_COPY", "Failed type casting in do_copy()")
            return;
        end
        
        super.do_copy(rhs); // Copy base class properties (e.g. metadata, labels)
        
        // Deep copy properties
        this.payload = rhs_cast.payload;
        
        // Deep copy nested object
        if (rhs_cast.hdr != null) begin
            if (this.hdr == null) begin
                this.hdr = header_item::type_id::create("hdr");
            end
            this.hdr.copy(rhs_cast.hdr); // Recursive deep copy of header
        end else begin
            this.hdr = null;
        end
    endfunction
endclass
```

### DV Architectural Impact
In a asynchronous UVM testbench:
* The **Sequencer** generates sequences, the **Driver** consumes them, and the **Monitor** observes pin activity.
* If the generator passes a transaction pointer down the pipeline without deep-copying it, the driver might modify the transaction data (e.g. adding handshake delay parameters or injecting errors) while the **Scoreboard** or **Coverage Collector** is processing the same object reference. This introduces silent, highly elusive testbench race conditions.

---

## Scenario 2: Verification Plan & UVM Testbench Architecture

### Question
> *"Design a verification plan and sketch the UVM architecture to verify a 4-channel input FIFO that uses Strict Priority Arbitration to output data on a single channel."*

### 1. Verification Plan
*   **Features to Verify**:
    *   Strict priority arbitration logic (Channel 0 > Channel 1 > Channel 2 > Channel 3).
    *   FIFO overflow and underflow conditions under back-to-back write cycles.
    *   Concurrent writes across multiple channels.
    *   Reset behavior (data clearance, pointer resets).
*   **Assertions (SVA)**:
    *   Assert that `ready` goes low within 1 cycle of FIFO full.
    *   Assert that data read matches FIFO ordering (FIFO properties).
*   **Functional Coverage Matrix**:
    *   Cross coverage of write activity across channels: `channel_0_active X channel_1_active X channel_2_active X channel_3_active`.
    *   Starvation checks: Channel 3 queue fills while Channel 0 is continuously executing.

### 2. UVM Testbench Architecture

```
                       ┌───────────────────────────────────────┐
                       │               UVM Test                │
                       └───────────────────┬───────────────────┘
                                           │
                       ┌───────────────────▼───────────────────┐
                       │               UVM Env                 │
                       └───────────┬───────────────┬───────────┘
                                   │               │
         ┌─────────────────────────┼───────────────┼─────────────────────────┐
         │                         │               │                         │
┌────────▼────────────┐ ┌──────────▼────────┐ ┌────▼───────┐ ┌───────────────▼────┐
│  4x Input Agents    │ │   Output Agent    │ │ Scoreboard │ │ Coverage Collector │
│  (Active)           │ │   (Passive)       │ └────────────┘ └────────────────────┘
└────────┬────────────┘ └──────────┬────────┘       ▲                  ▲
         │ (Virtual VIF)           │ (VIF)          │ TLM Port         │ TLM Port
         v                         v                ├──────────────────┘
┌───────────────────────────────────────────┐       │
│           Design Under Test (DUT)         ├───────┘
│                 (4-Ch FIFO)               │
└───────────────────────────────────────────┘
```

### 3. Component Verification Flow
*   **Virtual Sequencer**: Coordinates the generation of concurrent stimulus on all 4 channel sequencer instances.
*   **TLM Analysis Connections**: The input monitors and output monitor broadcast transactions using non-blocking `uvm_analysis_port`. The scoreboard receives these via `uvm_tlm_analysis_fifo` to prevent thread blocking during checking.
*   **Scoreboard Checker Logic**:
    *   Maintains 4 internal golden queue models (`std::deque`).
    *   On input observation, pushes transactions to the target channel queue.
    *   On output detection, evaluates the priority queue state: if Queue 0 is not empty, the output packet *must* match the front of Queue 0. If Queue 0 is empty but Queue 1 is active, it expects Queue 1's packet.

### 4. SystemVerilog Assertion (SVA) Example
This assertion ensures that if the FIFO is full (`fifo_full == 1`), the FIFO immediately drops its `ready` signal in the next cycle, and no further data writes are accepted.

```systemverilog
property p_fifo_full_ready_drop;
    @(posedge clk) disable iff (!rst_n)
    (fifo_full && wr_en) |=> (!wr_ready);
endproperty

assert_fifo_full_ready_drop: assert property (p_fifo_full_ready_drop)
    else `uvm_error("SVA_ALERT", "FIFO ready did not drop after full condition!")
```

---

## Scenario 3: Debugging UVM Simulation Failures

### Question
> *"During regression runs, a test fails due to a scoreboard mismatch: the data packet received on the output bus does not match the packet sent to Channel 2. How do you systematically debug this simulation mismatch?"*

### Debugging Flowchart

```
                          ┌─────────────────────────────┐
                          │ Scoreboard Mismatch Flagged │
                          └──────────────┬──────────────┘
                                         │
                 ┌───────────────────────┴───────────────────────┐
                 ▼                                               ▼
     [Testbench Driver Audit]                         [Silicon/RTL Signal Trace]
  Did driver violate protocol?                     Trace signals via Verdi waveform
  Check setup/hold times in VIF.                   at timestamp of mismatch.
                 │                                               │
        ┌────────┴────────┐                             ┌────────┴────────┐
        ▼                 ▼                             ▼                 ▼
  [TB Driver Bug]   [Clock Skew]                 [Internal Bug]     [FIFO Underflow]
  Fix pin toggling  Fix interface clocking       FIFO pointers      Arbiter read timing
  code constraints.                              corrupted in RTL.  failed to track state.
```

### Detailed Debug Steps

1. **Objection Trace Check**:
   If the simulation hangs or terminates prematurely before data reaches the scoreboard, trace UVM objections:
   ```bash
   +UVM_OBJECTION_TRACE
   ```
   This identifies which component (e.g. driver, sequence) raised an objection but failed to drop it, preventing the UVM `run_phase` from finishing.
2. **Replicate and Generate Waveform**:
   Rerun the failed test utilizing the identical random seed and dump the waveform database:
   ```bash
   # In VCS:
   ./simv +UVM_TESTNAME=fifo_priority_test +ntb_random_seed=12345 +fsdb+autoflush
   ```
3. **Trace Driver Pin Activity (Interface Audit)**:
   In Verdi, isolate the target channel's interface. Verify that the testbench driver held the data valid (`valid == 1`) long enough to satisfy setup requirements, and that `data` did not transition on the active clock edge. If the driver updated values before the clock edge, it is a **Testbench Phase/Clocking Bug**.
4. **Trace RTL Pointers and Write Logic**:
   If the driver signals are verified clean, trace the internal RAM write/read pointers:
   * Is the write pointer incrementing correctly during write access?
   * Check for **Clock Domain Crossing (CDC)** latency between write clock (`wr_clk`) and read clock (`rd_clk`). Ensure synchronizers are not causing cycle slippage.
5. **Trace Arbiter State Machine**:
   If the data inside the FIFO RAM is correct, inspect the arbiter control logic. Did the state machine select Channel 2 but fetch from the Channel 3 memory address? This is an **RTL Design Bug**.

---

## Pro-Tip: How to Impress the Interviewer

> [!IMPORTANT]
> **Emphasize Phase Sync and SystemVerilog Interfaces**
> When discussing SystemVerilog interfaces, always state that you use **Clocking Blocks** (`clocking ... endclocking`) within the virtual interface definitions. Emphasize that clocking blocks ensure the testbench driver drives inputs with a non-zero output skew and samples outputs with a non-zero input skew. This completely prevents race conditions between the simulator's Active and Re-Active regions, showing you write robust, simulator-independent code.

---

## Common Follow-Up Questions & How to Answer

### Q1: "What is the difference between `copy()` and `clone()` in UVM?"
**Answer:**
* `copy()` is a non-virtual void method that copies the contents of another object into the existing calling object. The calling object must already be allocated: `dest_obj.copy(src_obj);`.
* `clone()` is a virtual method that creates a new object using the UVM factory, calls `copy()` internally to copy the contents, and returns a `uvm_object` pointer. It handles allocation and copying in a single call: ``uvm_declare_p_info; $cast(dest_obj, src_obj.clone());`.

### Q2: "How do you handle clock-domain crossing (CDC) validation in your verification environment?"
**Answer:**
"We validate CDC using a combination of static analysis and dynamic simulation:
1. **Static Analysis**: Run CDC checks (e.g. using Synopsys VC CDC) to identify missing synchronizers, potential data coherency issues, and reconvergence loops.
2. **Dynamic Simulation**: We use specialized CDC simulation models that dynamically inject random delays or jitter on the destination clock domain boundaries to mimic metastability. Scoreboards must be robust enough to handle the resulting $\pm 1$ clock cycle latency variations."

### Q3: "What is the difference between a virtual sequencer and a standard sequencer?"
**Answer:**
"A virtual sequencer does not drive physical interfaces itself and does not have its own driver. Instead, it contains handles to the actual sub-sequencers (e.g. our 4 input sequencers). 

We run a **Virtual Sequence** on the virtual sequencer. The virtual sequence coordinates the execution of sub-sequences on the target sub-sequencers, allowing us to orchestrate complex scenarios like triggering back-to-back writes on Channel 0 and Channel 3 simultaneously, ensuring synchronized stimulus across multiple ports."
