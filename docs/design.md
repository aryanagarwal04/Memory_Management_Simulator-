Design and Implementation of a Memory Management Simulator
1. Introduction

This project implements a memory management simulator that models how an operating system manages physical memory and cache hierarchies. The simulator supports multiple memory allocation strategies, tracks fragmentation metrics, and simulates a multilevel CPU cache. The system is interactive and provides a command-line interface for testing different memory access patterns.

2. Assumptions and Memory Model
2.1 Physical Memory Representation

Physical memory is simulated as a contiguous block of memory.

Memory addresses start from 0 and increase sequentially.

Memory unit: Byte-level granularity.

Memory is internally represented using a linked list of memory blocks.

Each memory block contains:

Start address

Size (in bytes)

Allocation status (free or allocated)

Block ID (for allocated blocks)

This representation allows efficient splitting and coalescing of memory blocks.

3. Memory Allocation Strategies

The simulator implements the following allocation strategies:

3.1 First Fit

Selects the first free block that is large enough to satisfy the request.

Fast allocation, but may cause external fragmentation.

3.2 Best Fit

Selects the smallest free block that can satisfy the request.

Reduces wasted space but requires scanning all free blocks.

3.3 Worst Fit

Selects the largest free block.

Attempts to reduce the creation of small unusable fragments.

3.4 Block Splitting

When a free block is larger than the requested size:

The block is split into:

One allocated block

One remaining free block

3.5 Deallocation and Coalescing

On freeing a block:

Adjacent free blocks (left and right) are merged immediately.

This reduces external fragmentation and keeps memory contiguous.

4. Allocation Interface (CLI)

The simulator provides an interactive command-line interface.

Supported Commands:

init memory <size> – Initialize physical memory

set allocator <first_fit | best_fit | worst_fit> – Select allocation strategy

malloc <size> – Allocate memory

free <block_id> – Free allocated memory

dump memory – Display memory layout

stats – Display memory statistics

access <address> – Simulate cache access

dump cache – Display cache statistics

exit – Terminate simulator

5. Metrics and Statistics

The simulator computes the following metrics:

5.1 Memory Utilization
Memory Utilization
=
Used Memory
Total Memory
Memory Utilization=
Total Memory
Used Memory
	​

5.2 Internal Fragmentation

Calculated as:

∑(Allocated Block Size−Requested Size)

Internal fragmentation is zero because allocations are exact-sized and blocks are split precisely.

Tracked using a map of block IDs to requested sizes.

5.3 External Fragmentation
Total Free Memory
−
Largest Free Block
Total Memory
Total Memory
Total Free Memory−Largest Free Block
	​

5.4 Allocation Success and Failure Rate

Counts successful and failed allocation attempts.

Statistics are computed on demand to ensure accuracy.

6. Multilevel Cache Simulation
6.1 Cache Hierarchy

The simulator implements:

L1 Cache

L2 Cache

Both caches are:

Direct-mapped

Block-based addressing

6.2 Cache Access Flow

    Address Access
    ↓
    L1 Cache
    ↓ (miss)
    L2 Cache
    ↓ (miss)
    Main Memory

6.3 Cache Behavior

On L1 hit: access completes.

On L1 miss & L2 hit: data is promoted to L1.

On L2 miss: data is fetched from memory and inserted into both caches.

6.4 Cache Metrics

Cache hits and misses are tracked per level.

Hit ratios are computed from counters.

7. Design Decisions

Linked list chosen for memory blocks to simplify splitting and coalescing.

Derived statistics are recomputed on demand using mutable metadata.

Cache simulation is kept logically separate from memory allocation logic.

FIFO replacement chosen for simplicity and clarity.

8. Limitations and Simplifications

Virtual memory and paging are not implemented.

Cache timing and latency are not simulated.

Buddy allocation system is not implemented (optional feature).

These choices were made to maintain clarity while meeting all mandatory project requirements.

9. Conclusion

This simulator demonstrates key operating system concepts including dynamic memory allocation, fragmentation management, and cache hierarchy behavior. The modular design allows easy extension for advanced features such as virtual memory or additional cache levels.


On Windows systems, the project can be built using g++ directly. The provided Makefile is intended for Unix-based environments.
