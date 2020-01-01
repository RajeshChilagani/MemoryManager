Unique things I have done 

In HeapManager(source files are Heapmanager.h & Heapmanager.cpp in Engine)
- Implemented guardbands with 0xFD as guard values. The guard bands are used in finding if the user has  overwritten the guard values indicating memory access violation.
- Implemenetd realloc in my heapmanager which I used for my monster chase.

In EnityComponent(EC.h in Engine & Components.h in MonsterChase )
- Implemented Proper Entity and Component Pattern with several Components and funtions to Add & Get Components.
- It also contains a manager class that manages all the entities similarly how components are managed in entities.
- It also removes inactive entities in the game.

Created a MemoryInterface for game projects to access memory manager MemoryInterface.h in Engine 
Defined a DebugLog macro to log messages in debug builds to show warnings in FSA and other classes. FixedSizeAllocator.h in Engine.
