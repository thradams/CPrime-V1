#include "Mem.h"

#include <assert.h>

#if _DEBUG
#include <crtdbg.h>

void* DebugMalloc(const char* fileName, int line, size_t size)
{
  void * p = _malloc_dbg(size, _CLIENT_BLOCK, fileName, line);
  assert(p);
  return p;
}

void Free(void* ptr)
{
  _free_dbg(ptr, _CLIENT_BLOCK);
}
void *DebugRealloc(const char* fileName, int line, void *ptr, size_t new_size)
{
  void * p = _realloc_dbg(ptr, new_size, _CLIENT_BLOCK, fileName, line);
  assert(p);
  return p;
}

void PrintMemory()
{
  _CrtMemDumpAllObjectsSince(NULL);  
}    
#else
void PrintMemory() {}
#endif
