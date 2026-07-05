# Memory Management Simulator

A C++ simulator that models dynamic physical memory allocation and a multilevel CPU cache hierarchy.  
The project demonstrates core operating system concepts such as allocation strategies, fragmentation handling, and cache hit/miss behavior through an interactive command-line interface.

---

## Overview

This simulator models:
- A contiguous block of physical memory with dynamic allocation and deallocation
- Multiple memory allocation strategies
- Fragmentation analysis
- A realistic multilevel CPU cache (L1 and L2) using index–tag based lookup

The system is interactive and allows users to experiment with memory allocation patterns and observe cache behavior in real time.

---

## Features

### Physical Memory Simulation
- Contiguous physical memory
- Dynamic block splitting on allocation
- Immediate coalescing of adjacent free blocks on deallocation
- Byte-level addressing

### Allocation Strategies
- First Fit
- Best Fit
- Worst Fit

### Memory Statistics
- Used memory
- Free memory
- Memory utilization
- Internal fragmentation
- External fragmentation
- Allocation success and failure count

### Multilevel Cache Simulation
- L1 and L2 caches
- Direct-mapped cache design
- Address decomposition into block address, index, and tag
- Cache hit and miss tracking per level
- Miss propagation from L1 → L2 → main memory

### Command-Line Interface
The simulator provides an interactive CLI to issue memory and cache commands.

Supported commands:

init memory <size>
set allocator <first_fit | best_fit | worst_fit>
malloc <size>
free <block_id>
dump memory
stats
access <address>
dump cache
exit


---

## Build Instructions

### Windows (PowerShell / VS Code Terminal)
Compile the project using:
g++ -I include src/main.cpp src/cli.cpp src/allocator.cpp src/memory_block.cpp src/cache.cpp -o memsim

Run:
.\memsim

### Linux / macOS
make
./memsim


---

## Project Structure

Memory_Management_Simulator/
├── src/
│   ├── main.cpp            # Program entry point
│   ├── cli.cpp             # Command-line interface and user interaction
│   ├── allocator.cpp       # Memory allocation algorithms and statistics computation
│   ├── memory_block.cpp    # Memory block abstraction and helpers
│   └── cache.cpp           # L1/L2 cache simulation logic
│
├── include/
│   ├── cli.h               # CLI interface definitions
│   ├── allocator.h         # Allocator interface
│   ├── memory_block.h      # Memory block data structure
│   ├── cache.h             # Cache interface and cache line definition
│   └── stats.h             # Statistics data structure (header-only)
│
├── docs/
│   └── design.md           # Design documentation
│
├── tests/
│   └── basic_tests.txt     # Manual test cases with expected behavior
│
├── Makefile                # Build instructions (Unix-based systems)
└── memsim.exe              # Compiled executable (optional, Windows)


---

## Design Notes

- Memory blocks are maintained using a linked list to simplify splitting and coalescing.
- Allocation strategies are modular and easily extendable.
- Cache simulation closely follows real hardware behavior using index and tag comparison.
- Cache replacement for direct-mapped caches is handled implicitly via overwrite.

---

## Limitations

- Virtual memory simulation is not implemented (optional feature).
- Buddy allocation system is not implemented (optional feature).
- Cache timing and latency are not simulated.
- Only direct-mapped caches are supported.

---

## Testing

Test artifacts are provided in the `tests/` directory as scripted CLI command sequences with expected behavior and correctness criteria.  
Cache behavior and memory statistics can also be verified interactively using the CLI.

---
Short demonstration of memory allocation and cache behavior:

https://drive.google.com/file/d/12wqEzdmCo8EH7t5dMiqK4ROXFW5tQ4QI/view?usp=drive_link


## Author
Arnav Garg

