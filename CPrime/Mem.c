#include "Mem.h"

#if _DEBUG

struct MemInfo
{
  void * p;
  const char* fileName;
  int line;
};
#define MEM_MAX 90000
static struct MemInfo mem[MEM_MAX] = { 0 };
#define DISABLE

void* DebugMalloc(const char* fileName, int line, size_t size)
{
  void * p = malloc(size);
#ifndef DISABLE
  if (p)
  {
    int found = 0;
    for (int i = 0; i < MEM_MAX; i++)
    {
      if (mem[i].p == 0)
      {
        mem[i].p = p;
        mem[i].fileName = fileName;
        mem[i].line = line;
        found = 1;
        break;
      }
    }

    if (!found)
    {
      //aumentar 
      printf("aumentar MEM_MAX"); 
    }
  }
#endif
  return p;
}

void Free(void* ptr)
{
  if (ptr == 0)
    return;
#ifndef DISABLE

  int i = 0;
  for (; i < MEM_MAX; i++)
  {
    if (mem[i].p == ptr)
    {
      mem[i].p = 0;
      mem[i].fileName = "";
      mem[i].line = 0;
      break;
    }
  }
  if (i == MEM_MAX)
  {
	  i = 0;
	  //assert(0);
  }
#endif
  free(ptr);
}
void *DebugRealloc(const char* fileName, int line, void *ptr, size_t new_size)
{
  void * p = realloc(ptr, new_size);
#ifndef DISABLE

  if (p != 0)
  {
    if (ptr == 0)
    {
      //criou memoria 1 vez
      int found = 0;
      for (int i = 0; i < MEM_MAX; i++)
      {
        if (mem[i].p == 0)
        {
          mem[i].p = p;
          mem[i].fileName = fileName;
          mem[i].line = line;
          found = 1;
          break;
        }
      }

      if (!found)
      {
        //aumentar 
        printf("aumentar MEM_MAX");
      }
    }
    else
    {
      //memoria ja existia mudou tamanho
      //se != entao liberar antiga
      if (ptr != p)
      {
        for (int i = 0; i < MEM_MAX; i++)
        {
          if (mem[i].p == ptr)
          {
            mem[i].p = 0;
            mem[i].fileName = "";
            mem[i].line = 0;
            break;
          }
        }
		//criou memoria 1 vez
		int found = 0;
		for (int i = 0; i < MEM_MAX; i++)
		{
			if (mem[i].p == 0)
			{
				mem[i].p = p;
				mem[i].fileName = fileName;
				mem[i].line = line;
				found = 1;
				break;
			}
		}

		if (!found)
		{
			//aumentar 
			printf("aumentar MEM_MAX");
		}
      }
      else
      {
        //mesma memoria ainda
      }
    }
  }

#endif  
  return p;
}

void PrintMemory()
{
  int count = 0;
  for (int i = 0; i < MEM_MAX; i++)
  {
    if (mem[i].p != 0)
    {
      printf("%s line %d\n", mem[i].fileName, mem[i].line);
      count++;
    }
  }
  printf("%d leaks\n", count);
}    
#else
void PrintMemory() {}
#endif
