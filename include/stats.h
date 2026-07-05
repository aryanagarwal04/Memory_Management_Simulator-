#ifndef STATS_H
#define STATS_H

#include <cstddef>

struct Stats {
    size_t total_memory = 0;
    size_t used_memory = 0;
    size_t free_memory = 0;

    size_t alloc_success = 0;
    size_t alloc_failure = 0;

    size_t internal_fragmentation = 0;
    double external_fragmentation = 0.0;
};

#endif
