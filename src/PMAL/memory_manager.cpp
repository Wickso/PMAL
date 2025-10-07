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
    m_managedMemorySize           = ptrMemoryManagerInfo->sizeBytes;

    if (ptrMemoryManagerInfo->enableStatistics) {
        m_statisticsEnabled = true;
    }
    if (ptrMemoryManagerInfo->resizeAllowed) {
        m_resizeAllowed = true;
    }
}


pmal::MemoryManager::~MemoryManager() {
    std::free(m_ptrManagedMemory);
}


bool pmal::MemoryManager::resizeMemory(size sizeBytes) {
    // TODO: do this function

    // NOTE: Need to sus whether memcopy or memmove is the correct approach
}


bool pmal::MemoryManager::queryAvailableMemory(size sizeBytes, Block *ptrBlock) {
    assert(ptrBlock != nullptr);
    assert(sizeBytes > 0);

    // NOTE: The -2 in the algorithm when comparing sizes is to exclude the 'cell' that the start
    // and end of the already allocated blocks inhabit. This gives just the amount of bytes between
    // them.

    // helper lambda function. Takes a ptr to where the block will be in indexed in physical mem
    auto populate = [&](void *ptr) {
        ptrBlock->sizeBytes    = sizeBytes;
        ptrBlock->ptrHeapBlock = ptr;
        ptrBlock->blockIndex   = (size *)ptr - (size *)m_ptrManagedMemory;
        std::cout << "Debug: blockIndex = " << ptrBlock->blockIndex << "\n";
        ptrBlock->endOfBlock = (*ptrBlock).blockIndex + sizeBytes;
    };

    // helper lambda to get the ptr to block where it will be in physical mem
    auto getHeapBlockPtr = [&](Block* ptrPrevBlock) {
        // +1 brings it outside of the last block.
        index blockIndex = ptrPrevBlock->endOfBlock + 1;
        void* ptrHeapBlock = (void*)((u8*)m_ptrManagedMemory + blockIndex);
        return ptrHeapBlock;
    };

    // Query for available size of bytes. First fit algorithm

    // if no blocks, then allocate at start: edge case
    if (m_blocks.empty() && ptrBlock->sizeBytes < m_managedMemorySize) {
        populate(m_ptrManagedMemory);
        m_blocks.push_front(ptrBlock);
        return true;
    }
    // walk m_blocks container, compare byte gap between elements and insert
    // where byte gap > sizeBytes

    auto left  = m_blocks.begin();
    auto right = std::next(left, 1);
    while (left != m_blocks.end()) {

        // 'left' at last element: edge case
        if (right == m_blocks.end()) {
            if ((m_managedMemorySize - (*left)->endOfBlock) - 2 > (*left)->sizeBytes) {
                populate(getHeapBlockPtr(*left));
                m_blocks.insert_after(left, ptrBlock);
            } else if(m_resizeAllowed) {
                if (!resizeMemory(size(m_managedMemorySize*m_resizeFactor))) {
                    return false;
                }
                continue; // restart without incrementing iterators.
            }
            else {
                return false;
            }
            return true;
        }

        // check for free space in middle of container.
        if (((*right)->blockIndex - (*left)->endOfBlock) - 2 > ptrBlock->sizeBytes) {
            populate(getHeapBlockPtr(*left));
            m_blocks.insert_after(left, ptrBlock);
            return true;
        }
        std::advance(left, 1);
        std::advance(right, 1);
    }
    return false;
}
