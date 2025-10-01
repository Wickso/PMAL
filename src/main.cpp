#include "defines.h"
#include "memory_manager.h"
#include <iostream>

int main() {
    std::cout << "Hello pmal!\n";

    pmal::MemoryManagerInfo mmInfo;
    mmInfo.sizeBytes = 1024;

    pmal::MemoryManager* mm = new pmal::MemoryManager(&mmInfo);
    std::cout << mmInfo.success << std::endl;

}
