#ifndef DEFINES_H
#define DEFINES_H

#include <cstdint>

namespace PMAL {

using u8    = std::uint8_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using index = std::uint64_t; // index of memory position. Used internally.
using size  = std::uint64_t; // size: unit in bytes


/**
 * @brief Describes the region of memory requested and provided to an allocator from its memory
 * manager.
 */
typedef struct Block {
    void *ptrBlock   = nullptr;
    index blockIndex = 0;
    index endOfBlock = 0;
    size sizeBytes   = 0;
} Block;


/**
 * @brief Describes the data constructed inside a block.
 */
typedef struct Handle {
    void *ptrToBlock = nullptr;
    index dataIndex  = 0;
    index endOfData  = 0;
    size sizeBytes   = 0;
} Handle;


/**
 * @brief
 * A struct to provide information to MemoryManger on instantiation.
 *
 * Once passed to MemoryManager it is fine for the user to destroy this struct. Usage will no longer
 * be needed. Note the total size of memory on the heap is sizeBytes + sizeBytesRegistry however
 * sizeBytesRegistry can be set to zero and meta data will be allocated to the heap at random which
 * will more than likely incure performance overhead.
 *
 * @param [size] sizeBytes:
 * The size of memory to be allocated and managed on the heap for the user.
 * @param [size] sizeBytesRegistry:
 * The size of registry. Default 1024*1024+16 bytes
 * @param [bool] resizeAllowed:
 * If the memory being managed turns out to not be sufficient this options lets MemoryManager
 * dynamically resize the memory for extra space. Resizes by 20% by default or what is needed to
 * accomodate the data being constructed.
 * @param [float] resizeFactor:
 * Factor to increase memory by if needed/allowed.
 * @param [bool] success:
 * An indicator of the operation of MemoryManager on instantiation (i.e. was the memory successfully
 * allocated). Recommended to be checked before destroying this struct.
 * @param [bool] enableStatisitics:
 * An option if set to true will enable statisitics to be gathered by MemoryManager. Recommended
 * during debug builds. MemoryStatistics object will track each MemoryManagers stats and collate.
 */
typedef struct ManagerSpec {
    size sizeBytes         = 0;
    size sizeBytesRegistry = 1024 * 1024 + 16;
    bool resizeAllowed     = true;
    float resizeFactor     = 0.2f;
    bool success           = false;
    bool enableStatistics  = false;
} ManagerSpec;

} // namespace PMAL
#endif
