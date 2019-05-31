//#include "Map.h"


//#include "stdafx.h"
#include "Map2.h"
#include <string.h>
#include <stdlib.h>

#include "Mem.h"

void KeyValue_Delete(struct MapItem2* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Key);
        Free((void*)p);
    }
}

static struct MapItem2* Map2_GetAssocAt(
    struct Map2* pMap,
    const char* Key,
    unsigned int* nHashBucket,
    unsigned int* HashValue);


unsigned int String2_HashKey(const char* Key)
{
    // hash key to unsigned int value by pseudorandomizing transform
    // (algorithm copied from STL char hash in xfunctional)
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


void Map2_RemoveAll(struct Map2* pMap, void(*DeleteFunc)(void*))
{
    if (pMap->pHashTable != NULL)
    {
        for (unsigned int nHash = 0;
             nHash < pMap->nHashTableSize;
             nHash++)
        {
            struct MapItem2* pKeyValue =
                pMap->pHashTable[nHash];

            while (pKeyValue != NULL)
            {
                struct MapItem2* pKeyValueCurrent = pKeyValue;

                if (DeleteFunc)
                    DeleteFunc(pKeyValueCurrent->pValue);

                pKeyValue = pKeyValue->pNext;
                KeyValue_Delete(pKeyValueCurrent);


            }
        }

        Free(pMap->pHashTable);
        pMap->pHashTable = NULL;
        pMap->nCount = 0;
    }
}

void Map2_Destroy(struct Map2* pMap, void(*DeleteFunc)(void*))
{
    Map2_RemoveAll(pMap, DeleteFunc);
}

static struct MapItem2* Map2_GetAssocAt(
    struct Map2* pMap,
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

    struct MapItem2* pResult = NULL;

    struct MapItem2* pKeyValue =
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

bool Map2_Lookup(struct Map2* pMap,
                 const char* Key,
                 void** rValue)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    struct MapItem2* pKeyValue = Map2_GetAssocAt(pMap,
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

bool Map2_LookupKey(struct Map2* pMap,
                    const char* Key,
                    const char** rKey)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    struct MapItem2* pKeyValue = Map2_GetAssocAt(pMap,
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

bool Map2_RemoveKey(struct Map2* pMap,
                    const char* Key,
                    void** ppValue)
{
    *ppValue = 0;
    bool bResult = false;

    if (pMap->pHashTable != NULL)
    {
        unsigned int HashValue =
            String2_HashKey(Key);

        struct MapItem2** ppKeyValuePrev =
            &pMap->pHashTable[HashValue % pMap->nHashTableSize];

        struct MapItem2* pKeyValue = *ppKeyValuePrev;

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

int Map2_SetAt(struct Map2* pMap,
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

        struct MapItem2** pHashTable =
            (struct MapItem2**)Malloc(sizeof(struct MapItem2*) * pMap->nHashTableSize);

        if (pHashTable != NULL)
        {
            memset(pHashTable, 0, sizeof(struct MapItem2*) * pMap->nHashTableSize);
            pMap->pHashTable = pHashTable;
        }
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct MapItem2* pKeyValue =
            Map2_GetAssocAt(pMap,
                            Key,
                            &nHashBucket,
                            &HashValue);

        if (pKeyValue == NULL)
        {
            pKeyValue = (struct MapItem2*)Malloc(sizeof(struct MapItem2) * 1);
            pKeyValue->HashValue = HashValue;
            pKeyValue->pValue = newValue;
            pKeyValue->Key = StrDup(Key);
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

            Free(pKeyValue->Key);
            pKeyValue->Key = StrDup(Key);

        }
    }

    return result;
}

void Map2_Init(struct Map2* p) /*@default*/
{
    p->pHashTable = NULL;
    p->nHashTableSize = 0;
    p->nCount = 0;
}

void Map2_Swap(struct Map2* pA, struct Map2* pB)
{
    struct Map2 temp = *pA;
    *pA = *pB;
    *pB = temp;
}

struct Map2* Map2_Create(void) /*@default*/
{
    struct Map2* p = (struct Map2*) Malloc(sizeof * p);
    if (p != NULL)
    {
        Map2_Init(p);
    }
    return p;
}

void Map2_Delete(struct Map2* p, void(*DeleteFunc)(void*))
{
    if (p != NULL)
    {
        Map2_Destroy(p, DeleteFunc);
        Free((void*)p);
    }
}
