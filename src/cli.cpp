#include "cli.h"
#include <iostream>
#include <sstream>
#include "cache.h"

// CLI::CLI(Allocator& allocator) : allocator(allocator) {}

CLI::CLI(Allocator& allocator)
    : allocator(allocator),
      l1(16, 16),   // L1 cache: 16 lines, block size 16 bytes
      l2(32, 16) {} // L2 cache: 32 lines, block size 16 bytes


void CLI::run() {
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        handle_command(line);
    }
}

void CLI::handle_command(const std::string& line) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "init") {
        std::string mem;
        size_t size;
        iss >> mem >> size;
        if (mem == "memory") {
            allocator.init_memory(size);
            std::cout << "Memory initialized: " << size << " bytes\n";
        }
    }
    else if (cmd == "set") {
        std::string what, strategy;
        iss >> what >> strategy;
        if (what == "allocator") {
            if (strategy == "first_fit")
                allocator.set_strategy(AllocatorStrategy::FIRST_FIT);
            else if (strategy == "best_fit")
                allocator.set_strategy(AllocatorStrategy::BEST_FIT);
            else if (strategy == "worst_fit")
                allocator.set_strategy(AllocatorStrategy::WORST_FIT);

            std::cout << "Allocator set to " << strategy << "\n";
        }
    }
    else if (cmd == "malloc") {
        size_t size;
        iss >> size;
        int id = allocator.malloc(size);
        if (id == -1)
            std::cout << "Allocation failed\n";
        else
            std::cout << "Allocated block id=" << id << "\n";
    }
    else if (cmd == "free") {
        int id;
        iss >> id;
        if (allocator.free_block(id))
            std::cout << "Block " << id << " freed and merged\n";
        else
            std::cout << "Invalid block id\n";
    }
    // else if (cmd == "dump") {
    //     std::string what;
    //     iss >> what;
    //     if (what == "memory") {
    //         for (const auto& b : allocator.get_blocks()) {
    //             std::cout << "["
    //                       << b.start << " - "
    //                       << b.start + b.size - 1 << "] "
    //                       << (b.free ? "FREE" : "USED (id=" + std::to_string(b.block_id) + ")")
    //                       << "\n";
    //         }
    //     }
    // }
    else if (cmd == "exit") {
        std::exit(0);
    }
    else if (cmd == "stats") {
        const Stats& s = allocator.get_stats();

        std::cout << "Total memory: " << s.total_memory << "\n";
        std::cout << "Used memory: " << s.used_memory << "\n";
        std::cout << "Free memory: " << s.free_memory << "\n";
        std::cout << "Memory utilization: "
                  << (100.0 * s.used_memory / s.total_memory) << "%\n";
        std::cout << "Internal fragmentation: "
                  << s.internal_fragmentation << "\n";
        std::cout << "External fragmentation: "
                  << (100.0 * s.external_fragmentation) << "%\n";
        std::cout << "Alloc success: " << s.alloc_success << "\n";
        std::cout << "Alloc failure: " << s.alloc_failure << "\n";
    }
    else if (cmd == "access") {
        size_t address;
        iss >> address;

        if (l1.access(address)) {
            std::cout << "L1 hit\n";
        } else if (l2.access(address)) {
            std::cout << "L2 hit\n";
            l1.insert(address);  // bring to L1
        } else {
            std::cout << "Cache miss (memory access)\n";
            l2.insert(address);
            l1.insert(address);
        }
    }
    // else if (cmd == "dump") {
    //     std::string what;
    //     iss >> what;

    //     if (what == "cache") {
    //         std::cout << "L1 hits: " << l1.get_hits()
    //                   << ", misses: " << l1.get_misses() << "\n";
    //         std::cout << "L2 hits: " << l2.get_hits()
    //                   << ", misses: " << l2.get_misses() << "\n";
    //     }
    // }
    else if (cmd == "dump") {
        std::string what;
        iss >> what;

        if (what == "memory") {
            for (const auto& b : allocator.get_blocks()) {
                std::cout << "["
                          << b.start << " - "
                          << b.start + b.size - 1 << "] "
                          << (b.free ? "FREE"
                                     : "USED (id=" + std::to_string(b.block_id) + ")")
                          << "\n";
            }
        }
        else if (what == "cache") {
            std::cout << "L1 hits: " << l1.get_hits()
                      << ", misses: " << l1.get_misses() << "\n";
         std::cout << "L2 hits: " << l2.get_hits()
                      << ", misses: " << l2.get_misses() << "\n";
        }
        else {
        std::cout << "Unknown dump target\n";
        }
    }

    else {
        std::cout << "Unknown command\n";
    }
}
