#include "memory_block.h"

MemoryBlock::MemoryBlock(size_t start, size_t size, bool free, int block_id)
    : start(start), size(size), free(free), block_id(block_id) {}
