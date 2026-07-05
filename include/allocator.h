#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <unordered_map>
#include "stats.h"
#include <list>
#include <cstddef>
#include "memory_block.h"

enum class AllocatorStrategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

class Allocator {
public:
    void init_memory(size_t size);

    void set_strategy(AllocatorStrategy s);

    int malloc(size_t size);
    bool free_block(int block_id);

    const std::list<MemoryBlock>& get_blocks() const;
    const Stats& get_stats() const;

private:
    std::list<MemoryBlock> blocks;
    int next_block_id = 1;
    AllocatorStrategy strategy = AllocatorStrategy::FIRST_FIT;

    std::list<MemoryBlock>::iterator find_block(size_t size);
    std::unordered_map<int, size_t> requested_size;
    mutable Stats stats;
    size_t total_memory = 0;

};

#endif
