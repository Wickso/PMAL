#include "memory_manager.h"
#include "defines.h"

#include <cstdlib>
#include <iostream>


PMAL::MemoryManager::MemoryManager(size sizeBytes, size sizeBytesRegistry) {
    m_ptrManagedMemory = std::malloc(sizeBytes + sizeBytesRegistry);
    if (m_ptrRegistryMemory == nullptr) {
        std::cout << "Failed to initialize managed memory.\n";
    }
    m_ptrRegistryMemory = (void *)((u8 *)m_ptrManagedMemory + 16);
    m_ptrUserMemory     = (void *)((u8 *)m_ptrRegistryMemory + sizeBytes);
    m_blocks.reserve(8);
}


PMAL::MemoryManager::~MemoryManager() {
    std::free(m_ptrManagedMemory);
}
