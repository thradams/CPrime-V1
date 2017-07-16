
#include "StringEx.h"
#include <stdlib.h>
#include <string.h>
#include <stdlib.h> //malloc


void String_Reset(String* pString)
{
  String_Destroy(pString);
  String_Init(pString, NULL);
}

void String_Destroy(String*  pString)
{
  if (pString != NULL)
  {
    free(*pString);
    *pString = NULL;
  }
}

void String_Attach(String* pString, char* psz)
{
  free(*pString);
  *pString = psz;
}

void String_Swap(String* pA, String* pB)
{
  String temp_Moved = *pA;
  *pA = *pB;
  *pB =  temp_Moved;
}

Result String_Set(String *pS1, const char* psz1)
{
  Result result;
  String s1_Moved;
  result = String_Init(&s1_Moved, psz1);

  if (result == RESULT_OK)
  {
    String_Swap(&s1_Moved, pS1);
    String_Destroy(&s1_Moved);
  }

  return result;
}

Result String_Init(String* pString, const char*  sourceOpt)
{
  if (sourceOpt != NULL)
  {
    size_t len = strlen(sourceOpt) + 1;
    void *   snew = malloc(sizeof(char) * len);

    if (snew == NULL)
    {
      return RESULT_OUT_OF_MEM;
    }

    memcpy(snew, sourceOpt, len);
    *pString = (char*)  snew;
  }

  else
  {
    *pString = NULL;
  }

  return RESULT_OK;
}


int IsEmptyStr(const char*  psz)
{
  return psz == NULL || psz[0] == '\0';
}
