#include "memory_manager.h"
#include "defines.h"

#include <assert.h>
#include <cstdlib>
#include <iostream>


pmal::MemoryManager::MemoryManager(MemoryManagerInfo *ptrMemoryManagerInfo) {
    assert(ptrMemoryManagerInfo->sizeBytes > 0);
    m_ptrManagedMemory = std::malloc(ptrMemoryManagerInfo->sizeBytes);
    if (m_ptrManagedMemory == nullptr) {
        std::cout << "Failed to initialize managed memory.\n";
        ptrMemoryManagerInfo->success = false;
    }
    ptrMemoryManagerInfo->success = true;
    m_blocks.reserve(10);

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


bool pmal::MemoryManager::queryAvailableMemory(size sizeBytes, Block *ptrBlock) {
    // TODO: finish this function

    // query MemoryManager and allocate block for the size. If not, resize managed memory if allowed
    // populate the block supplied by the newAllocator function and store a reference to the block
    // in MemoryManager. MemoryManager references the block but the allocator owns it. return
    // true/false for success/fail
   
    // helper lambda function
    auto populate = [&](void* ptr) {
        (*ptrBlock).sizeBytes = sizeBytes;
        (*ptrBlock).ptrHeapBlock = ptr;
        (*ptrBlock).blockIndex = (size*)m_ptrManagedMemory - (size*)ptr;
        (*ptrBlock).endOfBlock = (*ptrBlock).blockIndex + sizeBytes;
    };

    // Query for available size of bytes. First fit algorithm
    if (m_blocks.empty()) {
        populate(m_ptrManagedMemory);
        // TODO: add ptr to singly linked list
    }
    for (int i = 0; i < m_blocks.size(); ++i) {

    }
}
