#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "defines.h"
#include <forward_list>

namespace pmal {

/**
 * @class MemoryManager
 * @brief
 * MemoryManager is a backend to the allocators.
 *
 * MemoryManager must be instantiated before allocators can be created and used. The purpose of
 * MemoryManager is to manage the memory requested by the user through the operation of
 * its allocators or user-defined allocators: constrained to ten allocators per MemoryManager
 * object. If more are needed then simply create another MemoryManager.
 *
 * Composed of user memory (what is interacted with directly) and registry memory (holds metadata
 * (e.g. allocators, statistics if enabled)).
 *
 * Note: Blocks will be 4-byte aligned, meaning the user may not be able to use 100% of the memory
 * requested. Either change the resize factor to something smaller for minute changes or disable
 * alligning, both options in MemoryManagerInfo.
 *
 * @param [MemoryManagerInfo] ptrMemoryManagerInfo
 * A struct specifying base information and options for MemoryManager.
 */
class MemoryManager {
  public:
    MemoryManager(MemoryManagerInfo *ptrMemoryManagerInfo);
    ~MemoryManager();

    template <typename ALLOCATOR_T> ALLOCATOR_T *newAllocator(size sizeBytes);

    bool resizeMemory(size sizeBytes);


  private:
    bool queryAvailableMemory(size sizeBytes, Block* blockPopulate);
    bool defragmentBlocks();
    void sortBlocks();

    void *m_ptrManagedMemory = nullptr;
    size m_managedMemorySize = 0;

    bool m_statisticsEnabled = false;
    bool m_resizeAllowed     = false;
    //bool m_registryAllocate  = true; // if false then metadata is allocated randomly in heap
    float m_resizeFactor     = 1.1f;


    std::forward_list<Block*> m_blocks = {};
};


/**
 *
 * @brief
 * Internal allocator for user allocators when one is requested.
 *
 * The user requests an allocator via this template with a specified size in bytes as the scope of
 * this allocator to work within. Allocators hold a reference to the MemoryManager object that
 * created it and vice versa. This means that the MemoryManager can free the allocator if
 * MemoryManager itself is freed and if the allocator is no longer needed then its reference is
 * removed from the MemoryManager as to nullify any chances of use after free errors. Allocation is
 * through the heap so instantiation is not recomended in loops.
 *
 * @param [size] sizeBytes:
 * The size in bytes of memory requested.
 *
 * @return A pointer to type of allocator requested by the user.
 */
template <typename ALLOCATOR_T> ALLOCATOR_T *pmal::MemoryManager::newAllocator(size sizeBytes) {
}

} // namespace pmal

#endif
