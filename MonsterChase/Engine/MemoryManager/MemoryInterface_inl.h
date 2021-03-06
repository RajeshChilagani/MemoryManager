#pragma once
//Interface functions to access FSA & HeapManager
#include "MemoryInterface.h"
#include <inttypes.h>
HeapManager* pHeapManager;
#define FSAArraySize 3
FSAInitData fsaInitArray[FSAArraySize] = { { 16,100 } ,{ 32,200 },{ 96,400 } };
FixedSizeAllocator* fsaArray[FSAArraySize];
bool InitMemoryManager(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	pHeapManager = CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	for (int i = 0; i < FSAArraySize; ++i)
	{
		fsaArray[i] = FixedSizeAllocator::Create(fsaInitArray[i], pHeapManager);
	}
	return true;
	return true;
}
void DestroyMemoryManager()
{
	for (int i = 0; i < FSAArraySize; ++i)
	{
		if (fsaArray[i])
		{
			fsaArray[i]->Destroy(pHeapManager);
			free(pHeapManager, fsaArray[i]);
			fsaArray[i] = nullptr;
		}
	}
	if (pHeapManager)
	{
		Destroy(pHeapManager);
		pHeapManager = nullptr;
	}
}
inline FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size)
{
	if (i_size > 0 && i_size <= 16)
	{
		std::cout << "fsa16 \n";
		return fsaArray[0];
	}
	else if (i_size > 16 && i_size <= 32)
	{
		std::cout << "fsa32 \n";
		return fsaArray[1];
	}
	else if (i_size > 32 && i_size <= 96)
	{
		std::cout << "fsa96 \n";
		return fsaArray[2];
	}
	return nullptr;
}
inline void* AllocateMemory(size_t i_size)
{
	void* pReturn = nullptr;
	FixedSizeAllocator* FSA = FindFixedSizeAllocator(i_size);

	if (FSA)
	{
		pReturn = FSA->FSAalloc();
	}

	if (pReturn == nullptr)
	{
		pReturn = alloc(pHeapManager, i_size);
	}
	return pReturn;
}
inline void FreeMemory(void* i_ptr)
{
	int i = 0;
	while (i < FSAArraySize)
	{
		if (fsaArray[i] && fsaArray[i]->FSAContains(i_ptr))
		{
			fsaArray[i]->FSAfree(i_ptr);
			return;
		}
		i++;
	}
	if (pHeapManager)
	{
		free(pHeapManager, i_ptr);
	}
}
_Ret_notnull_ _Post_writable_byte_size_(i_size)
_VCRT_ALLOCATOR void* __CRTDECL operator new (size_t i_size)
{
	printf("calling new(i_size ) for allocation: %zu\n", i_size);
	return AllocateMemory(i_size);
}

void operator delete(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return FreeMemory(i_ptr);

}

_Ret_notnull_ _Post_writable_byte_size_(i_size)
_VCRT_ALLOCATOR void* __CRTDECL operator new[](size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("calling []new(i_size ) for allocation: %zu\n", i_size);
	return AllocateMemory(i_size);
}

void operator delete [](void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return FreeMemory(i_ptr);
}
//Placement new
inline void * operator new(size_t i_size, uint8_t* i_ptr)
{
	std::cout << "Calling new(size_t i_size, uint8_t* i_ptr) for " << "\n";
	return i_ptr;
}
void* operator new(size_t i_size, NewAlignmemt i_align)
{
	std::cout << "Calling new(size_t i_size, NewAlignement enum i_align ) for allocation: " << i_size << "\n";
	switch (i_align)
	{
	case NEW_ALIGN_8:
	case NEW_ALIGN_16:
	case NEW_ALIGN_32:
		return alloc(pHeapManager, i_size, i_align);
		break;
	default:
		return AllocateMemory(i_size);
		break;
	}
}
void operator delete(void* i_ptr, NewAlignmemt i_align)
{
	std::cout << "calling delete(void* i_ptr, NewAlignement enum i_align) \n";
	//assert(i_ptr);
	FreeMemory(i_ptr);
}
inline char* myStrdup(const char* src)
{
	char* dst = static_cast<char*>(malloc(strlen(src) + 1));
	if (dst == nullptr)
		return nullptr;
	memcpy(dst, src, strlen(src));
	dst[strlen(src)] = '\0';
	return dst;
}
inline void ICollect()
{
	Collect(pHeapManager);
}

