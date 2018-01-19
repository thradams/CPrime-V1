//#include "Map.h"


//#include "stdafx.h"
#include "Map2.h"
#include <string.h>
#include <stdlib.h>



void KeyValue_Delete(MapItem2* p) _default
{
    if (p != NULL)
    {
        String_Destroy(&p->Key);
        free((void*)p);
    }
}

static MapItem2* Map2_GetAssocAt(
  Map2* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue);


unsigned int String2_HashKey(const char*  Key)
{
  // hash key to unsigned int value by pseudorandomizing transform
  // (algorithm copied from STL string hash in xfunctional)
  unsigned int uHashVal = 2166136261U;
  unsigned int uFirst = 0;
  unsigned int uLast = (unsigned int)strlen(Key);
  unsigned int uStride = 1 + uLast / 10;

  for (; uFirst < uLast; uFirst += uStride)
  {
    uHashVal = 16777619U * uHashVal ^ (unsigned int)Key[uFirst];
  }

  return (uHashVal);
}


void Map2_RemoveAll(Map2* pMap)
{
  if (pMap->pHashTable != NULL)
  {
    for (unsigned int nHash = 0;
         nHash < pMap->nHashTableSize;
         nHash++)
    {
      MapItem2* pKeyValue =
        pMap->pHashTable[nHash];

      while (pKeyValue != NULL)
      {
        MapItem2* pKeyValueCurrent = pKeyValue;
        pKeyValue = pKeyValue->pNext;
        KeyValue_Delete(pKeyValueCurrent);
      }
    }

    free(pMap->pHashTable);
    pMap->pHashTable = NULL;
    pMap->nCount = 0;
  }
}

void Map2_Destroy(Map2* pMap)
{
  Map2_RemoveAll(pMap);
}

static MapItem2* Map2_GetAssocAt(
  Map2* pMap,
  const char* Key,
  unsigned int* nHashBucket,
  unsigned int* HashValue)
{
  if (pMap->pHashTable == NULL)
  {
    *HashValue = 0;
    *nHashBucket = 0;
    return NULL;
  }

  *HashValue = String2_HashKey(Key);
  *nHashBucket = *HashValue % pMap->nHashTableSize;

  MapItem2* pResult = NULL;

  MapItem2* pKeyValue =
    pMap->pHashTable[*nHashBucket];

  for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
  {
    if (pKeyValue->HashValue == *HashValue &&
        strcmp(pKeyValue->Key, Key) == 0)
    {
      pResult = pKeyValue;
      break;
    }
  }

  return pResult;
}

bool Map2_Lookup(Map2* pMap,
                const char*  Key,
                void** rValue)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  MapItem2* pKeyValue = Map2_GetAssocAt(pMap,
                                      Key,
                                      &nHashBucket,
                                      &HashValue);

  if (pKeyValue != NULL)
  {
    *rValue = pKeyValue->pValue;
    bResult = true;
  }

  return bResult;
}

bool Map2_LookupKey(Map2* pMap,
                   const char*  Key,
                   const char** rKey)
{
  bool bResult = false;

  unsigned int nHashBucket, HashValue;
  MapItem2* pKeyValue = Map2_GetAssocAt(pMap,
                                      Key,
                                      &nHashBucket,
                                      &HashValue);

  if (pKeyValue != NULL)
  {
    *rKey = pKeyValue->Key;
    bResult = true;
  }

  return bResult;
}

bool Map2_RemoveKey(Map2* pMap,
                   const char*  Key,
                   void** ppValue)
{
  *ppValue = 0;
  bool bResult = false;

  if (pMap->pHashTable != NULL)
  {
    unsigned int HashValue =
      String2_HashKey(Key);

    MapItem2** ppKeyValuePrev =
      &pMap->pHashTable[HashValue % pMap->nHashTableSize];

    MapItem2* pKeyValue = *ppKeyValuePrev;

    for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
    {
      if ((pKeyValue->HashValue == HashValue) &&
          (strcmp(pKeyValue->Key, Key) == 0))
      {
        // remove from list
        *ppKeyValuePrev = pKeyValue->pNext;
        *ppValue = pKeyValue->pValue;
        KeyValue_Delete(pKeyValue);
        bResult = true;
        break;
      }

      ppKeyValuePrev = &pKeyValue->pNext;
    }
  }

  return bResult;
}

int Map2_SetAt(Map2* pMap,
              const char* Key,
              void* newValue,
              void** ppPreviousValue)
{
  int result = 0;
  *ppPreviousValue = NULL;

  if (pMap->pHashTable == NULL)
  {
    if (pMap->nHashTableSize < 1)
    {
      pMap->nHashTableSize = 1000;
    }

    MapItem2** pHashTable =
      (MapItem2**)malloc(sizeof(MapItem2*) * pMap->nHashTableSize);

    if (pHashTable != NULL)
    {
      memset(pHashTable, 0, sizeof(MapItem2*) * pMap->nHashTableSize);
      pMap->pHashTable = pHashTable;
    }
  }

  if (pMap->pHashTable != NULL)
  {
    unsigned int nHashBucket, HashValue;
    MapItem2* pKeyValue =
      Map2_GetAssocAt(pMap,
                     Key,
                     &nHashBucket,
                     &HashValue);

    if (pKeyValue == NULL)
    {
      pKeyValue = (MapItem2*)malloc(sizeof(MapItem2) * 1);
      pKeyValue->HashValue = HashValue;
      pKeyValue->pValue = newValue;
      String_InitWith(&pKeyValue->Key, Key);
      pKeyValue->pNext = pMap->pHashTable[nHashBucket];
      pMap->pHashTable[nHashBucket] = pKeyValue;
      pMap->nCount++;
      result = 0;
    }

    else
    {
      result = 1;
      *ppPreviousValue = pKeyValue->pValue;
      pKeyValue->pValue = newValue;
      String_Set(&pKeyValue->Key, Key);
    }
  }

  return result;
}

void Map2_Init(Map2 * p) _default
{
    p->pHashTable = NULL;
    p->nHashTableSize = 0;
    p->nCount = 0;
}

void Map2_Swap(Map2 * pA, Map2 * pB)
{
  Map2 temp = *pA;
  *pA = *pB;
  *pB = temp;
}

Map2* Map2_Create(void) _default
{
    Map2 *p = (Map2*) malloc(sizeof * p);
    if (p != NULL)
    {
        Map2_Init(p);
    }
    return p;
}

void Map2_Delete(Map2 * p) _default
{
    if (p != NULL)
    {
        Map2_Destroy(p);
        free((void*)p);
    }
}
