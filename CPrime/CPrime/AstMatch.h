#pragma once
#include "..\Parser\Ast.h"


TPostfixExpressionCore * MatchStructPointerMember(const char * varName,
	TExpression * pExpression);


bool MatchNULL(TExpression * pExpression);

const char * MatchIdentifier(TExpression* pExpression);
const char * MatchPrimaryExpression(TExpression* pExpression);

TExpression * MatchFunctionCall(TExpression* pExpression,
	const char** funcNameOpt);

