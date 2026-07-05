#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstddef>

struct CacheLine {
    bool valid = false;
    size_t tag = 0;
};

class Cache {
public:
    Cache(size_t num_lines, size_t block_size);

    bool access(size_t address);
    void insert(size_t address);

    size_t get_hits() const;
    size_t get_misses() const;

private:
    size_t num_lines;
    size_t block_size;
    std::vector<CacheLine> lines;

    size_t hits = 0;
    size_t misses = 0;
};

#endif
