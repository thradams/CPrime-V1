#include "AstMatch.h"




//Matches varName->XXXX, retorna ->XXXX
TPostfixExpressionCore* MatchStructPointerMember(const char* varName, TExpression *pExpression)
{
	TPostfixExpressionCore*  pResult = NULL;
	TPostfixExpressionCore *  pPostfixExpressionCore =
		TExpression_As_TPostfixExpressionCore(pExpression);

	if (pPostfixExpressionCore != NULL &&
		pPostfixExpressionCore->token == TK_ARROW &&
		pPostfixExpressionCore->pExpressionLeft != NULL)
	{
		const char *  pLeftLexeme =
			MatchPrimaryExpression(pPostfixExpressionCore->pExpressionLeft);
		if (pLeftLexeme &&
			strcmp(varName, pLeftLexeme) == 0)
		{
			pResult = pPostfixExpressionCore;
		}
	}

	return pResult;
}



/*bool MatchNULL(TExpression* pExpression)
{
	bool bResult = false;
	const char *  lexeme =
		MatchPrimaryExpression(pExpression);
	if (lexeme != NULL)
	{
		if (strcmp(lexeme, "0") == 0)
		{
			bResult = true;
		}
	}
	else
	{
		TPrimaryExpressionValue *  pPrimaryExpressionValue =
			TExpression_As_TPrimaryExpressionValue(pExpression);
		if (pPrimaryExpressionValue &&
			pPrimaryExpressionValue->pExpressionOpt != NULL)
		{
			pExpression = pPrimaryExpressionValue->pExpressionOpt;
		}

		//((void *)0)
		TCastExpressionType *  pCastExpressionType =
			TExpression_As_TCastExpressionType(pExpression);
		if (pCastExpressionType != NULL)
		{
			if (List_HasOneItem(&pCastExpressionType->TypeName.Declarator.PointerList))
			{
				TSingleTypeSpecifier *  pSingleTypeSpecifier =

					TTypeSpecifier_As_TSingleTypeSpecifier(pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt);

				if (pSingleTypeSpecifier != NULL)
				{

					if (pSingleTypeSpecifier->bIsVoid)
					{
						bResult = true;
					}
				}
			}
		}
	}
	return bResult;
}
*/
const char * MatchIdentifier(TExpression* pExpression)
{
	const char *  pResult = NULL;

	TPrimaryExpressionValue *  pPrimaryExpression =
		TExpression_As_TPrimaryExpressionValue(pExpression);

	if (pPrimaryExpression && 
		pPrimaryExpression->token == TK_IDENTIFIER)
	{		
		pResult = pPrimaryExpression->lexeme;		
	}

	return pResult;
}

const char *  MatchPrimaryExpression(TExpression* pExpression)
{
	const char *  pResult = NULL;

	TPrimaryExpressionValue *  pPrimaryExpression =
		TExpression_As_TPrimaryExpressionValue(pExpression);

	if (pPrimaryExpression)
	{
		if (pPrimaryExpression->pExpressionOpt == NULL)
		{
			pResult = pPrimaryExpression->lexeme;
		}
	}

	return pResult;
}


//funcName(XXX)
//returna XXX e funcName
TExpression * MatchFunctionCall(TExpression* pExpression,
	const char** funcNameOpt)
{
	TExpression *  pResult = NULL;

	TPostfixExpressionCore *  pPostfixExpressionCoreFirst =
		TExpression_As_TPostfixExpressionCore(pExpression);

	if (pPostfixExpressionCoreFirst &&
		pPostfixExpressionCoreFirst->token == TK_LEFT_PARENTHESIS)
	{
		const char*  lexeme = MatchPrimaryExpression(pPostfixExpressionCoreFirst->pExpressionLeft);

		if (lexeme != NULL)
		{
			*funcNameOpt = lexeme;			
			pResult = pPostfixExpressionCoreFirst->pExpressionRight;			
		}
	}

	return pResult;
}
