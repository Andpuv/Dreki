# Dreki

**Dreki** is a fantasy computer designed around a 32-bit architecture with a configurable, extensible instruction set and robust memory management capabilities. It is intended for research, educational purposes, or exploration of CPU and I/O processor design principles. The following document outlines the technical specifications of the Dreki computer.

---

## Overview

Dreki is a 32-bit RISC-based computer that includes:
- A 32-bit physical address space capable of addressing up to 4 GiB.
- An extendable 32-bit RISC instruction set, with support for future expansions up to 128 bits.
- Support for up to four privilege levels: hardware, firmware, software, and user ground.
- Advanced memory architecture with two parallel RAM banks and configurable memory models.
- Optional connections for up to two I/O processors for extended processing and data transfer capabilities.

---

## CPU Specifications

- **Architecture**: 32-bit RISC, with potential extension to a 128-bit instruction set for future upgrades.
- **Instruction Set**: Fixed-length 32-bit instructions with extensible op codes.
- **Privilege Levels**: Four privilege levels:
  - Hardware
  - Firmware
  - Software
  - User Ground
- **Interrupts**: Supports up to 32 external interrupt sources.
- **Parallel RAM Banks**: Capable of fetching up to two words at a time from dual RAM banks.
  
### Memory Models
Dreki provides two memory models:
1. **Linear**: Continuous memory addressing.
2. **Paged**: 4 KiB pages with a 64-entry Translation Lookaside Buffer (TLB).

### Caching and Write Operations
- **Instruction Cache**:
  - Two 4-way set-associative instruction caches.
  - Each cache has 1024 sets and 4-byte blocks per way.
- **Data Cache**:
  - One 4-way set-associative data cache.
  - Cache size and structure similar to the instruction cache.
- **Write Buffer**: Read operations have priority, so write operations are stored in a buffer that holds the data and empties only when requested.
- **Memory Coherence**: Requires forced `FENCE` operations to maintain coherence, particularly if interacting with co-processors or I/O devices.

### Pipeline
The CPU operates on a simple, four-stage pipeline:
1. **Fetch**: Retrieve the instruction from memory.
2. **Decode**: Interpret the instruction and prepare for execution.
3. **Execute**: Perform the instruction operation.
4. **Write-Back**: Store the result in the destination register.

This linear pipeline can be adapted for out-of-order execution in future versions to improve performance.

---

## Central Memory

- **Type**: RAM (assumes no physical latency for educational purposes).
- **Immediate Response**: Memory immediately responds to requests without latency simulation.
  - Note: In real-world scenarios, DRAM latency could affect access times, especially during refresh cycles.
- **Banked Configuration**: Memory is divided into banks (analogous to DIMMs in real hardware).
  - Each bank has a fixed size at runtime, typically in the range of tens of MiB.
  - The CPU can connect to up to two banks at once. With more than two banks present, only two are active at any given time.

---

## I/O Processor (IOP) Interface

Dreki's CPU can connect to up to two I/O processors (IOPs), which act as co-processors dedicated to handling I/O operations, enhancing data transfer efficiency, and offloading tasks from the main CPU.

- **Address Space**: Each I/O processor operates within a 28-bit address space, allowing it to address up to 256 MiB of memory.
- **Data Transfer Optimization**: Since each IOP is limited to a 256 MiB memory space, operating system designs should optimize data transfers within these constraints, especially when managing large data sets.

---

## Future Extensions

Dreki's architecture is designed with extensibility in mind:
- **Instruction Set**: The 32-bit instruction set can expand up to 128 bits, allowing additional op codes for new instructions and features.
- **Pipeline Enhancements**: The simple pipeline structure could be upgraded to an out-of-order execution pipeline for increased performance.

---

## Summary

Dreki is a fantasy computer system combining educational simplicity with extensible features for future development. Its 32-bit RISC instruction set, robust privilege levels, dual RAM banks, memory coherence management, and I/O processor interfaces make it an ideal foundation for exploring CPU and operating system design.

--- 

This project is still in its initial stages, and future versions may include more sophisticated features like enhanced pipelining, new instruction types, and advanced memory management techniques.

---

## Contributing

This project is open to contributions, especially in areas like:
- Extending the instruction set
- Developing the I/O processor interface
- Creating an efficient memory management subsystem
- Enhancing the pipeline for out-of-order execution

These specifications are still open to improvements and changes, so feel free to add/remove what you like.

Feel free to create issues, fork the project, or suggest features to improve **Dreki**.

--- 

## License

This project is licensed under the CC0 License (see LICENSE).

---

*Dreki - A Fantasy 32-Bit Computer Architecture for Educational Exploration and Research.*