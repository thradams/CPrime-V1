//#include "Map.h"


//#include "stdafx.h"
#include "SymbolMap.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Ast.h"
#include "Mem.h"

static void SymbolMap_KeyValue_Delete(struct SymbolMapItem * p)
{
    if (p)
    {
        Free(p->Key);
        Free(p);
    }
}

struct SymbolMapItem * SymbolMap_GetAssocAt(
    struct SymbolMap * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue);


static unsigned int SymbolMap_String2_HashKey(const char * Key)
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


void SymbolMap_RemoveAll(struct SymbolMap * pMap)
{
    if (pMap->pHashTable != NULL)
    {
        for (int nHash = 0;
            nHash < pMap->nHashTableSize;
            nHash++)
        {
            struct SymbolMapItem * pKeyValue =
                pMap->pHashTable[nHash];

            while (pKeyValue != NULL)
            {
                struct SymbolMapItem * pKeyValueCurrent = pKeyValue;
                pKeyValue = pKeyValue->pNext;
                SymbolMap_KeyValue_Delete(pKeyValueCurrent);
            }
        }

        Free(pMap->pHashTable);
        pMap->pHashTable = NULL;
        pMap->nCount = 0;
    }
}

void SymbolMap_Destroy(struct SymbolMap * pMap)
{
    SymbolMap_RemoveAll(pMap);
}

struct SymbolMapItem * SymbolMap_FindBucket(struct SymbolMap * pMap, const char * Key)
{
    if (pMap->pHashTable == NULL)
    {
        return NULL;
    }

    unsigned int HashValue = SymbolMap_String2_HashKey(Key);
    unsigned int nHashBucket = HashValue % pMap->nHashTableSize;


    struct SymbolMapItem * pKeyValue =
        pMap->pHashTable[nHashBucket];

    return pKeyValue;
}

struct SymbolMapItem * SymbolMap_GetAssocAt(
    struct SymbolMap * pMap,
    const char * Key,
    unsigned int * nHashBucket,
    unsigned int * HashValue)
{
    if (pMap->pHashTable == NULL)
    {
        *HashValue = 0;
        *nHashBucket = 0;
        return NULL;
    }

    *HashValue = SymbolMap_String2_HashKey(Key);
    *nHashBucket = *HashValue % pMap->nHashTableSize;

    struct SymbolMapItem * pResult = NULL;

    struct SymbolMapItem * pKeyValue =
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

TTypePointer * SymbolMap_Find(struct SymbolMap * pMap,
    const char * Key)
{
    TTypePointer * pTypePointer = NULL;
    unsigned int nHashBucket, HashValue;
    struct SymbolMapItem * pKeyValue = SymbolMap_GetAssocAt(pMap,
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

bool SymbolMap_LookupKey(struct SymbolMap * pMap,
    const char * Key,
    const char ** rKey)
{
    bool bResult = false;

    unsigned int nHashBucket, HashValue;
    struct SymbolMapItem * pKeyValue = SymbolMap_GetAssocAt(pMap,
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

bool SymbolMap_RemoveKey(struct SymbolMap * pMap,
    const char * Key,
    TTypePointer ** ppValue)
{
    *ppValue = 0;
    bool bResult = false;

    if (pMap->pHashTable != NULL)
    {
        unsigned int HashValue =
            SymbolMap_String2_HashKey(Key);

        struct SymbolMapItem ** ppKeyValuePrev =
            &pMap->pHashTable[HashValue % pMap->nHashTableSize];

        struct SymbolMapItem * pKeyValue = *ppKeyValuePrev;

        for (; pKeyValue != NULL; pKeyValue = pKeyValue->pNext)
        {
            if ((pKeyValue->HashValue == HashValue) &&
                (strcmp(pKeyValue->Key, Key) == 0))
            {
                // remove from list
                *ppKeyValuePrev = pKeyValue->pNext;
                *ppValue = pKeyValue->pValue;
                SymbolMap_KeyValue_Delete(pKeyValue);
                bResult = true;
                break;
            }

            ppKeyValuePrev = &pKeyValue->pNext;
        }
    }

    return bResult;
}

int SymbolMap_SetAt(struct SymbolMap * pMap,
    const char * Key,
    TTypePointer * newValue)
{
    int result = 0;


    if (pMap->pHashTable == NULL)
    {
        if (pMap->nHashTableSize < 1)
        {
            pMap->nHashTableSize = 1000;
        }

        struct SymbolMapItem ** pHashTable =
            (struct SymbolMapItem **)Malloc(sizeof(struct SymbolMapItem *) * pMap->nHashTableSize);

        if (pHashTable != NULL)
        {
            memset(pHashTable, 0, sizeof(struct SymbolMapItem *) * pMap->nHashTableSize);
            pMap->pHashTable = pHashTable;
        }
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                Key,
                &nHashBucket,
                &HashValue);

        //if (pKeyValue == NULL)
        {
            pKeyValue = (struct SymbolMapItem *)Malloc(sizeof(struct SymbolMapItem) * 1);
            pKeyValue->HashValue = HashValue;
            pKeyValue->pValue = newValue;
            pKeyValue->Key = StrDup(Key);
            pKeyValue->pNext = pMap->pHashTable[nHashBucket];
            pMap->pHashTable[nHashBucket] = pKeyValue;
            pMap->nCount++;
            result = 0;
        }

        //else
        //{
        //    result = 1;
        //    pKeyValue->pValue = newValue;
        //    strset(pKeyValue->Key, Key);
        //}
    }

    return result;
}

void SymbolMap_Init(struct SymbolMap * p)
{
    struct SymbolMap temp = SYMBOLMAP_INIT;
    *p = temp;
}

void SymbolMap_Swap(struct SymbolMap * pA, struct SymbolMap * pB)
{
    struct SymbolMap temp = *pA;
    *pA = *pB;
    *pB = temp;
}

struct SymbolMap * SymbolMap_Create()
{
    struct SymbolMap * p = (struct SymbolMap *)Malloc(sizeof(struct SymbolMap));

    if (p != 0)
    {
        struct SymbolMap t = SYMBOLMAP_INIT;
        *p = t;
    }

    return p;
}

void SymbolMap_Delete(struct SymbolMap * p)
{
    if (p != 0)
    {
        SymbolMap_Destroy(p);
        Free(p);
    }
}

const char * PrintType(EType type)
{

    switch (type)
    {
    case TypeNull:
    case TDeclaration_ID:
        return "TDeclaration_ID";
    case TStaticAssertDeclaration_ID:
    case TEofDeclaration_ID:

    case TSingleTypeSpecifier_ID:
        return "TSingleTypeSpecifier_ID";
    case TEnumSpecifier_ID:
        return "TEnumSpecifier_ID";
    case TStructUnionSpecifier_ID:
        return "TStructUnionSpecifier_ID";

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
    case TEnumerator_ID:
        break;
    default:
        break;
    }
    return "";
}

static void SymbolMap_PrintCore(struct SymbolMap * pMap, int * n)
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
            struct SymbolMapItem * pSymbolMapItem = pMap->pHashTable[i];
            while (pSymbolMapItem != NULL)
            {
                printf("%s = %s\n", pSymbolMapItem->Key, PrintType(pSymbolMapItem->pValue->Type));
                pSymbolMapItem = pSymbolMapItem->pNext;
            }
        }
    }
}


void SymbolMap_Print(struct SymbolMap * pMap)
{
    int n = 0;
    SymbolMap_PrintCore(pMap, &n);
}



bool SymbolMap_IsTypeName(struct SymbolMap * pMap, const char * identifierName)
{
    bool bIsTypeName = false;
    bool foundResult = false;

    while (pMap)
    {
        struct SymbolMapItem * pBucket =
            SymbolMap_FindBucket(pMap, identifierName);

        while (pBucket)
        {
            if (pBucket->pValue->Type == TDeclaration_ID &&
                strcmp(pBucket->Key, identifierName) == 0)
            {
                foundResult = true;

                TDeclaration * pDeclaration =
                    (TDeclaration *)pBucket->pValue;

                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];

                    if (pItem->Type == TStorageSpecifier_ID)
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypeName = true;
                            break;
                        }
                    }
                }
            }

            if (foundResult)
                break;

            pBucket = pBucket->pNext;
        }

        if (foundResult)
            break;

        pMap = pMap->pPrevious;
    }

    return bIsTypeName;
}


TDeclaration * SymbolMap_FindFunction(struct SymbolMap * pMap, const char * funcName)
{
    TDeclaration * pDeclaration = NULL;

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                funcName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TDeclaration_ID)
            {
                if (strcmp(pKeyValue->Key, funcName) == 0)
                {
                    pDeclaration =
                        (TDeclaration *)pKeyValue->pValue;

                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pDeclaration;
}




TDeclaration * SymbolMap_FindObjFunction2(struct SymbolMap * pMap,
    const char * objName,
    const char * funcName)
{
    if (objName == NULL || funcName == NULL)
    {
        return NULL;
    }

    char buffer[500] = { 0 };
    strcat(buffer, objName);
    strcat(buffer, "_");
    strcat(buffer, funcName);
    TDeclaration * p = SymbolMap_FindFunction(pMap, buffer);
    return p;
}

TStructUnionSpecifier * SymbolMap_FindStructUnion(struct SymbolMap * pMap, const char * structTagName)
{
    TStructUnionSpecifier * pStructUnionSpecifier = NULL;

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                structTagName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TStructUnionSpecifier_ID)
            {
                if (strcmp(pKeyValue->Key, structTagName) == 0)
                {
                    pStructUnionSpecifier =
                        (TStructUnionSpecifier *)pKeyValue->pValue;
                    if (pStructUnionSpecifier->StructDeclarationList.Size > 0 ||
                        pStructUnionSpecifier->UnionSet.pHead != NULL)
                    {
                        //Se achou definicao completa pode sair
                        //se achou um _union pode sair tb
                        //pois nao tem definicao completa de union
                        break;
                    }
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pStructUnionSpecifier;
}


TEnumSpecifier * SymbolMap_FindEnum(struct SymbolMap * pMap, const char * enumTagName)
{
    TEnumSpecifier * pEnumSpecifier = NULL;

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                enumTagName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TEnumSpecifier_ID)
            {
                if (strcmp(pKeyValue->Key, enumTagName) == 0)
                {
                    pEnumSpecifier =
                        (TEnumSpecifier *)pKeyValue->pValue;
                    if (pEnumSpecifier->EnumeratorList.pHead != NULL)
                    {
                        //Se achou definicao completa pode sair
                        break;
                    }
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pEnumSpecifier;
}


TDeclaration * SymbolMap_FindTypedefDeclarationTarget(struct SymbolMap * pMap,
    const char * typedefName)
{
    TDeclaration * pDeclarationResult = NULL;


    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                typedefName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            if (pKeyValue->pValue->Type == TDeclaration_ID &&
                strcmp(pKeyValue->Key, typedefName) == 0)
            {
                TDeclaration * pDeclaration =
                    (TDeclaration *)pKeyValue->pValue;

                //typedef X Y;
                bool bIsTypedef = false;
                const char * indirectTypedef = NULL;
                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];


                    switch (pItem->Type)
                    {
                    case TStorageSpecifier_ID:
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypedef = true;
                        }
                    }
                    break;
                    case TSingleTypeSpecifier_ID:
                    {
                        TSingleTypeSpecifier * pSingleTypeSpecifier =
                            (TSingleTypeSpecifier *)pItem;

                        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
                        {
                            indirectTypedef = pSingleTypeSpecifier->TypedefName;
                        }
                    }
                    break;
                    default:
                        //assert(false);
                        break;
                    }
                }
                if (!bIsTypedef)
                {
                    //Nao eh um typedef
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        //eh um typedef indireto
                        pDeclarationResult =
                            SymbolMap_FindTypedefDeclarationTarget(pMap, indirectTypedef);
                    }
                    else
                    {
                        //'e um typedef direto - retorna a declaracao que ele aparece
                        pDeclarationResult = pDeclaration;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pDeclarationResult;
}

//Acha o tipo final de um typedef
//e vai somando as partes dos declaratos
//por exemplo no meio do caminho dos typedefs
//pode ter ponteiros e depois const etc.
TDeclarationSpecifiers * SymbolMap_FindTypedefTarget(struct SymbolMap * pMap,
    const char * typedefName,
    TDeclarator * declarator)
{
    //TDeclaration* pDeclarationResult = NULL;
    TDeclarationSpecifiers * pSpecifiersResult = NULL;



    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                typedefName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            if (pKeyValue->pValue->Type == TDeclaration_ID &&
                strcmp(pKeyValue->Key, typedefName) == 0)
            {
                TDeclaration * pDeclaration =
                    (TDeclaration *)pKeyValue->pValue;

                //typedef X Y;
                bool bIsTypedef = false;
                const char * indirectTypedef = NULL;
                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];

                    switch (pItem->Type)
                    {
                    case TStorageSpecifier_ID:
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypedef = true;
                        }
                    }
                    break;
                    case TSingleTypeSpecifier_ID:
                    {
                        TSingleTypeSpecifier * pSingleTypeSpecifier =
                            (TSingleTypeSpecifier *)pItem;

                        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
                        {
                            indirectTypedef = pSingleTypeSpecifier->TypedefName;
                        }
                    }
                    break;
                    default:
                        //assert(false);
                        break;

                    }
                }
                if (!bIsTypedef)
                {
                    //Nao eh um typedef
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);
                        if (pDeclarator)
                        {
                            //copiar o pointer list deste typedef para o outro
                            ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                            {
                                TPointer * pNew = TPointer_Create();
                                TPointer_Copy(pNew, pItem);
                                TPointerList_PushBack(&declarator->PointerList, pNew);
                            }

                            //eh um typedef indireto
                            pSpecifiersResult =
                                SymbolMap_FindTypedefTarget(pMap, indirectTypedef, declarator);
                        }
                        else
                        {
                            //assert(false);
                        }
                    }
                    else
                    {
                        //'e um typedef direto - retorna a declaracao que ele aparece
                        pSpecifiersResult = &pDeclaration->Specifiers;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pSpecifiersResult;// &pDeclarationResult->Specifiers;
}



//Acha o primeiro typedef
//somas as partes do declarator
TDeclarationSpecifiers * SymbolMap_FindTypedefFirstTarget(struct SymbolMap * pMap,
    const char * typedefName,
    TDeclarator * declarator)
{
    //TDeclaration* pDeclarationResult = NULL;
    TDeclarationSpecifiers * pSpecifiersResult = NULL;



    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem * pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                typedefName,
                &nHashBucket,
                &HashValue);

        while (pKeyValue != NULL)
        {
            if (pKeyValue->pValue->Type == TDeclaration_ID &&
                strcmp(pKeyValue->Key, typedefName) == 0)
            {
                TDeclaration * pDeclaration =
                    (TDeclaration *)pKeyValue->pValue;

                //typedef X Y;
                bool bIsTypedef = false;
                const char * indirectTypedef = NULL;

                for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
                {
                    TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];


                    switch (pItem->Type)
                    {
                    case TStorageSpecifier_ID:
                    {
                        TStorageSpecifier * pStorageSpecifier =
                            (TStorageSpecifier *)pItem;
                        if (pStorageSpecifier->Token == TK_TYPEDEF)
                        {
                            bIsTypedef = true;
                        }
                    }
                    break;
                    case TSingleTypeSpecifier_ID:
                    {
                        TSingleTypeSpecifier * pSingleTypeSpecifier =
                            (TSingleTypeSpecifier *)pItem;

                        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
                        {
                            indirectTypedef = pSingleTypeSpecifier->TypedefName;
                        }
                    }
                    break;
                    default:
                        //assert(false);
                        break;
                    }
                }
                if (!bIsTypedef)
                {
                    //Nao eh um typedef
                    break;
                }
                else
                {
                    if (indirectTypedef != NULL)
                    {
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);
                        if (pDeclarator)
                        {
                            //copiar o pointer list deste typedef para o outro
                            ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                            {
                                TPointer * pNew = TPointer_Create();
                                TPointer_Copy(pNew, pItem);
                                TPointerList_PushBack(&declarator->PointerList, pNew);
                            }

                            //eh um typedef indireto
                            pSpecifiersResult = &pDeclaration->Specifiers;
                            //pSpecifiersResult =
                                //SymbolMap_FindTypedefTarget(pMap, indirectTypedef, declarator);
                        }
                        else
                        {
                            //assert(false);
                        }
                    }
                    else
                    {
                        //'e um typedef direto - retorna a declaracao que ele aparece
                        TDeclarator * pDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration, typedefName);

                        //copiar o pointer list deste typedef para o outro
                        ForEachListItem(TPointer, pItem, &pDeclarator->PointerList)
                        {
                            TPointer * pNew = TPointer_Create();
                            TPointer_Copy(pNew, pItem);
                            TPointerList_PushBack(&declarator->PointerList, pNew);
                        }

                        pSpecifiersResult = &pDeclaration->Specifiers;
                    }
                    break;
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }

    return pSpecifiersResult;// &pDeclarationResult->Specifiers;

}
TTypeSpecifier * SymbolMap_FindTypedefSpecifierTarget(struct SymbolMap * pMap,
    const char * typedefName)
{
    /*Sample:
    struct X;
    typedef struct X X;
    struct X { int i;  };
    typedef X Y;
    */

    TTypeSpecifier * pSpecifierTarget = NULL;

    TDeclaration * pDeclaration =
        SymbolMap_FindTypedefDeclarationTarget(pMap, typedefName);
    if (pDeclaration)
    {
        for (int i = 0; i < pDeclaration->Specifiers.Size; i++)
        {
            TDeclarationSpecifier * pItem = pDeclaration->Specifiers.pData[i];


            switch (pItem->Type)
            {
            case TSingleTypeSpecifier_ID:
                pSpecifierTarget = (TTypeSpecifier *)pItem;
                break;

            case TStructUnionSpecifier_ID:
            {
                TStructUnionSpecifier * pStructUnionSpecifier =
                    (TStructUnionSpecifier *)pItem;
                if (pStructUnionSpecifier->StructDeclarationList.Size == 0)
                {
                    if (pStructUnionSpecifier->TagName != NULL)
                    {
                        pSpecifierTarget = (TTypeSpecifier *)SymbolMap_FindStructUnion(pMap, pStructUnionSpecifier->TagName);
                    }
                    else
                    {
                        //assert(false);
                    }
                }
                else
                {
                    pSpecifierTarget = (TTypeSpecifier *)pStructUnionSpecifier;
                }
            }
            break;
            case TEnumSpecifier_ID:
            {
                TEnumSpecifier * pEnumSpecifier =
                    (TEnumSpecifier *)pItem;
                if (pEnumSpecifier->EnumeratorList.pHead == NULL)
                {
                    if (pEnumSpecifier->Name != NULL)
                    {
                        pEnumSpecifier = SymbolMap_FindEnum(pMap, pEnumSpecifier->Name);
                    }
                    else
                    {
                        //assert(false);
                    }
                }
                else
                {
                    pSpecifierTarget = (TTypeSpecifier *)pEnumSpecifier;
                }
            }
            break;

            default:
                break;
            }

            if (pSpecifierTarget != NULL)
            {
                //ja achou
                break;
            }
        }
    }
    return pSpecifierTarget;
}