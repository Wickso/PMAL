#include "memory_manager.h"
#include "defines.h"

#include <cstdlib>
#include <iostream>

PMAL::MemoryManager::MemoryManager(ManagerSpec* ptrManagerSpec) {
    // TODO: Include asserts
    m_ptrManagedMemory = std::malloc(ptrManagerSpec->sizeBytes + ptrManagerSpec->sizeBytesRegistry);
    if (m_ptrRegistryMemory == nullptr) {
        std::cout << "Failed to initialize managed memory.\n";
        ptrManagerSpec->success = false;
    }
    m_ptrRegistryMemory = (void *)((u8 *)m_ptrManagedMemory + 16);
    m_ptrUserMemory     = (void *)((u8 *)m_ptrRegistryMemory + ptrManagerSpec->sizeBytes);
    m_blocks.reserve(8);
    ptrManagerSpec->success = true;

    if (ptrManagerSpec->enableStatistics) {
        m_statisticsEnabled = true;
    }
    if (ptrManagerSpec->resizeAllowed) {
        m_resizeAllowed = true;
    }
    if (ptrManagerSpec->sizeBytesRegistry == 0) {
        m_registryAllocate = false;
    }
}


PMAL::MemoryManager::~MemoryManager() {
    std::free(m_ptrManagedMemory);
}
