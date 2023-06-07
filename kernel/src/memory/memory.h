#ifndef OPERATING_SYSTEM_MEMORY_H
#define OPERATING_SYSTEM_MEMORY_H

#include "../terminal/terminal.h"

struct MemoryBlock {
  int startIndex;
  int endIndex;
};

class Memory {
private:
  unsigned char memory_[1024 * 1024];
  struct MemoryBlock memoryBlocks_[1024];
  int memoryBlockNumber_;
  int FindFreeMemorySpace(int size);
  void InsertMemoryBlock(int startIndex, int endIndex);
  void RemoveMemoryBlock(int startIndex);
public:
  Memory();
  void* AllocateMemory(int size);
  void FreeMemory(void* memory);
  void* ReallocateMemory(void* currentMemory, int size);
};

#endif //OPERATING_SYSTEM_MEMORY_H
