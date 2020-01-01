#pragma once
#include "MemoryManager/FixedSizeAllocator.h"
// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();
// Find Appropriate FSA
FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size);
void* AllocateMemory(size_t i_size);
void FreeMemory(void* i_ptr);
