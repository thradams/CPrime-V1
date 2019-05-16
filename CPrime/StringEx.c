#include  "StringEx.h"

char* StrDup(const char* p)
{
  char* a = 0;
  if (p)
  {
    a = Malloc(strlen(p) + 1);
    if (a)
      strcpy(a, p);
  }
  else
  {
    a = Malloc(1);
    if (a)
    {
      a[0] = '\0';
    }
  }
  return a;
}
