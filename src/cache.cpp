#include "cache.h"

Cache::Cache(size_t num_lines, size_t block_size)
    : num_lines(num_lines), block_size(block_size),
      lines(num_lines) {}

bool Cache::access(size_t address) {
    size_t block_addr = address / block_size;
    size_t index = block_addr % num_lines;
    size_t tag = block_addr / num_lines;

    if (lines[index].valid && lines[index].tag == tag) {
        hits++;
        return true;
    } else {
        misses++;
        return false;
    }
}

void Cache::insert(size_t address) {
    size_t block_addr = address / block_size;
    size_t index = block_addr % num_lines;
    size_t tag = block_addr / num_lines;

    lines[index].valid = true;
    lines[index].tag = tag;
}

size_t Cache::get_hits() const { return hits; }
size_t Cache::get_misses() const { return misses; }
