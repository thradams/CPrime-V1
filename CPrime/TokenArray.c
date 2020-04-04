#include <stdlib.h>
#include "TokenArray.h"

#include "PPToken.h"
#include <string.h>
#include "Map2.h"
#include  <stdio.h>
#include "Mem.h"

void TokenArray_Reserve(struct TokenArray* p, int nelements) /*@default*/
{
    if (nelements > p->Capacity)
    {
        struct PPToken** pnew = p->pItems;
        pnew = (struct PPToken**)Realloc(pnew, nelements * sizeof(struct PPToken*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = nelements;
        }
    }
}



struct PPToken* TokenArray_PopFront(struct TokenArray* p)
{
    struct PPToken* pItem = NULL;
    if (p->Size > 0)
    {
        pItem = p->pItems[0];
        if (p->Size > 1)
        {
            memmove(p->pItems, p->pItems + 1, sizeof(void*) * (p->Size - 1));
        }
        p->Size--;
    }
    return pItem;    
}

void TokenArray_Pop(struct TokenArray* p)
{
    void* pItem = 0;
    if (p->Size > 0)
    {
        pItem = p->pItems[p->Size - 1];
        p->pItems[p->Size - 1] = NULL;
        p->Size--;
    }    
    PPToken_Delete(pItem);
}

struct PPToken* TokenArray_Top(struct TokenArray* p)
{
    if (p->Size)
      return p->pItems[p->Size - 1];    
    return NULL;
}

void TokenArray_PushBack(struct TokenArray* p, struct PPToken* pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TokenArray_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

void TokenArray_Clear(struct TokenArray* p)
{
    for (int i = 0; i < p->Size; i++)
    {
        PPToken_Delete(p->pItems[i]);
    }
    Free(p->pItems);
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}


void TokenArray_Init(struct TokenArray* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

struct TokenArray* TokenArray_Create() /*@default*/
{
    struct TokenArray *p = (struct TokenArray *) Malloc(sizeof * p);
    if (p != NULL)
    {
        TokenArray_Init(p);
    }
    return p;
}

void TokenArray_Destroy(struct TokenArray* st) /*@default*/
{
    for (int i = 0; i < st->Size; i++)
    {
        PPToken_Delete(st->pItems[i]);
    }
    Free((void*)st->pItems);
}

void TokenArray_Swap(struct TokenArray* p1, struct TokenArray* p2)
{
    struct TokenArray temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void TokenArray_Delete(struct TokenArray* st) /*@default*/
{
    if (st != NULL)
    {
        TokenArray_Destroy(st);
        Free((void*)st);
    }
}




void TokenArray_AppendTokensCopy(struct TokenArray* pArray, struct PPToken** pToken, int len)
{
    for (int i = 0; i < len; i++)
    {
        TokenArray_PushBack(pArray, PPToken_Clone(pToken[i]));
    }
}
void TokenArray_AppendTokensMove(struct TokenArray* pArray, struct PPToken** pToken, int len)
{
    for (int i = 0; i < len; i++)
    {
        TokenArray_PushBack(pArray, pToken[i]);
        pToken[i] = NULL;
    }
}

void TokenArray_AppendCopy(struct TokenArray* pArrayTo, const struct TokenArray* pArrayFrom)
{
    for (int i = 0; i < pArrayFrom->Size; i++)
    {
        TokenArray_PushBack(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
    }
}

void TokenArray_AppendMove(struct TokenArray* pArrayTo, struct TokenArray* pArrayFrom)
{
    for (int i = 0; i < pArrayFrom->Size; i++)
    {
        TokenArray_PushBack(pArrayTo, pArrayFrom->pItems[i]);
        pArrayFrom->pItems[i] = NULL;
    }
}

struct PPToken* TokenArray_Find(const struct TokenArray* pArray, const char* lexeme)
{
    struct PPToken* pFound = NULL;

    for (int i = 0; i < pArray->Size; i++)
    {
        if (strcmp(lexeme, pArray->pItems[i]->Lexeme) == 0)
        {
            pFound = pArray->pItems[i];
            break;
        }
    }

    return pFound;
}

void TokenArray_ToStrBuilder(const struct TokenArray* tokens,
                             struct StrBuilder* strBuidler)
{
    StrBuilder_Clear(strBuidler);
    for (int i = 0; i < tokens->Size; i++)
    {
        StrBuilder_Append(strBuidler, tokens->pItems[i]->Lexeme);
    }
}

void TokenArray_Print(const struct TokenArray* tokens)
{
    if (tokens->Size == 0)
    {
        //printf("(empty)");
    }

    //for (int i = 0; i < tokens->Size; i++)
    //{

      //printf(" '%s' ", tokens->pItems[i]->Lexeme);

    //}
    //printf("\n");

}


void TokenArray_Erase(struct TokenArray* pArray, int begin, int end)
{
    for (int i = begin; i < end; i++)
    {
        PPToken_Delete(pArray->pItems[i]);
    }


    if (pArray->Size > 1)
    {
        memmove(pArray->pItems + begin,
                pArray->pItems + end,
                sizeof(void*) * (pArray->Size - end));
    }

    pArray->Size = pArray->Size - end;
}


int TokenArrayMap_SetAt(struct TokenArrayMap* pMap,
                        const char* Key,
                        struct TokenArray* newValue)
{
    void* pPrevious;
    int r = Map2_SetAt((struct Map2*)pMap, Key, newValue, &pPrevious);
    TokenArray_Delete((struct TokenArray*)pPrevious);
    return r;
}

bool TokenArrayMap_Lookup(const struct TokenArrayMap* pMap,
                          const char* Key,
                          struct TokenArray** rValue)
{
    if (pMap == NULL)
    {
        return false;
    }

    return Map2_Lookup((struct Map2*)pMap,
                       Key,
                       (void**)rValue);
}

bool TokenArrayMap_RemoveKey(struct TokenArrayMap* pMap, const char* Key)
{
    struct TokenArray* pItem;
    bool r = Map2_RemoveKey((struct Map2*)pMap, Key, (void**)& pItem);

    if (r)
    {
        TokenArray_Delete(pItem);
    }

    return r;
}

void TokenArrayMap_Init(struct TokenArrayMap* p)
{
    struct TokenArrayMap t = TOKENARRAY_INIT;
    *p = t;
}


static void TokenArray_DeleteVoid(void* p)
{
    TokenArray_Delete((struct TokenArray*)p);
}

void TokenArrayMap_Destroy(struct TokenArrayMap* p)
{
    Map2_Destroy((struct Map2*)p, &TokenArray_DeleteVoid);
}



void TokenArrayMap_Swap(struct TokenArrayMap* pA, struct TokenArrayMap* pB)
{
    struct TokenArrayMap t = TOKENARRAYMAP_INIT;
    *pA = *pB;
    *pB = t;
}

static void TokenSet_Push(struct TokenSet* p, struct PPToken* pItem)
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        struct PPToken** pnew = p->pItems;
        pnew = (struct PPToken**)Realloc(pnew,  n * sizeof(struct PPToken*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

void TokenSet_PushUnique(struct TokenSet* p, struct PPToken* pItem) /*custom*/
{
    struct PPToken* pTk = TokenSet_Find(p, pItem->Lexeme);

    if (pTk == NULL)
    {
        TokenSet_Push(p, pItem);        
    }
    else
    {
        PPToken_Delete(pItem);
    }

}


void TokenSetAppendCopy(struct TokenSet* pArrayTo, const struct TokenSet* pArrayFrom)
{
    for (int i = 0; i < pArrayFrom->Size; i++)
    {
        TokenSet_PushUnique(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
    }
}


struct PPToken* TokenSet_Find(const struct TokenSet* pArray, const char* lexeme)
{
    struct PPToken* pFound = NULL;

    for (int i = 0; i < pArray->Size; i++)
    {
        if (strcmp(lexeme, pArray->pItems[i]->Lexeme) == 0)
        {
            pFound = pArray->pItems[i];
            break;
        }
    }

    return pFound;
}


void TokenSet_Destroy(struct TokenSet* pArray) /*@default*/
{
    for (int i = 0; i < pArray->Size; i++)
    {
        PPToken_Delete(pArray->pItems[i]);
    }
    Free((void*)pArray->pItems);
}

void SetIntersection(const struct TokenSet* p1,
                     const struct TokenSet* p2,
                     struct TokenSet* pResult)
{
    if (p1->Size != 0 && p2->Size != 0)
    {
        struct PPToken* first1 = p1->pItems[0];
        struct PPToken* last1 = p1->pItems[p1->Size];

        struct PPToken* first2 = p2->pItems[0];
        struct PPToken* last2 = p2->pItems[p2->Size];

        while (first1 != last1 && first2 != last2)
        {
            //if (comp(*first1, *first2))
            if (strcmp(first1->Lexeme, first2->Lexeme) == 0)
            {
                ++first1;
            }

            else
            {
                //if (!comp(*first2, *first1))
                if (strcmp(first2->Lexeme, first1->Lexeme) != 0)
                {
                    //*d_first++ = *first1++;
                    TokenSet_PushUnique(pResult, PPToken_Clone(first1));
                    first1++;
                    //*d_first++ = *first1++;
                    //d_first
                }

                ++first2;
            }
        }
    }

    else if (p1->Size == 0)
    {
        TokenSetAppendCopy(pResult, p1);
    }

    else if (p2->Size == 0)
    {
        TokenSetAppendCopy(pResult, p2);
    }


}

/*
http://en.cppreference.com/w/cpp/algorithm/set_intersection
template<class InputIt1, class InputIt2,
class OutputIt, class Compare>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
InputIt2 first2, InputIt2 last2,
OutputIt d_first, Compare comp)
{
while (first1 != last1 && first2 != last2) {
if (comp(*first1, *first2)) {
++first1;
} else {
if (!comp(*first2, *first1)) {
*d_first++ = *first1++;
}
++first2;
}
}
return d_first;
}
*/