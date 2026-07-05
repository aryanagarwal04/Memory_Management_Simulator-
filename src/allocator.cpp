#include "allocator.h"
#include <algorithm>

// -------------------- Initialization --------------------

void Allocator::init_memory(size_t size) {
    blocks.clear();
    next_block_id = 1;
    total_memory = size;

    requested_size.clear();
    stats = Stats{};
    stats.total_memory = size;

    blocks.emplace_back(0, size, true, -1);
}

// -------------------- Strategy --------------------

void Allocator::set_strategy(AllocatorStrategy s) {
    strategy = s;
}

// -------------------- Block Selection --------------------

std::list<MemoryBlock>::iterator Allocator::find_block(size_t size) {
    auto best = blocks.end();

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free || it->size < size) continue;

        if (strategy == AllocatorStrategy::FIRST_FIT)
            return it;

        if (best == blocks.end())
            best = it;
        else if (strategy == AllocatorStrategy::BEST_FIT &&
                 it->size < best->size)
            best = it;
        else if (strategy == AllocatorStrategy::WORST_FIT &&
                 it->size > best->size)
            best = it;
    }
    return best;
}

// -------------------- Allocation --------------------

int Allocator::malloc(size_t size) {
    auto it = find_block(size);
    if (it == blocks.end()) {
        stats.alloc_failure++;
        return -1;
    }

    int id = next_block_id++;
    stats.alloc_success++;
    requested_size[id] = size;

    if (it->size == size) {
        it->free = false;
        it->block_id = id;
        return id;
    }

    MemoryBlock used(it->start, size, false, id);
    MemoryBlock remaining(it->start + size,
                          it->size - size,
                          true, -1);

    it = blocks.erase(it);
    blocks.insert(it, used);
    blocks.insert(it, remaining);

    return id;
}

// -------------------- Free + Coalescing --------------------

bool Allocator::free_block(int block_id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (!it->free && it->block_id == block_id) {

            requested_size.erase(block_id);

            it->free = true;
            it->block_id = -1;

            auto next = std::next(it);
            if (next != blocks.end() && next->free) {
                it->size += next->size;
                blocks.erase(next);
            }

            if (it != blocks.begin()) {
                auto prev = std::prev(it);
                if (prev->free) {
                    prev->size += it->size;
                    blocks.erase(it);
                }
            }
            return true;
        }
    }
    return false;
}

// -------------------- Accessors --------------------

const std::list<MemoryBlock>& Allocator::get_blocks() const {
    return blocks;
}

// -------------------- Stats Computation --------------------

static void compute_stats(const std::list<MemoryBlock>& blocks,
                          const std::unordered_map<int, size_t>& req,
                          Stats& s) {
    s.used_memory = 0;
    s.internal_fragmentation = 0;   // ✅ IMPORTANT FIX

    size_t largest_free = 0;

    for (const auto& b : blocks) {
        if (b.free) {
            largest_free = std::max(largest_free, b.size);
        } else {
            s.used_memory += b.size;
            auto it = req.find(b.block_id);
            if (it != req.end()) {
                s.internal_fragmentation += (b.size - it->second);
            }
        }
    }

    s.free_memory = s.total_memory - s.used_memory;

    if (s.total_memory > 0) {
        s.external_fragmentation =
            double(s.free_memory - largest_free) / double(s.total_memory);
    }
}

// -------------------- Public Stats API --------------------

const Stats& Allocator::get_stats() const {
    compute_stats(blocks, requested_size, stats);
    return stats;
}
