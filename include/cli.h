#ifndef CLI_H
#define CLI_H
#include <string>
#include "allocator.h"
#include "cache.h"
class CLI {
public:
    CLI(Allocator& allocator);
    void run();

private:
    Allocator& allocator;
    Cache l1{16, 16};
    Cache l2{32, 32};
    void handle_command(const std::string& line);
};

#endif
