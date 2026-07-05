#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <cstddef>

struct MemoryBlock {
    size_t start;     // starting address
    size_t size;      // size of block
    bool free;         // is this block free?
    int block_id;      // -1 if free, otherwise allocation id

    MemoryBlock(size_t start, size_t size, bool free, int block_id);
};

#endif
