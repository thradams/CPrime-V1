
#include "StringEx.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h> //malloc
#include "Mem.h"

void String_Init(String* s) 
{ 
    *s = 0; 
}

void String_Reset(String* pString)
{
  String_Destroy(pString);
  String_InitWith(pString, NULL);
}

void String_Destroy(String*  pString)
{
  if (pString != NULL)
  {
    Free(*pString);
    *pString = NULL;
  }
}

void String_Attach(String* pString, char* psz)
{
  Free(*pString);
  *pString = psz;
}

void String_Swap(String* pA, String* pB)
{
  String temp_Moved = *pA;
  *pA = *pB;
  *pB =  temp_Moved;
}

#ifndef SEARCH_LEAKS

void String_Set(String *pS1, const char* psz1)
{
  String s1_Moved;
  String_InitWith(&s1_Moved, psz1);

  String_Swap(&s1_Moved, pS1);
  String_Destroy(&s1_Moved);
}

void String_InitWith(String* pString, const char*  sourceOpt)
{
  if (sourceOpt != NULL)
  {
    int len = strlen(sourceOpt) + 1;
    void *   snew = Malloc(sizeof(char) * len);

    if (snew == NULL)
    {
      return;
    }

    memcpy(snew, sourceOpt, len);
    *pString = (char*)snew;
  }
  else
  {
    *pString = NULL;
  }
}

#endif


int IsEmptyStr(const char*  psz)
{
  return psz == NULL || psz[0] == '\0';
}
