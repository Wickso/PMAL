#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "defines.h"
#include <vector>

namespace PMAL {

/**
 * @class MemoryManager
 * @brief
 * MemoryManager is a backend to the allocators.
 *
 * MemoryManager must be instantiated before allocators can be created and used. The purpose of
 * MemoryManager is to manage the memory requested by the user through the operation of
 * its allocators or user-defined allocators.
 *
 * Composed of user memory (what is interacted with directly) and registry memory (holds metadata
 * (e.g. allocators, statistics if enabled)).
 *
 * @param [ManagerSpec] ptrManagerSpec
 * A struct specifying base information and options for MemoryManager.
 */
class MemoryManager {
  public:
    MemoryManager(ManagerSpec *ptrManagerSpec);
    ~MemoryManager();

    template <typename ALLOCATOR_T> ALLOCATOR_T *allocator(size sizeBytes);

    bool resizeMemory(size sizeBytes);


  private:
    Block *queryAvailableMemory();
    bool defragmentBlocks();
    void sortBlocks();

    void *m_ptrManagedMemory  = nullptr;
    void *m_ptrRegistryMemory = nullptr;
    void *m_ptrUserMemory     = nullptr;

    bool m_statisticsEnabled = false;
    bool m_resizeAllowed     = false;
    bool m_registryAllocate  = true; // if sizeBytesRegistry in ManagerSpec is zero then metadata is
                                     // allocated randomly in heap as no registry space exists

    std::vector<Block> m_blocks = {};
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
 * removed from the MemoryManager as to nullify any chances of use after free errors.
 *
 * @param [size] sizeBytes:
 * The size in bytes of memory requested.
 *
 * @return A pointer to type of allocator requested by the user.
 */
template <typename ALLOCATOR_T> ALLOCATOR_T *PMAL::MemoryManager::allocator(size sizeBytes) {
}

} // namespace PMAL

#endif
