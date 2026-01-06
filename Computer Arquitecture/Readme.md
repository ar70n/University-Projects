# Computer Architecture

This directory contains a collection of academic projects focused on **computer architecture and performance-oriented system design**. Each project explores a key architectural concept through hands-on implementation, analysis, and experimentation, combining theoretical foundations with low-level programming and hardware-aware optimization techniques.

The projects cover **memory hierarchy performance**, **instruction-level and thread-level parallelism**, **segmented (pipelined) microprocessor design**, and **vector/SIMD processing**.

---

## 1. Cache Performance

This project analyzes the impact of the **memory hierarchy** on program execution time, with particular emphasis on **cache behavior** and data locality.

### Core Topics

* Memory hierarchy (cache vs main memory)
* **Cache hits and misses**
* **Spatial and temporal locality**
* Cache line size, associativity, and replacement effects
* Memory access patterns

### Techniques and Methodology

* Empirical evaluation of cache performance using synthetic benchmarks
* Measurement of execution time and memory access cost
* Analysis of loop ordering, stride access, and data layout
* Performance comparison under different cache-sensitive workloads

### Key Concepts

* Cache miss penalty
* Memory-bound vs compute-bound execution
* Data locality optimization
* Performance profiling

This project highlights how algorithmic structure and memory access patterns directly influence cache efficiency and overall system performance.

---

## 2. Parallelism with OpenMP

This project focuses on **shared-memory parallelism** using **OpenMP**, exploiting multi-core architectures to reduce execution time.

### Core Topics

* Thread-level parallelism (TLP)
* Fork-join execution model
* Shared vs private data
* Synchronization overhead

### Techniques and Methodology

* Parallelization of computational kernels using OpenMP pragmas
* Use of `parallel`, `for`, `reduction`, and scheduling clauses
* Performance scalability analysis across multiple threads
* Identification of bottlenecks such as false sharing and load imbalance

### Key Concepts

* Speedup and efficiency
* Amdahl’s Law
* Critical sections and race conditions
* Static vs dynamic scheduling

The project demonstrates how proper workload distribution and synchronization management are essential for achieving scalable performance on multicore processors.

---

## 3. Segmented Microprocessor (Pipelined RISC-V)

This project implements and extends a **segmented (pipelined) RISC-V microprocessor** described in classical computer architecture literature (Harris & Harris, Patterson & Hennessy).

### Core Topics

* Instruction pipelining (IF, ID, EX, MEM, WB)
* **Data hazards and control hazards**
* Pipeline stalls and flushes
* Hazard detection and resolution

### Techniques and Methodology

* VHDL implementation of a pipelined RISC-V processor
* Design of a **Hazard Unit** for:

  * **RAW data hazards**
  * **Load-Use hazards**
* Implementation of **data forwarding paths** (EX/MEM and MEM/WB)
* Insertion of pipeline bubbles (NOPs) via stalling
* Control hazard handling for branch and jump instructions
* Simulation and verification using ModelSim/QuestaSim

### Key Concepts

* Forwarding (bypassing) logic
* Pipeline stall and flush mechanisms
* Branch penalty
* Instruction-level parallelism (ILP)

This project provides a low-level view of how modern processors maintain correctness while maximizing throughput.

---

## 4. Vectorial Processing (SIMD)

This project explores **data-level parallelism** through **vector (SIMD) processing**, focusing on accelerating numeric workloads.

### Core Topics

* SIMD architectures
* Vector registers and vector instructions
* Data parallel computation

### Techniques and Methodology

* Refactoring scalar code into vectorized implementations
* Use of SIMD-style operations to process multiple data elements per instruction
* Comparison of scalar vs vector execution performance
* Analysis of alignment, vector length, and memory access efficiency

### Key Concepts

* Data-Level Parallelism (DLP)
* Vector speedup
* Arithmetic intensity
* Throughput-oriented execution

The project demonstrates how vectorization can significantly improve performance for compute-heavy and data-parallel workloads.

---

## Summary

Together, these projects provide a comprehensive exploration of **performance-oriented computer architecture**, spanning:

* Memory hierarchy optimization
* Multithreaded execution
* Pipeline design and hazard management
* SIMD/vector acceleration

They emphasize the close relationship between **hardware architecture**, **low-level programming**, and **measurable performance outcomes**, offering practical insight into how modern processors are designed and exploited efficiently.

