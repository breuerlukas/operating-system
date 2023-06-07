#include "memory.h"

Memory::Memory() {

}

void* Memory::AllocateMemory(int size) {
  void* memoryBlock;
  int blockStartIndex = FindFreeMemorySpace(size);
  memoryBlock = &memory_[blockStartIndex];
  InsertMemoryBlock(blockStartIndex, blockStartIndex + size - 1);
  return memoryBlock;
}

int Memory::FindFreeMemorySpace(int size) {
  if (memoryBlockNumber_ == 0 || memoryBlocks_[0].startIndex - 1 >= size) {
    return 0;
  }
  for (int i = 0; i < memoryBlockNumber_ - 1; i++) {
    MemoryBlock currentBlock = memoryBlocks_[i];
    MemoryBlock nextBlock = memoryBlocks_[i + 1];
    int spaceBetween = nextBlock.startIndex - currentBlock.endIndex - 1;
    if (spaceBetween >= size) {
      return currentBlock.endIndex + 1;
    }
  }
  return memoryBlocks_[memoryBlockNumber_ - 1].endIndex + 1;
}

void Memory::InsertMemoryBlock(int startIndex, int endIndex) {
  memoryBlockNumber_++;
  MemoryBlock memoryBlock = {startIndex, endIndex};
  if (memoryBlockNumber_ - 1 == 0) {
    memoryBlocks_[0] = memoryBlock;
    return;
  }
  if (endIndex < memoryBlocks_[0].startIndex) {
    for (int i = memoryBlockNumber_ - 1; i > 0; i--) {
      memoryBlocks_[i] = memoryBlocks_[i - 1];
    }
    memoryBlocks_[0] = memoryBlock;
    return;
  }
  if (startIndex > memoryBlocks_[memoryBlockNumber_ - 2].endIndex) {
    memoryBlocks_[memoryBlockNumber_ - 1] = memoryBlock;
    return;
  }
  for (int i = memoryBlockNumber_; i > 0; i--) {
    if (memoryBlocks_[i - 2].endIndex < startIndex) {
      memoryBlocks_[i - 1] = memoryBlock;
      return;
    }
    memoryBlocks_[i - 1] = memoryBlocks_[i - 2];
  }
}

void Memory::FreeMemory(void* memory) {
  for(int i = 0; i < memoryBlockNumber_; i++) {
    if (&memory_[memoryBlocks_[i].startIndex] == memory) {
      RemoveMemoryBlock(i);
      break;
    }
  }
}

void Memory::RemoveMemoryBlock(int startIndex) {
  int currentBlockIndex = 0;
  for (int i = 0; i < memoryBlockNumber_; i++) {
    if (i == startIndex) {
      continue;
    }
    memoryBlocks_[currentBlockIndex] = memoryBlocks_[i];
    currentBlockIndex++;
  }
  memoryBlocks_[memoryBlockNumber_] = {-1, -1};
  memoryBlockNumber_--;
}

void* Memory::ReallocateMemory(void* currentMemory, int size) {
  FreeMemory(currentMemory);
  return AllocateMemory(size);
}