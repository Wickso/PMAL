#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "defines.h"

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
 * @param [size] sizeBytes
 * Takes a size in bytes to allocate for user memory.
 * @param [size] sizeBytesRegistry (default value 1MiB)
 * Take a size in bytes to allocate for registry memory.
 */
class MemoryManager {
  public:
    MemoryManager(size sizeBytes, size sizeBytesRegistry = 1024 * 1024);
    ~MemoryManager();

    template <typename ALLOCATOR_T> ALLOCATOR_T *allocator(size sizeBytes);

    bool requestMemory(size sizeBytes);


  private:
    void *m_managedMemory = nullptr;
};


/**
 *
 * @brief
 * Internal allocator for user allocators when one is requested.
 *
 * The user requests an allocator via this template with a specified size in bytes as the scope of
 * this allocator to work within.
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
