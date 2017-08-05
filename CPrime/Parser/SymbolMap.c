//#include "Map.h"


//#include "stdafx.h"
#include "SymbolMap.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"

static void KeyValue_Delete(SymbolMapItem* p)
{
    if (p)
    {
        String_Destroy(&p->Key);
        free(p);
    }
}

static SymbolMapItem* SymbolMap_GetAssocAt(
    SymbolMap* pMap,
    const char* Key,
    unsigned int* nHashBucket,
    unsigned int* HashValue);


inline unsigned int String2_HashKey(const char*  Key)
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


void SymbolMap_RemoveAll(SymbolMap* pMap)
{
    if (pMap->pHashTable != NULL)
    {
        for (unsigned int nHash = 0;
            nHash < pMap->nHashTableSize;
            nHash++)
        {
            SymbolMapItem* pKeyValue =
                pMap->pHashTable[nHash];

            while (pKeyValue != NULL)
            {
                SymbolMapItem* pKeyValueCurrent = pKeyValue;
                pKeyValue = pKeyValue->pNext;
                KeyValue_Delete(pKeyValueCurrent);
            }
        }

        free(pMap->pHashTable);
        pMap->pHashTable = NULL;
        pMap->nCount = 0;
    }
}

void SymbolMap_Destroy(SymbolMap* pMap)
{
    SymbolMap_RemoveAll(pMap);
}

SymbolMapItem* SymbolMap_FindBucket(SymbolMap* pMap, const char*  Key)
{
    if (pMap->pHashTable == NULL)
    {
        return NULL;
    }

    unsigned int HashValue = String2_HashKey(Key);
    unsigned int nHashBucket = HashValue % pMap->nHashTableSize;


    SymbolMapItem* pKeyValue =
        pMap->pHashTable[nHashBucket];

    return pKeyValue;
}

static SymbolMapItem* SymbolMap_GetAssocAt(
    SymbolMap* pMap,
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

    SymbolMapItem* pResult = NULL;

    SymbolMapItem* pKeyValue =
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

TTypePointer* SymbolMap_Find(SymbolMap* pMap,
    const char*  Key)
{
    TTypePointer* pTypePointer = NULL;
    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue = SymbolMap_GetAssocAt(pMap,
        Key,
        &nHashBucket,
        &HashValue);

    if (pKeyValue != NULL)
    {
        pTypePointer = pKeyValue->pValue;
    }
    

    if (pTypePointer == NULL && pMap->pPrevious != NULL)
    {
        pTypePointer = SymbolMap_Find(pMap->pPrevious, Key);
    }

    return pTypePointer;
}

bool SymbolMap_LookupKey(SymbolMap* pMap,
    const char*  Key,
    const char** rKey)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    SymbolMapItem* pKeyValue = SymbolMap_GetAssocAt(pMap,
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

bool SymbolMap_RemoveKey(SymbolMap* pMap,
    const char*  Key,
    TTypePointer** ppValue)
{
    *ppValue = 0;
    bool bResult = false;

    if (pMap->pHashTable != NULL)
    {
        unsigned int HashValue =
            String2_HashKey(Key);

        SymbolMapItem** ppKeyValuePrev =
            &pMap->pHashTable[HashValue % pMap->nHashTableSize];

        SymbolMapItem* pKeyValue = *ppKeyValuePrev;

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

int SymbolMap_SetAt(SymbolMap* pMap,
    const char* Key,
    TTypePointer* newValue,
    TTypePointer** ppPreviousValue)
{
    if (strcmp(Key, "uintptr_t") == 0)
    {
        Key = Key;
    }


    int result = 0;
    *ppPreviousValue = NULL;

    if (pMap->pHashTable == NULL)
    {
        if (pMap->nHashTableSize < 1)
        {
            pMap->nHashTableSize = 1000;
        }

        SymbolMapItem** pHashTable =
            (SymbolMapItem**)malloc(sizeof(SymbolMapItem*) * pMap->nHashTableSize);

        if (pHashTable != NULL)
        {
            memset(pHashTable, 0, sizeof(SymbolMapItem*) * pMap->nHashTableSize);
            pMap->pHashTable = pHashTable;
        }
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        SymbolMapItem* pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                Key,
                &nHashBucket,
                &HashValue);

        if (pKeyValue == NULL)
        {
            pKeyValue = (SymbolMapItem*)malloc(sizeof(SymbolMapItem) * 1);
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

void SymbolMap_Init(SymbolMap * p)
{
    SymbolMap temp = SYMBOLMAP_INIT;
    *p = temp;
}

void SymbolMap_Swap(SymbolMap * pA, SymbolMap * pB)
{
    SymbolMap temp = *pA;
    *pA = *pB;
    *pB = temp;
}

SymbolMap* SymbolMap_Create()
{
    SymbolMap* p = (SymbolMap*)malloc(sizeof(SymbolMap));

    if (p != 0)
    {
        SymbolMap t = SYMBOLMAP_INIT;
        *p = t;
    }

    return p;
}

void SymbolMap_Delete(SymbolMap * p)
{
    if (p != 0)
    {
        SymbolMap_Destroy(p);
        free(p);
    }
}

const char* PrintType(Type type)
{

    switch (type)
    {
    case TypeNull:
    case TDeclaration_ID:
        return "TDeclaration_ID";
    case TStaticAssertDeclaration_ID:
    case TEofDeclaration_ID:

    case TSingleTypeSpecifier_ID:
    case TEnumSpecifier_ID:
    case TStructUnionSpecifier_ID:
    case TStorageSpecifier_ID:
    case TAtomicTypeSpecifier_ID:
    case TTemplateTypeSpecifier_ID:
    case TStructDeclaration_ID:
    case TAlignmentSpecifier_ID:
    case TTypeQualifier_ID:
    case TFunctionSpecifier_ID:
    case TCompoundStatement_ID:
    case TExpressionStatement_ID:
    case TSwitchStatement_ID:
    case TLabeledStatement_ID:
    case TForStatement_ID:
    case TJumpStatement_ID:
    case TAsmStatement_ID:
    case TWhileStatement_ID:
    case TDoStatement_ID:
    case TIfStatement_ID:
    case TypeName_ID:

    case TInitializerListType_ID:

    case TPrimaryExpression_ID:
    case TUnaryExpressionOperator_ID:
    case TCastExpressionType_ID:
    case TPrimaryExpressionValue_ID:
    case TPrimaryExpressionLiteral_ID:
    case TPostfixExpressionCore_ID:
    case TBinaryExpression_ID:
    case TTernaryExpression_ID:
        break;
    }
    return "";
}

static void SymbolMap_PrintCore(SymbolMap* pMap, int* n)
{
    if (pMap->pPrevious)
    {
        SymbolMap_PrintCore(pMap->pPrevious, n);
        (*n)++;
    }

    for (int k = 0; k < *n; k++)
    {
        printf(" ");
    }

    if (pMap->pHashTable != NULL)
    {
        for (int i = 0; i < pMap->nHashTableSize; i++)
        {
            SymbolMapItem* pSymbolMapItem = pMap->pHashTable[i];
            if (pSymbolMapItem != NULL)
            {
                printf("%s = %s\n", pSymbolMapItem->Key, PrintType(pSymbolMapItem->pValue->Type));
            }
        }
    }
}


void SymbolMap_Print(SymbolMap* pMap)
{
    int n = 0;
    SymbolMap_PrintCore(pMap, &n);
}



static int SymbolMap_IsTypeNameCore(SymbolMap* pMap, const char* identifierName)
{
    int iResult = -1; //-1 nao achou


    SymbolMapItem* pBucket =
        SymbolMap_FindBucket(pMap, identifierName);

    while (pBucket)
    {
        if (strcmp(pBucket->Key, identifierName) == 0)
        {
            //ja achou alguma coisa agora ve se eh typedef
            iResult = 0;

            SymbolMapItem* pSymbolMapItem = pBucket;
            if (pSymbolMapItem->pValue->Type == TDeclaration_ID)
            {
                TDeclaration* p = (TDeclaration*)pSymbolMapItem->pValue;
                if (TDeclarationSpecifiers_IsTypedef(&p->Specifiers))
                {
                    iResult = 1;
                }
            }
            break;
        }
        pBucket = pBucket->pNext;
    }


    if (iResult == -1 &&
        pMap->pPrevious != NULL)
    {
        iResult = SymbolMap_IsTypeNameCore(pMap->pPrevious, identifierName);
    }


    return iResult;
}

int SymbolMap_IsTypeName(SymbolMap* pMap, const char* identifierName)
{
    if (strcmp(identifierName, "PVOID64") == 0)
    {
        identifierName = identifierName;
    }

    return SymbolMap_IsTypeNameCore(pMap, identifierName) == 1;
}
