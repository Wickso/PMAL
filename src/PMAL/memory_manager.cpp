#include "memory_manager.h"
#include "defines.h"

#include <cstdlib>
#include <iostream>
#include <assert.h>


pmal::MemoryManager::MemoryManager(MemoryManagerInfo *ptrMemoryManagerInfo) {
    assert(ptrMemoryManagerInfo->sizeBytes > 0);
    m_ptrManagedMemory = std::malloc(ptrMemoryManagerInfo->sizeBytes);
    if (m_ptrManagedMemory == nullptr) {
        std::cout << "Failed to initialize managed memory.\n";
        ptrMemoryManagerInfo->success = false;
    }
    ptrMemoryManagerInfo->success = true;

    if (ptrMemoryManagerInfo->enableStatistics) {
        m_statisticsEnabled = true;
    }
    if (ptrMemoryManagerInfo->resizeAllowed) {
        m_resizeAllowed = true;
    }
    if (!ptrMemoryManagerInfo->allignData) {
        m_allignData = false;
    }
}


pmal::MemoryManager::~MemoryManager() {
    std::free(m_ptrManagedMemory);
}

// Will leave this here for now, don't believe I will need it as the vector of blocks should be
// sorted intrinsiclly if the blocks are added and removed in the order of creation and deletion.
// Testing will show if it is needed.
/**
 * @brief
 * Sorts the representation, a vector, of blocks from MemoryManager.
 *
 * Does not physically sort the blocks of memory that an allocator uses, defragmentBlocks is used
 * for that. This function sorts blocks based of the index member in ascending order to
 * ensure that when availabe space is queried, the vector that holds the blocks can walk the
 * data structure which will allow for faster query (search) times. This function will most likely
 * not be used often.
 */
void pmal::MemoryManager::sortBlocks() {
    // NOTE: May not be needed
}


pmal::Block *pmal::MemoryManager::queryAvailableMemory() {
    // TODO: finish this function
}
