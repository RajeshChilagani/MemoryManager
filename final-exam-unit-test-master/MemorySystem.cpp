#include "MemorySystem.h"
#include "MemoryManager/MemoryInterface.h"
#include <iostream>

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	return InitMemoryManager(i_pHeapMemory,i_sizeHeapMemory,i_OptionalNumDescriptors);
}

void Collect()
{
	ICollect();
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	
	return DestroyMemoryManager();
	// Destroy your HeapManager and FixedSizeAllocators
}




