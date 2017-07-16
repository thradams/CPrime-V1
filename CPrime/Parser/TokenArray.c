#include <stdlib.h>
#include "TokenArray.h"
#include "..\Base\Array.h"
#include "PPToken.h"
#include <string.h>
#include "..\Base\Map2.h"
#include  <stdio.h>

int TokenArray_Reserve(TokenArray* p, int nelements)
{
  return Array_Reserve((Array*)p, nelements);
}

int TokenArray_Grow(TokenArray* p, size_t nelements)
{
  return Array_Grow((Array*)p, nelements);
}

PPToken* TokenArray_PopFront(TokenArray* p)
{
  void *pItem = Array_PopFront((Array*)p);
  return (PPToken*)pItem;
}

void TokenArray_Pop(TokenArray* p)
{
  Array_Pop((Array*)p, PPToken_DeleteVoid);  
}

PPToken* TokenArray_Top(TokenArray* p)
{
  return (PPToken*)Array_Top((Array*)p);
}

int TokenArray_Push(TokenArray* p, PPToken* pItem)
{
  int r = Array_Push((Array*)p, pItem);

  if (r == -1)
  {
    PPToken_Delete(pItem);
  }

  return r;
}

void TokenArray_Clear(TokenArray* p)
{
  Array_Clear((Array*)p, PPToken_DeleteVoid);
}


void TokenArray_Init(TokenArray* p)
{
  TokenArray temp = TOKENARRAY_INIT;
  *p = temp;
}

TokenArray* TokenArray_Create()
{
  TokenArray* p = (TokenArray*)malloc(sizeof * p);

  if (p)
  {
    TokenArray_Init(p);
  }

  return p;
}

void TokenArray_Destroy(TokenArray* st)
{
  TokenArray_Clear(st);
}

void TokenArray_Swap(TokenArray* p1, TokenArray* p2)
{
  TokenArray temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

void TokenArray_Delete(TokenArray* st)
{
  if (st != NULL)
  {
    TokenArray_Destroy(st);
    free(st);
  }
}

PPToken* TokenArray_Begin(TokenArray* p)
{
  return p->pItems[0];
}

PPToken* TokenArray_End(TokenArray* p)
{
  return p->pItems[p->Size];
}

void TokenArray_RemoveAt(TokenArray* p, int index)
{
  void *pItem =
    Array_RemoveAt((Array*)p, index);
  PPToken_Delete((PPToken*)pItem);
}



bool TokenArray_Contain(TokenArray *pArray, PPToken* pToken)
{
  return false;
}

void TokenArray_AppendTokensCopy(TokenArray *pArray, PPToken** pToken, int len)
{
  for (int i = 0; i < len; i++)
  {
    TokenArray_Push(pArray, PPToken_Clone(pToken[i]));
  }
}
void TokenArray_AppendTokensMove(TokenArray *pArray, PPToken** pToken, int len)
{
  for (int i = 0; i < len; i++)
  {
    TokenArray_Push(pArray, pToken[i]);
    pToken[i] = NULL;
  }
}

void TokenArray_AppendCopy(TokenArray *pArrayTo, const TokenArray *pArrayFrom)
{
  for (int i = 0; i < pArrayFrom->Size; i++)
  {
    TokenArray_Push(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
  }
}

void TokenArray_AppendMove(TokenArray *pArrayTo, TokenArray *pArrayFrom)
{
  for (int i = 0; i < pArrayFrom->Size; i++)
  {
    TokenArray_Push(pArrayTo, pArrayFrom->pItems[i]);
    pArrayFrom->pItems[i] = NULL;
  }
}

PPToken* TokenArray_Find(const TokenArray *pArray, const char * lexeme)
{
  PPToken* pFound = NULL;

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

void TokenArray_ToStrBuilder(const TokenArray* tokens, 
  StrBuilder* strBuidler)
{
  StrBuilder_Clear(strBuidler);
  for (int i = 0; i < tokens->Size; i++)
  {
    StrBuilder_Append(strBuidler, tokens->pItems[i]->Lexeme);
  }
}

void TokenArray_Print(const TokenArray* tokens)
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


void TokenArray_Erase(TokenArray *pArray, int begin, int end)
{
  for (int i = begin; i < end; i++)
  {
    PPToken_Delete(pArray->pItems[i]);
  }

  void* pItem = pArray->pItems[0];

  if (pArray->Size > 1)
  {
    memmove(pArray->pItems + begin,
            pArray->pItems + end,
            sizeof(void*) * (pArray->Size - end));
  }

  pArray->Size = pArray->Size - end;
}


int TokenArrayMap_SetAt(TokenArrayMap* pMap,
                        const char* Key,
                        TokenArray* newValue)
{
  void *pPrevious;
  int r = Map2_SetAt((Map2*)pMap, Key, newValue, &pPrevious);
  TokenArray_Delete((TokenArray*)pPrevious);
  return r;
}

bool TokenArrayMap_Lookup(const TokenArrayMap* pMap,
                          const char*  Key,
                          TokenArray** rValue)
{
  if (pMap == NULL)
  {
    return false;
  }

  return Map2_Lookup((Map2*)pMap,
                    Key,
                    (void**)rValue);
}

bool TokenArrayMap_RemoveKey(TokenArrayMap* pMap, const char*  Key)
{
  TokenArray *pItem;
  bool r = Map2_RemoveKey((Map2*)pMap, Key, (void**)&pItem);

  if (r)
  {
    TokenArray_Delete(pItem);
  }

  return r;
}

void TokenArrayMap_Init(TokenArrayMap* p)
{
  TokenArrayMap t = TOKENARRAY_INIT;
  *p = t;
}

void TokenArrayMap_Destroy(TokenArrayMap* p)
{
  Map2_Destroy((Map2*)p);
}



void TokenArrayMap_Swap(TokenArrayMap * pA, TokenArrayMap * pB)
{
  TokenArrayMap t = TOKENARRAYMAP_INIT;
  *pA = *pB;
  *pB = t;
}

int TokenSet_Add(TokenSet* p, PPToken* pItem)
{
  int r = 0;
  PPToken* pTk = TokenSet_Find(p, pItem->Lexeme);

  if (pTk == NULL)
  {
    r = Array_Push((Array*)p, pItem);

    if (r == -1)
    {
      PPToken_Delete(pItem);
    }
  }

  else
  {
    r = 0;
    PPToken_Delete(pItem);
  }

  return r;
}


void TokenSetAppendCopy(TokenSet *pArrayTo, const TokenSet *pArrayFrom)
{
  for (int i = 0; i < pArrayFrom->Size; i++)
  {
    TokenSet_Add(pArrayTo, PPToken_Clone(pArrayFrom->pItems[i]));
  }
}


PPToken* TokenSet_Find(const TokenSet *pArray, const char * lexeme)
{
  PPToken* pFound = NULL;

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

void TokenSet_Clear(TokenSet* p)
{
  Array_Clear((Array*)p, PPToken_DeleteVoid);
}


void TokenSet_Destroy(TokenSet *pArray)
{
  TokenSet_Clear(pArray);
}

void SetIntersection(const TokenSet *p1,
                     const TokenSet *p2,
                     TokenSet *pResult)
{
  if (p1->Size != 0 && p2->Size != 0)
  {
    PPToken* first1 = p1->pItems[0];
    PPToken* last1 = p1->pItems[p1->Size];

    PPToken* first2 = p2->pItems[0];
    PPToken* last2 = p2->pItems[p2->Size];

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
          TokenSet_Add(pResult, PPToken_Clone(first1));
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