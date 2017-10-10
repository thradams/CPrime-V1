#pragma once
#include "String.h"
#include  "TokenArray.h"

typedef enum
{
	PPTokenType_Identifier,
	PPTokenType_Number,
	PPTokenType_CharConstant,
	PPTokenType_StringLiteral,
	PPTokenType_Punctuator,
  PPTokenType_Spaces,
	PPTokenType_Other,
} PPTokenType;

typedef struct PPToken
{
	PPTokenType Token;
	String Lexeme;
	TokenSet HiddenSet;
} PPToken;

#define TOKEN_INIT { PPTokenType_Other, STRING_INIT, TOKENSET_INIT }


void PPToken_Destroy(PPToken* p);

PPToken*  PPToken_Create(const char* s, PPTokenType token);
PPToken*  PPToken_Clone(PPToken* p);
void PPToken_Delete(PPToken * p);
void PPToken_DeleteVoid(void* pv);
void PPToken_Swap(PPToken * pA, PPToken * pB);


bool PPToken_IsIdentifier(PPToken* pHead);
bool PPToken_IsSpace(PPToken* pHead);
bool PPToken_IsStringizingOp(PPToken* pHead);
bool PPToken_IsConcatOp(PPToken* pHead);
bool PPToken_IsStringLit(PPToken* pHead);
bool PPToken_IsCharLit(PPToken* pHead);
bool PPToken_IsOpenPar(PPToken* pHead);
bool PPToken_IsChar(PPToken* pHead, char ch);
bool PPToken_IsLexeme(PPToken* pHead, const char* ch);