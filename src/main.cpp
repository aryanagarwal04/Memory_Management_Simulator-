#include <iostream>
#include "allocator.h"
#include "cli.h"

int main() {
    std::cout << "Memory Simulator\n";
    Allocator allocator;
    CLI cli(allocator);
    cli.run();
    return 0;
}
