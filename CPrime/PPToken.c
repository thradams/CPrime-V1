
#include "PPToken.h"
#include <stdlib.h>
#include <assert.h>
#include "Mem.h"


void PPToken_Destroy(struct  PPToken* p) /*@default*/
{
    Free((void*)p->Lexeme);
    TokenSet_Destroy(&p->HiddenSet);
}

void PPToken_Swap(struct  PPToken* pA, struct  PPToken* pB)
{
    struct  PPToken temp = *pA;
    *pA = *pB;
    *pB = temp;
}

struct  PPToken* PPToken_Clone(struct  PPToken* p)
{
    struct PPToken* pNew = PPToken_Create(p->Lexeme, p->Token);
    TokenSetAppendCopy(&pNew->HiddenSet, &p->HiddenSet);
    return pNew;
}

struct PPToken* PPToken_Create(const char* s, enum PPTokenType token)
{
    struct PPToken* p = (struct PPToken*)Malloc(sizeof(struct PPToken));

    if (p != 0)
    {
        struct PPToken t = TOKEN_INIT;
        *p = t;
        p->Lexeme = StrDup(s);
        p->Token = token;
    }
    else
    {
        //assert(false);
    }

    return p;
}

void PPToken_Delete(struct PPToken* p) /*@default*/
{
    if (p != NULL)
    {
        PPToken_Destroy(p);
        Free((void*)p);
    }
}

void PPToken_DeleteVoid(void* pv)
{
    PPToken_Delete((struct PPToken*)pv);
}

bool PPToken_IsIdentifier(struct PPToken* pHead)
{
    return pHead->Token == PPTokenType_Identifier;
}

bool PPToken_IsSpace(struct PPToken* pHead)
{
    if (pHead->Token == PPTokenType_Spaces)
    {
        return true;
    }
    return false;
}

bool PPToken_IsStringizingOp(struct PPToken* pHead)
{
    return pHead->Lexeme[0] == '#' &&
        pHead->Lexeme[1] == '\0';
}

bool PPToken_IsConcatOp(struct PPToken* pHead)
{
    return pHead->Lexeme[0] == '#' &&
        pHead->Lexeme[1] == '#' &&
        pHead->Lexeme[2] == '\0';
}

bool PPToken_IsStringLit(struct PPToken* pHead)
{
    return pHead->Token == PPTokenType_StringLiteral;
}

bool PPToken_IsCharLit(struct PPToken* pHead)
{
    return pHead->Token == PPTokenType_CharConstant;
}

bool PPToken_IsOpenPar(struct PPToken* pHead)
{
    return pHead->Lexeme[0] == '(' &&
        pHead->Lexeme[1] == '\0';
}

bool PPToken_IsChar(struct PPToken* pHead, char ch)
{
    return pHead->Lexeme[0] == ch &&
        pHead->Lexeme[1] == '\0';
}

bool PPToken_IsLexeme(struct PPToken* pHead, const char* lexeme)
{
    return strcmp(pHead->Lexeme, lexeme) == 0;
}