
#include "CodePrint.h"
#include "Ast.h"
#include "Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Path.h"



void Options_Destroy(Options* options) _default
{
}


void TSpecifierQualifierList_CodePrint(TProgram* program, Options * options, TSpecifierQualifierList* pDeclarationSpecifiers, StrBuilder* fp);

void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp);

static void TInitializer_CodePrint(TProgram* program,
	Options * options,
	TDeclarator* pDeclarator,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TInitializer* pTInitializer,

	StrBuilder* fp);

static void TInitializerList_CodePrint(TProgram* program,
	Options * options,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TDeclarator* pDeclarator,
	TInitializerList*p,

	StrBuilder* fp);


static void TInitializerListItem_CodePrint(TProgram* program,
	Options * options,
	TDeclarator* pDeclarator,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TInitializerListItem* p,

	StrBuilder* fp);


static void TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, StrBuilder* fp);

static void TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, StrBuilder* fp);

static void TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, StrBuilder* fp);
static void TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, StrBuilder* fp);
static void TDeclaration_CodePrint(TProgram* program, Options * options, TDeclaration* p, StrBuilder* fp);
static void TExpression_CodePrint(TProgram* program, Options * options, TExpression * p, const char* name, StrBuilder* fp);
static void TStatement_CodePrint(TProgram* program, Options * options, TStatement * p, StrBuilder* fp);
static void TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem * p, StrBuilder* fp);

static void TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, StrBuilder* fp);
static void TParameter_CodePrint(TProgram* program, Options * options, TParameter* p, StrBuilder* fp);

void Output_Append(StrBuilder* p,
	Options* options,
	const char* source)
{
	if (options->bInclude  && options->IncludeLevel == 0)
		StrBuilder_Append(p, source);
}

static void TNodeClueList_CodePrint(Options* options, TScannerItemList* list,
	StrBuilder* fp)
{
	if (options->bPrintRepresentation)
	{
		//quando se imprime a representacao o espacamento
		//eh feito por fora e nao tem macros.
		return;
	}

	ForEachListItem(ScannerItem, pNodeClue, list)
	{
		switch (pNodeClue->token)
		{
		case TK_PRE_INCLUDE:

			Output_Append(fp, options, pNodeClue->lexeme.c_str);
			Output_Append(fp, options, "\n");
			//if (pNodeClue->bActive)

			options->IncludeLevel++;
			//}
			break;

		case TK_FILE_EOF:
			options->IncludeLevel--;
			//ASSERT(IncludeLevel > 0);
			//bInclude = true;
			break;
		case TK_PRE_DEFINE:
			//TODO gerar macros como init
			Output_Append(fp, options, pNodeClue->lexeme.c_str);
			Output_Append(fp, options, "\n");
			break;

		case TK_PRE_UNDEF:
		case TK_PRE_PRAGMA:
		case TK_PRE_IF:
		case TK_PRE_ENDIF:
		case TK_PRE_ELSE:
		case TK_PRE_IFDEF:
		case TK_PRE_IFNDEF:
		case TK_PRE_ELIF:
			Output_Append(fp, options, pNodeClue->lexeme.c_str);
			Output_Append(fp, options, "\n");
			break;

		case TK_COMMENT:
			if (options->bIncludeComments)
			{
				Output_Append(fp, options, pNodeClue->lexeme.c_str);
			}
			else
			{
				Output_Append(fp, options, " ");
			}

			break;

		case TK_LINE_COMMENT:
			if (options->bIncludeComments)
			{
				Output_Append(fp, options, pNodeClue->lexeme.c_str);
			}
			else
			{
				Output_Append(fp, options, "\n");
			}
			break;

		case TK_BREAKLINE:
			Output_Append(fp, options, "\n");

			break;

		case TK_MACRO_CALL:
			if (options->bExpandMacros)
			{

			}
			else
			{
				Output_Append(fp, options, pNodeClue->lexeme.c_str);
				options->bInclude = false;
			}
			break;


		case TK_MACRO_EOF:
			if (options->bExpandMacros)
			{

			}
			else
			{
				options->bInclude = true;
			}


			break;

		case TK_SPACES:
			Output_Append(fp, options, pNodeClue->lexeme.c_str);
			break;

			//case NodeClueTypeNone:      
		default:
			Output_Append(fp, options, pNodeClue->lexeme.c_str);
			break;
		}
	}

}

static void TCompoundStatement_CodePrint(TProgram* program,
	Options * options,
	TCompoundStatement * p,

	StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "{");

	for (int j = 0; j < p->BlockItemList.Size; j++)
	{
		TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
		TBlockItem_CodePrint(program, options, pBlockItem, fp);
	}

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "}");

}


static void TLabeledStatement_CodePrint(TProgram* program, Options * options, TLabeledStatement * p, StrBuilder* fp)
{


	if (p->token == TK_CASE)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "case");
		if (p->pExpression)
		{
			TExpression_CodePrint(program, options, p->pExpression, "", fp);
		}
		else
		{
			ASSERT(false);
		}
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, ":");

		TStatement_CodePrint(program, options, p->pStatementOpt, fp);
	}
	else if (p->token == TK_DEFAULT)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "default");
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, ":");
		TStatement_CodePrint(program, options, p->pStatementOpt, fp);
	}
	else if (p->token == TK_IDENTIFIER)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, p->Identifier);

		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, ":");

		TStatement_CodePrint(program, options, p->pStatementOpt, fp);
	}



}

static void TForStatement_CodePrint(TProgram* program, Options * options, TForStatement * p, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "for");
	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "(");

	if (p->pInitDeclarationOpt)
	{
		TAnyDeclaration_CodePrint(program, options, p->pInitDeclarationOpt, fp);
		if (p->pExpression2)
		{
			TExpression_CodePrint(program, options, p->pExpression2, "expr2", fp);
		}
		TNodeClueList_CodePrint(options, &p->ClueList2, fp);
		Output_Append(fp, options, ";");
		TExpression_CodePrint(program, options, p->pExpression3, "expr3", fp);
	}
	else
	{
		TExpression_CodePrint(program, options, p->pExpression1, "expr1", fp);
		TNodeClueList_CodePrint(options, &p->ClueList2, fp);
		Output_Append(fp, options, ";");
		TExpression_CodePrint(program, options, p->pExpression2, "expr2", fp);
		TNodeClueList_CodePrint(options, &p->ClueList3, fp);
		Output_Append(fp, options, ";");
		TExpression_CodePrint(program, options, p->pExpression3, "expr3", fp);
	}

	TNodeClueList_CodePrint(options, &p->ClueList4, fp);
	Output_Append(fp, options, ")");

	TStatement_CodePrint(program, options, p->pStatement, fp);


}


static void TWhileStatement_CodePrint(TProgram* program, Options * options, TWhileStatement * p, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "while");
	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "(");
	TExpression_CodePrint(program, options, p->pExpression, "expr", fp);
	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, ")");
	TStatement_CodePrint(program, options, p->pStatement, fp);

}



static void TDoStatement_CodePrint(TProgram* program, Options * options, TDoStatement * p, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "do");

	TStatement_CodePrint(program, options, p->pStatement, fp);

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "while");
	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, "(");
	TExpression_CodePrint(program, options, p->pExpression, "expr", fp);
	TNodeClueList_CodePrint(options, &p->ClueList3, fp);
	Output_Append(fp, options, ")");
	TNodeClueList_CodePrint(options, &p->ClueList4, fp);
	Output_Append(fp, options, ";");


}


static void TExpressionStatement_CodePrint(TProgram* program, Options * options, TExpressionStatement * p, StrBuilder* fp)
{
	TExpression_CodePrint(program, options, p->pExpression, "", fp);

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, ";");


}


static void TJumpStatement_CodePrint(TProgram* program, Options * options, TJumpStatement * p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);

	switch (p->token)
	{
	case TK_GOTO:
		Output_Append(fp, options, "goto");
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, p->Identifier);
		break;
	case  TK_CONTINUE:
		Output_Append(fp, options, "continue");
		break;
	case TK_BREAK:
		Output_Append(fp, options, "break");
		break;
	case TK_RETURN:
		Output_Append(fp, options, "return");
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		TExpression_CodePrint(program, options, p->pExpression, "", fp);
		break;

	default:
		ASSERT(false);
	}


	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, ";");


}

static void TAsmStatement_CodePrint(TProgram* program, Options * options, TAsmStatement * p, StrBuilder* fp)
{
	Output_Append(fp, options, "\"type\":\"asm-statement\"");

}

static void TSwitchStatement_CodePrint(TProgram* program, Options * options, TSwitchStatement * p, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "switch");

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "(");

	TExpression_CodePrint(program, options, p->pConditionExpression, "expr", fp);

	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, ")");

	TStatement_CodePrint(program, options, p->pExpression, fp);

}


static void TIfStatement_CodePrint(TProgram* program, Options * options, TIfStatement * p, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "if");

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "(");


	TExpression_CodePrint(program, options, p->pConditionExpression, "expr", fp);

	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, ")");

	if (p->pStatement->Type != TCompoundStatement_ID)
		Output_Append(fp, options, "");

	if (p->pStatement)
	{
		TStatement_CodePrint(program, options, p->pStatement, fp);
	}

	if (p->pElseStatement)
	{
		TNodeClueList_CodePrint(options, &p->ClueList3, fp);
		Output_Append(fp, options, "else");
		TStatement_CodePrint(program, options, p->pElseStatement, fp);
	}


}

static void TStatement_CodePrint(TProgram* program, Options * options, TStatement *  p, StrBuilder* fp)
{
	if (p == NULL)
	{
		return;
	}

	switch (p->Type)
	{
	case TExpressionStatement_ID:
		TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, fp);
		break;

	case TSwitchStatement_ID:
		TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, fp);
		break;

	case TLabeledStatement_ID:
		TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, fp);
		break;

	case TForStatement_ID:
		TForStatement_CodePrint(program, options, (TForStatement*)p, fp);
		break;

	case TJumpStatement_ID:
		TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, fp);
		break;

	case TAsmStatement_ID:
		TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, fp);
		break;

	case TCompoundStatement_ID:
		TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, fp);
		break;

	case TIfStatement_ID:
		TIfStatement_CodePrint(program, options, (TIfStatement*)p, fp);
		break;

	case TDoStatement_ID:
		TDoStatement_CodePrint(program, options, (TDoStatement*)p, fp);
		break;

	default:
		ASSERT(false);
		break;
	}


}

static void TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem *  p, StrBuilder* fp)
{
	if (p == NULL)
	{
		ASSERT(false);
		return;
	}


	switch (p->Type)
	{
	case TEofDeclaration_ID:
		break;

	case TStaticAssertDeclaration_ID:
		break;

	case TSwitchStatement_ID:

		TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, fp);

		break;

	case TJumpStatement_ID:

		TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, fp);

		break;

	case TForStatement_ID:

		TForStatement_CodePrint(program, options, (TForStatement*)p, fp);

		break;

	case TIfStatement_ID:

		TIfStatement_CodePrint(program, options, (TIfStatement*)p, fp);

		break;

	case TWhileStatement_ID:

		TWhileStatement_CodePrint(program, options, (TWhileStatement*)p, fp);

		break;

	case TDoStatement_ID:

		TDoStatement_CodePrint(program, options, (TDoStatement*)p, fp);

		break;

	case TDeclaration_ID:
		TDeclaration_CodePrint(program, options, (TDeclaration*)p, fp);
		//Output_Append(fp, options,  "\n");
		break;

	case TLabeledStatement_ID:

		TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, fp);

		break;

	case TCompoundStatement_ID:
		TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, fp);
		break;

	case TExpressionStatement_ID:

		TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, fp);

		break;


	case TAsmStatement_ID:

		TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, fp);

		break;

	default:
		ASSERT(false);
		break;
	}


}



bool GetType(const char* source,
	StrBuilder* strBuilderType)
{

	while (*source  &&
		*source != '_')
	{
		StrBuilder_AppendChar(strBuilderType, *source);
		source++;
	}


	return *source == '_';
}


bool GetTypeAndFunction(const char* source,
	StrBuilder* strBuilderType,
	StrBuilder* strBuilderFunc)
{

	while (*source  &&
		*source != '_')
	{
		StrBuilder_AppendChar(strBuilderType, *source);
		source++;
	}

	while (*source)
	{
		StrBuilder_AppendChar(strBuilderFunc, *source);
		source++;
	}

	return *source == '_';
}

static void TParameterTypeList_CodePrint(TProgram* program, Options * options, TParameterTypeList *p, StrBuilder* fp);


static void TPrimaryExpressionLambda_CodePrint(TProgram* program,
	Options * options,
	TPrimaryExpressionLambda * p,
	StrBuilder* fp)
{
	static int global_lambda_counter = 0;
	//Output_Append(fp, options, "l1");
	StrBuilder_AppendFmt(fp, "_lambda_%d", global_lambda_counter);

	StrBuilder sb = STRBUILDER_INIT;

	if (p->pParameterTypeListOpt)
	{
		//TNodeClueList_CodePrint(options, &p->ClueList2, &sb);


		Output_Append(&sb, options, "\n");
		StrBuilder_AppendFmt(&sb, "static void _lambda_%d(", global_lambda_counter);
		//Output_Append(&sb, options, "static void func_l1(");

		TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, &sb);

		//TNodeClueList_CodePrint(options, &p->ClueList3, &sb);
		Output_Append(&sb, options, ")");

	}
	global_lambda_counter++;
	TCompoundStatement_CodePrint(program, options, p->pCompoundStatement, &sb);

	Output_Append(&program->sbPreDeclaration, options, "\n");

	StrBuilder_Append(&program->sbPreDeclaration, sb.c_str);




	StrBuilder_Destroy(&sb);

#if NORMAL 
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "[");
	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "]");

	if (p->pParameterTypeListOpt)
	{
		TNodeClueList_CodePrint(options, &p->ClueList2, fp);
		Output_Append(fp, options, "(");

		TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, fp);

		TNodeClueList_CodePrint(options, &p->ClueList3, fp);
		Output_Append(fp, options, ")");

	}

	TCompoundStatement_CodePrint(program, options, p->pCompoundStatement, fp);
#endif

}

static void TPostfixExpressionCore_CodePrint(TProgram* program,
	Options * options,
	TPostfixExpressionCore * p,

	StrBuilder* fp)
{


	bool bIsPointer = false;

	if (p->pExpressionLeft)
	{
		TExpression_CodePrint(program, options, p->pExpressionLeft, "l", fp);
	}


	{
		if (p->pTypeName)
		{
			TNodeClueList_CodePrint(options, &p->ClueList0, fp);
			Output_Append(fp, options, "(");
			TTypeName_CodePrint(program, options, p->pTypeName, fp);
			TNodeClueList_CodePrint(options, &p->ClueList1, fp);
			Output_Append(fp, options, ")");

			//pSpecifierQualifierList = &p->pTypeName->SpecifierQualifierList;
			bIsPointer = TPointerList_IsPointer(&p->pTypeName->Declarator.PointerList);

			//falta imprimeir typename
			//TTypeName_Print*
			TInitializerList_CodePrint(program,
				options,
				(TDeclarationSpecifiers*)&p->pTypeName->SpecifierQualifierList,
				NULL,
				&p->InitializerList,

				fp);
		}

	}

	switch (p->token)
	{
	case TK_FULL_STOP:
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, ".");
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, p->Identifier);

		break;
	case TK_ARROW:
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "->");
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, p->Identifier);

		break;

	case TK_LEFT_SQUARE_BRACKET:
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "[");
		TExpression_CodePrint(program, options, p->pExpressionRight, "r", fp);
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, "]");
		break;

	case TK_LEFT_PARENTHESIS:
		//Do lado esquerdo vem o nome da funcao p->pExpressionLeft
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "(");
		TExpression_CodePrint(program, options, p->pExpressionRight, "r", fp);
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, ")");
		break;

	case TK_PLUSPLUS:
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "++");

		break;
	case TK_MINUSMINUS:
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "--");

		break;


	default:
		ASSERT(false);
		break;
	}



	if (p->pNext)
	{
		TPostfixExpressionCore_CodePrint(program, options, p->pNext, fp);
	}



}

static void TExpression_CodePrint(TProgram* program, Options * options, TExpression *  p,
	const char* name,

	StrBuilder* fp)
{
	if (p == NULL)
	{
		//ASSERT(false);
		return;
	}



	switch (p->Type)
	{
		CASE(TBinaryExpression) :
		{
			TBinaryExpression* pBinaryExpression = (TBinaryExpression*)p;

			TExpression_CodePrint(program, options, pBinaryExpression->pExpressionLeft, "l-expr", fp);

			TNodeClueList_CodePrint(options, &pBinaryExpression->ClueList0, fp);
			Output_Append(fp, options, TokenToString(pBinaryExpression->token));

			TExpression_CodePrint(program, options, ((TBinaryExpression*)p)->pExpressionRight, "r-expr", fp);
		}
		break;

		CASE(TTernaryExpression) :
		{
			TTernaryExpression* pTernaryExpression =
				(TTernaryExpression*)p;


			TExpression_CodePrint(program, options, pTernaryExpression->pExpressionLeft, "l-expr", fp);

			TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList0, fp);
			Output_Append(fp, options, "?");

			TExpression_CodePrint(program, options, pTernaryExpression->pExpressionMiddle, "m-expr", fp);

			TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList1, fp);
			Output_Append(fp, options, ":");

			TExpression_CodePrint(program, options, pTernaryExpression->pExpressionRight, "r-expr", fp);
		}
		break;

		CASE(TPrimaryExpressionLiteral) :
		{
			TPrimaryExpressionLiteral* pPrimaryExpressionLiteral
				= (TPrimaryExpressionLiteral*)p;

			ForEachListItem(TPrimaryExpressionLiteralItem, pItem, &pPrimaryExpressionLiteral->List)
			{
				TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
				Output_Append(fp, options, pItem->lexeme);
			}
		}
		break;

		CASE(TPrimaryExpressionValue) :
		{
			TPrimaryExpressionValue* pPrimaryExpressionValue =
				(TPrimaryExpressionValue*)p;

			if (pPrimaryExpressionValue->pExpressionOpt != NULL)
			{
				TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
				Output_Append(fp, options, "(");
				TExpression_CodePrint(program, options, pPrimaryExpressionValue->pExpressionOpt, "expr", fp);

				TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList1, fp);
				Output_Append(fp, options, ")");
			}
			else
			{
				TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
				Output_Append(fp, options, pPrimaryExpressionValue->lexeme);
			}
		}
		///true;

		break;

		CASE(TPrimaryExpressionLambda) :
		{
			TPrimaryExpressionLambda* pPostfixExpressionCore =
				(TPrimaryExpressionLambda*)p;
			TPrimaryExpressionLambda_CodePrint(program, options, pPostfixExpressionCore, fp);
		}
		break;

		CASE(TPostfixExpressionCore) :
		{
			TPostfixExpressionCore* pPostfixExpressionCore =
				(TPostfixExpressionCore*)p;
			TPostfixExpressionCore_CodePrint(program, options, pPostfixExpressionCore, fp);
		}
		break;

		CASE(TUnaryExpressionOperator) :
		{
			TUnaryExpressionOperator* pTUnaryExpressionOperator =
				(TUnaryExpressionOperator*)p;

			TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList0, fp);

			if (pTUnaryExpressionOperator->token == TK_SIZEOF)
			{
				if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.Size > 0)
				{
					Output_Append(fp, options, "sizeof");
					TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList1, fp);

					Output_Append(fp, options, "(");
					TTypeName_CodePrint(program, options, &pTUnaryExpressionOperator->TypeName, fp);

					TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList2, fp);
					Output_Append(fp, options, ")");
				}
				else
				{
					Output_Append(fp, options, "sizeof");
					TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
					Output_Append(fp, options, "");
				}
			}
			else
			{
				Output_Append(fp, options, TokenToString(((TBinaryExpression*)p)->token));
				TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
			}
		}
		break;

		CASE(TCastExpressionType) :
		{
			TCastExpressionType * pCastExpressionType =
				(TCastExpressionType*)p;
			TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList0, fp);
			Output_Append(fp, options, "(");

			TTypeName_CodePrint(program, options, &pCastExpressionType->TypeName, fp);


			TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList1, fp);
			Output_Append(fp, options, ")");

			TExpression_CodePrint(program, options, pCastExpressionType->pExpression, "expr", fp);
		}
		break;

	default:

		ASSERT(false);
	}



}



static   void TEnumerator_CodePrint(TProgram* program, Options * options, TEnumerator* pTEnumerator, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &pTEnumerator->ClueList0, fp);
	Output_Append(fp, options, pTEnumerator->Name);

	if (pTEnumerator->pExpression)
	{
		TNodeClueList_CodePrint(options, &pTEnumerator->ClueList1, fp);
		Output_Append(fp, options, "=");

		TExpression_CodePrint(program, options, pTEnumerator->pExpression, "expr", fp);


	}
	else
	{
		//vou criar uma expressionp enum?
	}

	if (pTEnumerator->bHasComma)
	{
		TNodeClueList_CodePrint(options, &pTEnumerator->ClueList2, fp);
		Output_Append(fp, options, ",");
	}


}

static void TEnumSpecifier_CodePrint(TProgram* program, Options * options, TEnumSpecifier* p, StrBuilder* fp)
{
	//true;

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "enum");

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, p->Name);

	TNodeClueList_CodePrint(options, &p->ClueList2, fp);

	if (p->EnumeratorList.pHead != NULL)
	{
		Output_Append(fp, options, "{");

		ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
		{
			TEnumerator_CodePrint(program, options, pTEnumerator, fp);
		}

		TNodeClueList_CodePrint(options, &p->ClueList3, fp);
		Output_Append(fp, options, "}");
	}


}

static void TUnionSetItem_CodePrint(TProgram* program, Options * options, TUnionSetItem* p, StrBuilder* fp)
{
	if (p->Token == TK_STRUCT)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "struct");
	}
	else if (p->Token == TK_UNION)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "union");
	}

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, p->Name);

	if (p->TokenFollow == TK_VERTICAL_LINE)
	{
		TNodeClueList_CodePrint(options, &p->ClueList2, fp);
		Output_Append(fp, options, "|");
	}
}

static void TUnionSet_CodePrint(TProgram* program, Options * options, TUnionSet* p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "_union");

	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "(");
	TUnionSetItem* pCurrent = p->pHead;
	while (pCurrent)
	{
		TUnionSetItem_CodePrint(program, options, pCurrent, fp);
		pCurrent = pCurrent->pNext;
	}

	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, ")");


}

static void TStructUnionSpecifier_CodePrint(TProgram* program, Options * options, TStructUnionSpecifier* p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);

	//true;

	if (p->Token == TK_STRUCT)
	{
		Output_Append(fp, options, "struct");
	}
	else if (p->Token == TK_UNION)
	{
		Output_Append(fp, options, "union");
	}

	if (p->Token2 == TK__UNION)
	{
		TUnionSet_CodePrint(program, options, &p->UnionSet, fp);
	}
	TNodeClueList_CodePrint(options, &p->ClueList1, fp);

	if (options->bPrintRepresentation)
	{
		Output_Append(fp, options, " ");
	}

	Output_Append(fp, options, p->Name);


	if (p->StructDeclarationList.Size > 0)
	{
		TNodeClueList_CodePrint(options, &p->ClueList2, fp);

		Output_Append(fp, options, "{");

		for (int i = 0; i < p->StructDeclarationList.Size; i++)
		{
			TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
			TAnyStructDeclaration_CodePrint(program, options, pStructDeclaration, fp);
		}

		TNodeClueList_CodePrint(options, &p->ClueList3, fp);
		Output_Append(fp, options, "}");
	}

}

static void TSingleTypeSpecifier_CodePrint(TProgram* program, Options * options, TSingleTypeSpecifier* p, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &p->ClueList0, fp);

	//true;
	if (p->Token != TK_IDENTIFIER)
	{
		Output_Append(fp, options,
			TokenToString(p->Token));
	}
	else
	{
		Output_Append(fp, options, p->TypedefName);
	}


}

static void TDesignator_CodePrint(TProgram* program, Options * options, TDesignator* p, StrBuilder* fp)
{
	//    if (b)
	//      Output_Append(fp, options,  ",");


	//
	if (p->Name)
	{
		//.identifier
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, ".");
		Output_Append(fp, options, p->Name);
		Output_Append(fp, options, "=");
		TExpression_CodePrint(program, options, p->pExpression, "index", fp);
	}
	else
	{
		//[constant-expression]
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		TExpression_CodePrint(program, options, p->pExpression, "index", fp);
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	}



}

#define List_HasOneItem(pList) \
 ((pList)->pHead != NULL && (pList)->pHead == (pList)->pTail)

#define List_Back(pList) \
  ((pList)->pTail)

static void TInitializerList_CodePrint(TProgram* program,
	Options * options,
	TDeclarationSpecifiers* pDeclarationSpecifiers, //<- usadao para construir {}
	TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
	TInitializerList*p,

	StrBuilder* fp)
{
	if (List_HasOneItem(p) &&
		List_Back(p)->pInitializer == NULL/* &&
										  pSpecifierQualifierList != NULL*/)
	{
		if (!options->bHideDefaultImplementation)
		{
			Output_Append(fp, options, "_default ");
		}
		//a partir de {} e um tipo consegue gerar o final  
		StrBuilder sb = STRBUILDER_INIT;
		bool bHasInitializers = false;
		InstanciateDestroy2(program,
			options,
			(TSpecifierQualifierList*)(pDeclarationSpecifiers),
			pDeclatator,                        //<-dupla para entender o tipo
			NULL,
			NULL,/*args*/
			"",
			NULL /*not used*/,
			ActionStaticInit,
			SearchNone,
			&bHasInitializers,
			&sb);
		if (bHasInitializers)
		{
			Output_Append(fp, options, sb.c_str);
		}
		else
		{
			Output_Append(fp, options, "{0}");
		}

		StrBuilder_Destroy(&sb);
	}
	else
	{

		ForEachListItem(TInitializerListItem, pItem, p)
		{
			if (!List_IsFirstItem(p, pItem))
				Output_Append(fp, options, ",");

			TInitializerListItem_CodePrint(program,
				options,
				pDeclatator,
				pDeclarationSpecifiers,
				pItem,
				fp);
		}

	}
}

static void TInitializerListType_CodePrint(TProgram* program,
	Options * options,
	TDeclarator* pDeclarator,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TInitializerListType*p,

	StrBuilder* fp)
{

	if (p->bDefault)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		TInitializer* pInitializer = NULL;
		//p->InitializerList.pHead ?
		//p->InitializerList.pHead->pInitializer : NULL;

		Output_Append(fp, options, "_default");
		Output_Append(fp, options, " {");
		if (options->bHideDefaultImplementation)
		{
		}
		else
		{
			StrBuilder sb = STRBUILDER_INIT;
			bool bHasInitializers = false;
			InstanciateDestroy2(program,
				options,
				(TSpecifierQualifierList*)(pDeclarationSpecifiers),
				pDeclarator,                        //<-dupla para entender o tipo
				pInitializer,
				NULL,/*args*/
				"",
				NULL /*not used*/,
				ActionStaticInit,
				SearchNone,
				&bHasInitializers,
				&sb);

			if (bHasInitializers)
			{
				Output_Append(fp, options, sb.c_str);
			}
			else
			{
				Output_Append(fp, options, "0");
			}

			StrBuilder_Destroy(&sb);
		}
		Output_Append(fp, options, "}");
	}
	else
	{
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, "{");

		TInitializerList_CodePrint(program,
			options,
			pDeclarationSpecifiers,
			pDeclarator,
			&p->InitializerList,

			fp);

		TNodeClueList_CodePrint(options, &p->ClueList2, fp);
		Output_Append(fp, options, "}");
	}


}


static void TInitializer_CodePrint(TProgram* program,
	Options * options,
	TDeclarator* pDeclarator,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TInitializer* pTInitializer,

	StrBuilder* fp)
{
	if (pTInitializer == NULL)
	{
		return;
	}
	if (pTInitializer->Type == TInitializerListType_ID)
	{
		TInitializerListType_CodePrint(program,
			options,
			pDeclarator,
			pDeclarationSpecifiers,
			(TInitializerListType*)pTInitializer, fp);
	}
	else
	{
		TExpression_CodePrint(program, options, (TExpression*)pTInitializer, "", fp);
	}


}



static void TPointerList_CodePrint(TProgram* program, Options * options, TPointerList *p, StrBuilder* fp)
{
	ForEachListItem(TPointer, pItem, p)
	{
		TPointer_CodePrint(program, options, pItem, fp);
	}
}

static void TParameterList_CodePrint(TProgram* program, Options * options, TParameterList *p, StrBuilder* fp)
{



	ForEachListItem(TParameter, pItem, p)
	{
		//if (!List_IsFirstItem(p, pItem))
		//{
		//  TNodeClueList_CodePrint(options, &pItem->ClueList, fp);
		//            Output_Append(fp, options,  ",");
		//}
		//TParameterDeclaration * pItem = p->pItems[i];
		TParameter_CodePrint(program, options, pItem, fp);
	}



}

static void TParameterTypeList_CodePrint(TProgram* program, Options * options, TParameterTypeList *p, StrBuilder* fp)
{
	//Output_Append(fp, options,  "(");
	TParameterList_CodePrint(program, options, &p->ParameterList, fp);

	if (p->bVariadicArgs)
	{
		//TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		//Output_Append(fp, options,  ",");

		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, "...");
	}
	//Output_Append(fp, options,  ")");

}
static void TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool bPrintName, StrBuilder* fp);

static void TDirectDeclarator_CodePrint(TProgram* program, Options * options, TDirectDeclarator* pDirectDeclarator,

	bool bPrintName,
	StrBuilder* fp)
{
	if (pDirectDeclarator == NULL)
	{
		return;
	}
	//fprintf(fp, "{");


	if (pDirectDeclarator->Identifier)
	{
		//identifier
		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
		if (bPrintName)
		{
			Output_Append(fp, options, pDirectDeclarator->Identifier);
		}
		//true;
	}
	else  if (pDirectDeclarator->pDeclarator)
	{
		//( declarator )
		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
		Output_Append(fp, options, "(");

		TDeclarator_CodePrint(program, options, pDirectDeclarator->pDeclarator, bPrintName, fp);

		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList1, fp);
		Output_Append(fp, options, ")");
	}

	if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeArray)
	{
		/*
		direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
		direct-declarator [ static type-qualifier-listopt assignment-expression ]
		direct-declarator [ type-qualifier-list static assignment-expression ]
		*/
		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
		Output_Append(fp, options, "[");
		if (pDirectDeclarator->pExpression)
		{
			TExpression_CodePrint(program, options, pDirectDeclarator->pExpression, "assignment-expression", fp);
		}
		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
		Output_Append(fp, options, "]");
	}


	if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
	{
		//( parameter-type-list )
		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
		Output_Append(fp, options, "(");
		TParameterTypeList_CodePrint(program, options, &pDirectDeclarator->Parameters, fp);
		TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
		Output_Append(fp, options, ")");
	}

	if (pDirectDeclarator->pDirectDeclarator)
	{
		//fprintf(fp, "\"direct-declarator\":");
		TDirectDeclarator_CodePrint(program, options, pDirectDeclarator->pDirectDeclarator, bPrintName, fp);
	}


	//fprintf(fp, "}");

}

static void TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool bPrintName, StrBuilder* fp)
{
	TPointerList_CodePrint(program, options, &p->PointerList, fp);
	TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, bPrintName, fp);

}

//void TInitDeclarator_CodePrint(TProgram* program, 
//Options * options, 
//TI/nitDeclarator* p,    
//StrBuilder* fp);



void TStructDeclarator_CodePrint(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pSpecifierQualifierList,
	TStructDeclarator* p,
	StrBuilder* fp)
{

	TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);
	if (p->pInitializer)
	{
		TNodeClueList_CodePrint(options, &p->ClueList1, fp);
		Output_Append(fp, options, "_defval");

		Output_Append(fp, options, "(");

		Options options2 = *options;
		options2.bExpandMacros = true;
		options2.bIncludeComments = false;


		TInitializer_CodePrint(program,
			&options2,
			p->pDeclarator,
			(TDeclarationSpecifiers*)pSpecifierQualifierList,
			p->pInitializer,

			fp);
		Output_Append(fp, options, ")");
	}

}

static void TStructDeclaratorList_CodePrint(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pSpecifierQualifierList,
	TStructDeclaratorList *p,
	StrBuilder* fp)
{




	ForEachListItem(TInitDeclarator, pItem, p)
	{
		if (!List_IsFirstItem(p, pItem))
		{
			TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
			Output_Append(fp, options, ",");
		}
		TStructDeclarator_CodePrint(program, options, pSpecifierQualifierList, pItem, fp);
	}



}

static void TStructDeclaration_CodePrint(TProgram* program,
	Options * options,
	TStructDeclaration* p,
	StrBuilder* fp)
{
	TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);
	TStructDeclaratorList_CodePrint(program,
		options,
		&p->SpecifierQualifierList,
		&p->DeclaratorList, fp);


	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, ";");


}

static void TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, StrBuilder* fp)
{
	switch (p->Type)
	{
	case TStructDeclaration_ID:
		TStructDeclaration_CodePrint(program, options, (TStructDeclaration*)p, fp);
		break;

	default:
		ASSERT(false);
		break;
	}


}

static void StorageSpecifier_CodePrint(TProgram* program, Options * options, TStorageSpecifier* p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, TokenToString(p->Token));
}

static void TFunctionSpecifier_CodePrint(TProgram* program, Options * options, TFunctionSpecifier* p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, TokenToString(p->Token));
}


static void TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);

	Output_Append(fp, options, TokenToString(p->Token));
#ifdef LANGUAGE_EXTENSIONS
	if (p->Token == TK__SIZE)
	{
		Output_Append(fp, options, "(");
		Output_Append(fp, options, p->SizeIdentifier);
		Output_Append(fp, options, ")");
	}
#endif
}

static void TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, StrBuilder* fp)
{
	for (int i = 0; i < p->Size; i++)
	{
		TTypeQualifier* pItem = p->Data[i];
		TTypeQualifier_CodePrint(program, options, pItem, fp);
	}

}
static void TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, StrBuilder* fp)
{

	TNodeClueList_CodePrint(options, &pPointer->ClueList0, fp);
	Output_Append(fp, options, "*");

	TTypeQualifierList_CodePrint(program, options, &pPointer->Qualifier, fp);



}

void TSpecifierQualifierList_CodePrint(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pDeclarationSpecifiers,
	StrBuilder* fp)
{
	for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
	{
		TSpecifierQualifier* pItem = pDeclarationSpecifiers->pData[i];
		switch (pItem->Type)
		{

			CASE(TSingleTypeSpecifier) :
				TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, fp);
			break;

			CASE(TStorageSpecifier) :
				StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, fp);
			break;
			CASE(TTypeQualifier) :
				TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, fp);
			break;
			CASE(TFunctionSpecifier) :
				TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, fp);
			break;
			//CASE(TAlignmentSpecifier) : 
			///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
			//break;

			CASE(TStructUnionSpecifier) :
				TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, fp);
			break;

			CASE(TEnumSpecifier) :
				TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, fp);
			break;

		default:
			ASSERT(false);
			break;
		}
	}


}

void TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, StrBuilder* fp)
{

	for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
	{
		TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];

		switch (pItem->Type)
		{

			CASE(TSingleTypeSpecifier) :
				TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, fp);
			break;

			CASE(TStructUnionSpecifier) :
				TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, fp);
			break;

			CASE(TEnumSpecifier) :
				TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, fp);
			break;

			CASE(TStorageSpecifier) :
				StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, fp);
			break;
			CASE(TTypeQualifier) :
				TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, fp);
			break;
			CASE(TFunctionSpecifier) :
				TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, fp);
			break;

			//CASE(TAlignmentSpecifier) : 
			///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
			//break;

		default:
			ASSERT(false);
			break;
		}
	}





}

void TInitDeclarator_CodePrint(TProgram* program,
	Options * options,
	TDeclarator* pDeclarator,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TInitDeclarator* p,
	StrBuilder* fp)
{
	TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);

	if (p->pInitializer)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, "=");
		TInitializer_CodePrint(program,
			options,
			pDeclarator,
			pDeclarationSpecifiers,
			p->pInitializer,

			fp);
	}

}



void TInitDeclaratorList_CodePrint(TProgram* program,
	Options * options,

	TDeclarationSpecifiers *pDeclarationSpecifiers,
	TInitDeclaratorList *p,

	StrBuilder* fp)
{

	//fprintf(fp, "[");
	ForEachListItem(TInitDeclarator, pInitDeclarator, p)
	{
		if (!List_IsFirstItem(p, pInitDeclarator))
			Output_Append(fp, options, ",");


		TInitDeclarator_CodePrint(program,
			options,
			pInitDeclarator->pDeclarator,
			pDeclarationSpecifiers,
			pInitDeclarator,
			fp);
	}

	//  fprintf(fp, "]");

}



TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers);


static bool FindListStructPattern(TProgram* program,
	TParameter* pParameter,
	bool* pbItemIsPointer,
	bool* pbItemIsAutoPointer,
	StrBuilder* itemTypeName,
	StrBuilder* arrayName)
{
	//Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
	//ter size, capacity e um vector de items

	bool bHasHead = false;
	bool bHasTail = false;

	//O primeiro parametro tem que ser struct or typedef para struct
	TStructUnionSpecifier* pStructUnionSpecifier =
		GetStructSpecifier(program, &pParameter->Specifiers);
	if (pStructUnionSpecifier)
	{
		//Vou analisar a "digital" da struct
		//ok tem a definicao completa da struct
		for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
		{
			TAnyStructDeclaration* pAnyStructDeclaration =
				pStructUnionSpecifier->StructDeclarationList.pItems[i];

			TStructDeclaration* pStructDeclaration =
				TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
			if (pStructDeclaration)
			{
				TStructDeclarator* pStructDeclarator =
					pStructDeclaration->DeclaratorList.pHead;

				while (pStructDeclarator)
				{
					const char* structDeclaratorName =
						TDeclarator_GetName(pStructDeclarator->pDeclarator);


					bool bIsPointer1 =
						TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

					bool bIsPointer2 =
						TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 2);
					if (bIsPointer1)

					{
						if (strcmp(structDeclaratorName, "pHead") == 0)
						{
							bHasHead = true;
						}
						if (strcmp(structDeclaratorName, "pTail") == 0)
						{
							bHasTail = true;
						}
					}

					pStructDeclarator = (pStructDeclarator)->pNext;
				}
			}
		}
	}

	return bHasHead && bHasTail;
}

static bool FindVectorStructPattern(TProgram* program,
	TParameter* pParameter,
	bool* pbItemIsPointer,
	bool* pbItemIsAutoPointer,
	StrBuilder* itemTypeName,
	StrBuilder* arrayName)
{
	//Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
	//ter size, capacity e um vector de items
	bool bHasVector = false;
	bool bHasSize = false;
	bool bHasCapacity = false;

	//O primeiro parametro tem que ser struct or typedef para struct
	TStructUnionSpecifier* pStructUnionSpecifier =
		GetStructSpecifier(program, &pParameter->Specifiers);
	if (pStructUnionSpecifier)
	{
		//Vou analisar a "digital" da struct
		//ok tem a definicao completa da struct
		for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
		{
			TAnyStructDeclaration* pAnyStructDeclaration =
				pStructUnionSpecifier->StructDeclarationList.pItems[i];

			TStructDeclaration* pStructDeclaration =
				TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
			if (pStructDeclaration)
			{
				TStructDeclarator* pStructDeclarator =
					pStructDeclaration->DeclaratorList.pHead;

				while (pStructDeclarator)
				{
					const char* structDeclaratorName =
						TDeclarator_GetName(pStructDeclarator->pDeclarator);


					bool bIsPointer1 =
						TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

					bool bIsPointer2 =
						TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 2);

					if (bIsPointer1 || bIsPointer2)
					{
						bHasVector = true;
						StrBuilder_Set(arrayName, structDeclaratorName);

						//se eh um array de ponteiros 
						bool bItemIsPointer =
							TPointerList_IsPointer(&pStructDeclarator->pDeclarator->PointerList);

						*pbItemIsPointer = bIsPointer2;

						//se eh um array de ponteiros  donos
						bool bItemIsAutoPointer =
							TPointerList_IsAutoPointer(&pStructDeclarator->pDeclarator->PointerList);

						*pbItemIsAutoPointer = bItemIsPointer;

						//este eh array
						//vamos ver o tipo do item e se ele eh auto
						//pStructDeclaration->SpecifierQualifierList
						// StrBuilder itemTypeStr = STRBUILDER_INIT;
						TTypeName* pTypeName = NULL;
						Options  options = OPTIONS_INIT;
						options.bPrintRepresentation = true;
						TSpecifierQualifierList_CodePrint(program, &options, &pStructDeclaration->SpecifierQualifierList, itemTypeName);
						//StrBuilder_Destroy(&itemTypeStr);
					}
					else  if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
					{
						if (strcmp(structDeclaratorName, "Size") == 0)
						{
							bHasSize = true;
						}
						else if (strcmp(structDeclaratorName, "Capacity") == 0)
						{
							bHasCapacity = true;
						}
					}

					pStructDeclarator = (pStructDeclarator)->pNext;
				}
			}
		}
	}

	return bHasSize && bHasCapacity && bHasVector;
}


struct TemplateVar
{
	const char* Name;
	const char* Value;
};

const char* FindValue(const char* name, int namesize, struct TemplateVar* args, int argssize)
{
	for (int i = 0; i < argssize; i++)
	{
		if (namesize == strlen(args[i].Name) &&
			strncmp(name, args[i].Name, namesize) == 0)
		{
			return args[i].Value;
		}
	}
	return "?";
}

void StrBuilder_Template(StrBuilder * p,
	const char* tmpt,
	struct TemplateVar* vars,
	int size,
	int identationLevel)
{


	const char* pch = tmpt;

	//Move tudo para o lado de acordo com a identacao
	for (int i = 0; i < identationLevel * 4; i++)
	{
		StrBuilder_AppendChar(p, ' ');
	}

	//agora nove de acordo com os espacos
	while (*pch == ' ')
	{
		for (int j = 0; j < 4; j++)
		{
			StrBuilder_AppendChar(p, ' ');
		}

		pch++;
	}

	while (*pch)
	{
		if (*pch == '$')
		{

			pch++;
			const char* name = pch;
			int namesize = 0;
			if (*pch &&
				(*pch >= 'a' && *pch <= 'z') ||
				(*pch >= 'A' && *pch <= 'Z') ||
				(*pch >= '_'))
			{
				pch++;
				namesize++;

				while (*pch &&
					(*pch >= 'a' && *pch <= 'z') ||
					(*pch >= 'A' && *pch <= 'Z') ||
					(*pch >= '0' && *pch <= '9') ||
					(*pch >= '_')) //$X_X
				{
					pch++;
					namesize++;
				}
			}

			const char* val =
				FindValue(name, namesize, vars, size);
			StrBuilder_Append(p, val);
		}
		else
		{
			//Este \b eh usado para juntar identificador
			//$part1_part2
			//$part1\b_part2
			//

			if (*pch == '\n')
			{
				StrBuilder_AppendChar(p, *pch);
				pch++;


				if (*pch != '\0') //se for o ultimo nao move
				{//Move tudo para o lado de acordo com a identacao
					for (int i = 0; i < identationLevel * 4; i++)
					{
						StrBuilder_AppendChar(p, ' ');
					}

					//agora nove de acordo com os espacos
					while (*pch == ' ')
					{
						for (int j = 0; j < 4; j++)
						{
							StrBuilder_AppendChar(p, ' ');
						}
						pch++;
					}
				}
			}
			else
			{
				if (*pch != '\b')
				{
					StrBuilder_AppendChar(p, *pch);
				}
				pch++;
			}
		}
	}
}

void GetPrefixSuffix(const char* psz, StrBuilder* prefix, StrBuilder* suffix)
{
	while (*psz && *psz != '_')
	{
		StrBuilder_AppendChar(prefix, *psz);
		psz++;
	}

	if (*psz == '_')
		psz++;

	while (*psz)
	{
		StrBuilder_AppendChar(suffix, *psz);
		psz++;
	}
}

static int FindRuntimeID(TProgram* program,
	const char* structOrTypeName,
	StrBuilder* idname)
{
	////////////
	TDeclaration * pFinalDecl =
		TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
	int typeInt = 0;
	TStructUnionSpecifier* pStructUnionSpecifier = NULL;
	if (pFinalDecl)
	{
		typeInt = 1; //typefef
		if (pFinalDecl->Specifiers.Size > 1)
		{
			pStructUnionSpecifier =
				TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
			if (pStructUnionSpecifier->Name)
			{
				//procura a mais completa
				pStructUnionSpecifier =
					SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
			}
		}
	}
	else
	{
		typeInt = 2; //struct
		pStructUnionSpecifier =
			SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
	}
	//////////////

	if (pStructUnionSpecifier &&
		pStructUnionSpecifier->Token2 == TK__UNION)
	{
		if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
		{
			TStructDeclaration* pStructDeclaration =
				TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
			if (pStructDeclaration)
			{
				TStructDeclarator* pStructDeclarator =
					pStructDeclaration->DeclaratorList.pHead;

				//o primeiro item tem que ser o ID
				if (pStructDeclarator)
				{
					const char* structDeclaratorName =
						TDeclarator_GetName(pStructDeclarator->pDeclarator);
					//if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
					{
						StrBuilder_Set(idname, structDeclaratorName);
					}
				}
			}
		}
	}
	return typeInt;
}


static int FindIDValue(TProgram* program,
	const char* structOrTypeName,
	StrBuilder* idname)
{
	////////////
	TDeclaration * pFinalDecl =
		TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
	int typeInt = 0;
	TStructUnionSpecifier* pStructUnionSpecifier = NULL;
	if (pFinalDecl)
	{
		typeInt = 1; //typefef
		if (pFinalDecl->Specifiers.Size > 1)
		{
			pStructUnionSpecifier =
				TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
			if (pStructUnionSpecifier->Name)
			{
				//procura a mais completa
				pStructUnionSpecifier =
					SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
			}
		}
	}
	else
	{
		typeInt = 2; //struct
		pStructUnionSpecifier =
			SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
	}
	//////////////

	if (pStructUnionSpecifier)
	{
		if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
		{
			TStructDeclaration* pStructDeclaration =
				TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
			if (pStructDeclaration)
			{
				TStructDeclarator* pStructDeclarator =
					pStructDeclaration->DeclaratorList.pHead;

				//o primeiro item tem que ser o ID
				if (pStructDeclarator)
				{
					const char* structDeclaratorName =
						TDeclarator_GetName(pStructDeclarator->pDeclarator);
					//if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
					{
						Options options2 = OPTIONS_INIT;
						TInitializer_CodePrint(program, &options2, pStructDeclarator->pDeclarator,
							(TDeclarationSpecifiers*)&pStructDeclaration->SpecifierQualifierList,
							pStructDeclarator->pInitializer, idname);

						//StrBuilder_Set(idname, structDeclaratorName);
					}
				}
			}
		}
	}
	return typeInt;
}


void FindUnionSetOf(TProgram* program,
	const char* structOrTypeName,
	Map2* map)
{
	TDeclaration * pFinalDecl =
		TProgram_GetFinalTypeDeclaration(program, structOrTypeName);
	int typeInt = 0;
	TStructUnionSpecifier* pStructUnionSpecifier = NULL;
	if (pFinalDecl)
	{
		typeInt = 1; //typefef
		if (pFinalDecl->Specifiers.Size > 1)
		{
			pStructUnionSpecifier =
				TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
			if (pStructUnionSpecifier->Name)
			{
				//procura a mais completa
				pStructUnionSpecifier =
					SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
			}
		}
	}
	else
	{
		typeInt = 2; //struct
		pStructUnionSpecifier =
			SymbolMap_FindStructUnion(&program->GlobalScope, structOrTypeName);
	}

	if (pStructUnionSpecifier &&
		pStructUnionSpecifier->Token2 == TK__UNION)
	{
		TUnionSetItem * pCurrent =
			pStructUnionSpecifier->UnionSet.pHead;
		while (pCurrent)
		{
			FindUnionSetOf(program, pCurrent->Name, map);
			pCurrent = pCurrent->pNext;
		}
	}
	else
	{
		void *pp;
		Map2_SetAt(map, structOrTypeName, (void*)typeInt, &pp);
	}
}

void UnionTypeDefault(TProgram* program,
	Options* options,
	const char* structName,
	TParameterTypeList * pArgsOpt, //parametros
	const char* parameterName,
	const char* functionSuffix,
	StrBuilder* fp);
static const char* GetNullStr(TProgram* program);

static void DefaultFunctionDefinition_CodePrint(TProgram* program,
	Options * options,
	TDeclaration* p,
	StrBuilder* fp)
{

	//Retorno da funcao
	TDeclarationSpecifiers* pSpecifiers =
		&p->Specifiers;

	const char* funcName =
		TDeclarator_GetName(p->InitDeclaratorList.pHead->pDeclarator);

	StrBuilder functionPrefix = STRBUILDER_INIT;
	StrBuilder functionSuffix = STRBUILDER_INIT;

	GetPrefixSuffix(funcName, &functionPrefix, &functionSuffix);

	//parametros


	TParameterTypeList * pArgs =
		TDeclaration_GetFunctionArguments(p);

	TParameter* pFirstParameter =
		TParameterTypeList_GetParameterByIndex(pArgs, 0);

	TParameter* pSecondParameter =
		TParameterTypeList_GetParameterByIndex(pArgs, 1);


	if (IsSuffix(funcName, "_Create"))
	{
		options->IdentationLevel++;

		InstanciateDestroy2(program,
			options,
			(TSpecifierQualifierList*)(pSpecifiers),
			p->InitDeclaratorList.pHead->pDeclarator,
			NULL,
			pArgs,
			"p",
			NULL /*not used*/,
			ActionCreate,
			SearchInit,
			NULL,
			fp);
		options->IdentationLevel--;
	}
	else if (IsSuffix(funcName, "_Init") && pFirstParameter != NULL)
	{
		options->IdentationLevel++;
		InstanciateDestroy2(program,
			options,
			(TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
			&pFirstParameter->Declarator,
			NULL,
			pArgs,/*args fazer inicializacao conforme parametro*/
			TParameter_GetName(pFirstParameter),
			NULL /*not used*/,
			ActionInitContent,
			SearchNone,
			NULL,
			fp);
		options->IdentationLevel--;
	}
	else if (IsSuffix(funcName, "_Destroy") && pFirstParameter != NULL)
	{

		options->IdentationLevel++;
		InstanciateDestroy2(program,
			options,
			(TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
			&pFirstParameter->Declarator,
			NULL,
			NULL,/*args*/
			TParameter_GetName(pFirstParameter),
			NULL /*not used*/,
			ActionDestroyContent,
			SearchNone,
			NULL,
			fp);
		options->IdentationLevel--;
	}
	else if (IsSuffix(funcName, "_Delete") && pFirstParameter != NULL)
	{

		options->IdentationLevel++;
		InstanciateDestroy2(program,
			options,
			(TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
			&pFirstParameter->Declarator,
			NULL,
			NULL,/*args*/
			TParameter_GetName(pFirstParameter),
			NULL /*not used*/,
			ActionDelete,
			SearchDestroy,
			NULL,
			fp);
		options->IdentationLevel--;
	}
	else
	{
		if (pFirstParameter != NULL &&
			pSecondParameter != NULL &&
			IsSuffix(funcName, "_Reserve"))
		{
			bool bItemIsPointer;
			bool bItemIsAutoPointer;
			StrBuilder itemType = STRBUILDER_INIT;
			StrBuilder arrayName = STRBUILDER_INIT;

			//Implemetancao para vector
			if (FindVectorStructPattern(program,
				pFirstParameter,
				&bItemIsPointer,
				&bItemIsAutoPointer,
				&itemType,
				&arrayName))
			{
				const char* pszTemplatePointer =
					"if ($nelements > $p->Capacity)\n"
					"{\n"
					" $type** pnew = $p->$data;\n"
					" pnew = ($type**)realloc(pnew, $nelements * sizeof($type*));\n"
					" if (pnew)\n"
					" {\n"
					"  $p->$data = pnew;\n"
					"  $p->Capacity = $nelements;\n"
					" }\n"
					"}\n";

				const char* pszTemplateNotPointer =
					"if ($nelements > $p->Capacity)\n"
					"{\n"
					" $type* pnew = $p->$data;\n"
					" pnew = ($type*)realloc(pnew, $nelements * sizeof($type));\n"
					" if (pnew)\n"
					" {\n"
					"  $p->$data = pnew;\n"
					"  $p->Capacity = $nelements;\n"
					" }\n"
					"}\n";

				const char* pszTemplate =
					bItemIsPointer ? pszTemplatePointer : pszTemplateNotPointer;

				struct TemplateVar vars[] = {
					{ "p", TParameter_GetName(pFirstParameter) },
				{ "nelements", TParameter_GetName(pSecondParameter) },
				{ "type", itemType.c_str },
				{ "data", arrayName.c_str }
				};

				StrBuilder_Template(fp,
					pszTemplate,
					vars,
					sizeof(vars) / sizeof(vars[0]),
					1 /*options->IdentationLevel*/);
			}

			StrBuilder_Destroy(&itemType);
			StrBuilder_Destroy(&arrayName);
		}
		else if (pFirstParameter != NULL &&
			pSecondParameter != NULL &&
			IsSuffix(funcName, "_PushBack"))
		{
			bool bItemIsPointer;
			bool bItemIsAutoPointer;
			StrBuilder itemType = STRBUILDER_INIT;
			StrBuilder arrayName = STRBUILDER_INIT;

			//Implemetancao para vector
			if (FindVectorStructPattern(program,
				pFirstParameter,
				&bItemIsPointer,
				&bItemIsAutoPointer,
				&itemType,
				&arrayName))
			{
				bool bHasReserve =
					SymbolMap_FindObjFunction(&program->GlobalScope, functionPrefix.c_str, "Reserve") != 0;
				const char* pszTemplate = "";

				if (bHasReserve)
				{
					pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
						"{\n"
						" int n = $p->Capacity * 2;\n"
						" if (n == 0)\n"
						" {\n"
						"  n = 1;\n"
						" }\n"
						" $prefix\b_Reserve($p, n);\n"
						"}\n"
						"$p->$data[$p->Size] = $nelements;\n"
						"$p->Size++;\n";
				}
				else
				{
					pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
						"{\n"
						" int n = $p->Capacity * 2;\n"
						" if (n == 0)\n"
						" {\n"
						"  n = 1;\n"
						" }\n"
						" $type** pnew = $p->data;\n"
						" pnew = ($type**)realloc(pnew, n * sizeof($type*));\n"
						" if (pnew)\n"
						" {\n"
						"  $p->data = pnew;\n"
						"  $p->Capacity = n;\n"
						" }\n"
						"}\n"
						"$p->$data[$p->Size] = $nelements;\n"
						"$p->Size++;\n";
				}

				struct TemplateVar vars[] = {
					{ "p", TParameter_GetName(pFirstParameter)},
				{ "nelements", TParameter_GetName(pSecondParameter) },
				{ "type", itemType.c_str },
				{ "data", arrayName.c_str },
				{ "prefix", functionPrefix.c_str }
				};

				StrBuilder_Template(fp,
					pszTemplate,
					vars,
					sizeof(vars) / sizeof(vars[0]),
					1/*options->IdentationLevel*/);
			}
			else if (FindListStructPattern(program,
				pFirstParameter,
				&bItemIsPointer,
				&bItemIsAutoPointer,
				&itemType,
				&arrayName))
			{
				struct TemplateVar vars[] = {
					{ "pList", TParameter_GetName(pFirstParameter) },
				{ "pItem", TParameter_GetName(pSecondParameter) },
				{ "type", itemType.c_str },
				{ "data", arrayName.c_str },
				{ "prefix", functionPrefix.c_str },
				{ "null", GetNullStr(program)}
				};
				//o item apontado tem que ter pNext verificar isso
				//e colocar erro se nao tiver
				const char* pszTemplate =
					"if ($pList->pHead == $null)\n"
					"{\n"
					" $pList->pHead = $pItem;\n"
					"}\n"
					"else\n"
					"{\n"
					" $pList->pTail->pNext = $pItem;\n"
					"}\n"
					"$pList->pTail = $pItem; \n";

				StrBuilder_Template(fp,
					pszTemplate,
					vars,
					sizeof(vars) / sizeof(vars[0]),
					1/*options->IdentationLevel*/);
			}

			StrBuilder_Destroy(&itemType);
			StrBuilder_Destroy(&arrayName);
		}
		else
		{
			if (pFirstParameter != NULL)
			{
				TStructUnionSpecifier* pStructUnionSpecifier =
					GetStructSpecifier(program, &pFirstParameter->Specifiers);
				if (pStructUnionSpecifier &&
					pStructUnionSpecifier->Token2 == TK__UNION)
				{
					options->IdentationLevel++;
					UnionTypeDefault(program,
						options,
						pStructUnionSpecifier->Name,
						pArgs,
						TParameter_GetName(pFirstParameter),
						functionSuffix.c_str,
						fp);
					options->IdentationLevel--;
				}
			}
		}
	}

	StrBuilder_Destroy(&functionPrefix);
	StrBuilder_Destroy(&functionSuffix);

}

static void TDeclaration_CodePrint(TProgram* program,
	Options * options,
	TDeclaration* p,

	StrBuilder* fp)
{
	TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);

	TInitDeclaratorList_CodePrint(program,
		options,
		&p->Specifiers,
		&p->InitDeclaratorList, fp);

	if (p->pCompoundStatementOpt != NULL)
	{
		/*
		typedef struct Array { int data; ... } Items;
		void Items_Add(Items* p,int i) {...}
		void Items_Delete(Items* p,int i) {...}
		*/

		if (p->bDefault)
		{
			TNodeClueList_CodePrint(options, &p->ClueList0, fp);
			StrBuilder_Append(fp, "_default");

			if (options->bHideDefaultImplementation)
			{
				Output_Append(fp, options, ";");
			}
			else
			{
				TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList0, fp);
				Output_Append(fp, options, "{\n");

				DefaultFunctionDefinition_CodePrint(program,
					options,
					p,

					fp);

				Output_Append(fp, options, "}");

			}
			return;
		}
		else
		{
			if (p->pCompoundStatementOpt != NULL)
			{
				//normal
				TCompoundStatement_CodePrint(program,
					options,
					p->pCompoundStatementOpt,

					fp);
			}
		}
	}
	else
	{
		if (p->bDefault)
		{

			if (!options->bHideDefaultImplementation)
			{
				TNodeClueList_CodePrint(options, &p->ClueList0, fp);
				StrBuilder_Append(fp, "_default");

				TNodeClueList_CodePrint(options, &p->ClueList1, fp);
				Output_Append(fp, options, "\n{\n");

				DefaultFunctionDefinition_CodePrint(program,
					options,
					p,

					fp);

				Output_Append(fp, options, "}");
			}
			else
			{
				TNodeClueList_CodePrint(options, &p->ClueList1, fp);
				StrBuilder_Append(fp, " _default");
				Output_Append(fp, options, ";");
			}

			return;
		}
		else
		{
			TNodeClueList_CodePrint(options, &p->ClueList1, fp);
			Output_Append(fp, options, ";");
		}
	}


	return;
}

void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp)
{

	TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);

	TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);


}

static void TParameter_CodePrint(TProgram* program,
	Options * options,
	TParameter* p,

	StrBuilder* fp)
{
	TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);
	TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);

	if (p->bHasComma)
	{
		TNodeClueList_CodePrint(options, &p->ClueList0, fp);
		Output_Append(fp, options, ",");
	}


}

static void TEofDeclaration_CodePrint(TProgram* program,
	Options * options,
	TEofDeclaration *p,

	StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);

}

static void TStaticAssertDeclaration_CodePrint(TProgram* program,
	Options * options,
	TStaticAssertDeclaration *p,

	StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "_StaticAssert");
	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "(");
	TExpression_CodePrint(program, options, p->pConstantExpression, "", fp);
	Output_Append(fp, options, ",");
	TNodeClueList_CodePrint(options, &p->ClueList2, fp);

	TNodeClueList_CodePrint(options, &p->ClueList3, fp);
	Output_Append(fp, options, p->Text);


	TNodeClueList_CodePrint(options, &p->ClueList4, fp);
	Output_Append(fp, options, ")");
	TNodeClueList_CodePrint(options, &p->ClueList5, fp);
	Output_Append(fp, options, ";");

}

static void TGroupDeclaration_CodePrint(TProgram* program, Options * options, TGroupDeclaration *p, StrBuilder* fp)
{
	TNodeClueList_CodePrint(options, &p->ClueList0, fp);
	Output_Append(fp, options, "#pragma region cprime");
	TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, p->Identifier);
	TNodeClueList_CodePrint(options, &p->ClueList2, fp);
	Output_Append(fp, options, "\n");
	
	TDeclaration* pFunction =
		SymbolMap_FindFunction(&program->GlobalScope, p->Identifier);
	if (pFunction)
	{
		TDeclaration_CodePrint(program, options, pFunction, fp);
	}
	else
	{
		Map2 map = MAPSTRINGTOPTR_INIT;
		FindUnionSetOf(program, p->Identifier, &map);

		StrBuilder idname = STRBUILDER_INIT;

		int ir = FindRuntimeID(program,
			p->Identifier,
			&idname);

		for (int i = 0; i < (int)map.nHashTableSize; i++)
		{
			if (map.pHashTable[i])
			{
				const char* derivedName = (const char*)map.pHashTable[i]->Key;
				const char* baseName = p->Identifier;

				StrBuilder idnamelocal = STRBUILDER_INIT;

				int ir2 = FindIDValue(program,
					derivedName,
					&idnamelocal);

				struct TemplateVar vars0[] = {
					{ "base", baseName },
				{ "derived", derivedName },
				{ "id", idname.c_str },
				{ "idvalue", idnamelocal.c_str }
				};

				if ((int)map.pHashTable[i]->pValue == 2)
				{




					if (ir == 2)
					{
						StrBuilder_Template(fp,
							"inline struct $derived* $base\b_As_$derived(struct $base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
							"inline struct $base* $derived\b_As_$base(struct $derived* p) { return (struct $base*) p; }\n",
							vars0,
							sizeof(vars0) / sizeof(vars0[0]),
							options->IdentationLevel);
					}
					else
					{
						if (ir == 2)
						{
							StrBuilder_Template(fp,
								"inline struct $derived* $base\b_As_$derived(struct $base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
								"inline struct $base* $derived\b_As_$base(struct $derived* p) { return (struct $base*) p; }\n",
								vars0,
								sizeof(vars0) / sizeof(vars0[0]),
								options->IdentationLevel);
						}
						else
						{
							StrBuilder_Template(fp,
								"inline struct $derived* $base\b_As_$derived($base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
								"inline $base* $derived\b_As_$base(struct $derived* p) { return ($base*) p; }\n",
								vars0,
								sizeof(vars0) / sizeof(vars0[0]),
								options->IdentationLevel);
						}
					}

				}
				else
				{
					StrBuilder_Template(fp,
						"inline $derived* $base\b_As_$derived($base* p) { return p->$id == $idvalue ? ($derived*) p : 0;}\n"
						"inline $base* $derived\b_As_$base($derived* p) { return ($base*) p; }\n",
						vars0,
						sizeof(vars0) / sizeof(vars0[0]),
						options->IdentationLevel);
				}

				StrBuilder_Destroy(&idnamelocal);
			}
		}
		Map2_Destroy(&map);
		StrBuilder_Destroy(&idname);

	}
	
	//for (int i = 0; i < p->Declarations.Size; i++)
	//{
	  //TAnyDeclaration_CodePrint(program, options, p->Declarations.pItems[i], fp);
	//}
	//TNodeClueList_CodePrint(options, &p->ClueList1, fp);
	Output_Append(fp, options, "#pragma endregion cprime\n");
}

static void TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, StrBuilder* fp)
{
	switch (pDeclaration->Type)
	{
	case TGroupDeclaration_ID:
		TGroupDeclaration_CodePrint(program, options, (TGroupDeclaration*)pDeclaration, fp);
		break;

	case TEofDeclaration_ID:
		TEofDeclaration_CodePrint(program, options, (TEofDeclaration*)pDeclaration, fp);
		break;

	case TStaticAssertDeclaration_ID:
		TStaticAssertDeclaration_CodePrint(program, options, (TStaticAssertDeclaration*)pDeclaration, fp);
		break;

	case TDeclaration_ID:
		TDeclaration_CodePrint(program, options, (TDeclaration*)pDeclaration, fp);
		break;

	default:
		ASSERT(false);
		break;
	}


}

static void TDesignatorList_CodePrint(TProgram* program, Options * options, TDesignatorList *p, StrBuilder* fp)
{



	ForEachListItem(TDesignator, pItem, p)
	{
		if (!List_IsFirstItem(p, pItem))
		{
			Output_Append(fp, options, ",");
		}
		TDesignator_CodePrint(program, options, pItem, fp);
	}



}


static void TInitializerListItem_CodePrint(TProgram* program,
	Options * options,
	TDeclarator* pDeclarator,
	TDeclarationSpecifiers* pDeclarationSpecifiers,
	TInitializerListItem* p,

	StrBuilder* fp)
{
	if (p->DesignatorList.pHead != NULL)
	{
		TDesignatorList_CodePrint(program, options, &p->DesignatorList, fp);
	}

	TInitializer_CodePrint(program,
		options,
		pDeclarator,
		pDeclarationSpecifiers,
		p->pInitializer,
		fp);
}



void TProgram_PrintCodeToFile(TProgram* pProgram,
	Options* options,
	const char* outFileName,
	const char* inputFileName)
{
	FILE * fp = fopen(outFileName, "w");

	if (fp == NULL)
	{
		printf("cannot open output file %s", outFileName);
		return;
	}



	int k = 0;

	//for (int i = 0; i < pProgram->Files2.size; i++)
	//{
	//  TFile *pFile = pProgram->Files2.pItems[i];
	//  printf("\"%s\"\n", pFile->FullPath);
	//}

	StrBuilder sb = STRBUILDER_INIT;
	StrBuilder_Reserve(&sb, 80 * 5000);

	for (int i = 0; i < pProgram->Declarations.Size; i++)
	{
		TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];

		StrBuilder_Clear(&pProgram->sbPreDeclaration);

		StrBuilder sbDeclaration = STRBUILDER_INIT;
		TAnyDeclaration_CodePrint(pProgram, options, pItem, &sbDeclaration);

		StrBuilder_Append(&sb, pProgram->sbPreDeclaration.c_str);
		StrBuilder_Append(&sb, sbDeclaration.c_str);

		StrBuilder_Destroy(&sbDeclaration);


		fprintf(fp, "%s", sb.c_str);


		StrBuilder_Clear(&sb);
		k++;
	}
	StrBuilder_Destroy(&sb);
	fclose(fp);
}

void TProgram_PrintCodeToString(TProgram* pProgram,
  Options* options,
  StrBuilder* output)
{
  
  int k = 0;

  
  StrBuilder sb = STRBUILDER_INIT;
  StrBuilder_Reserve(&sb, 80 * 5000);

  for (int i = 0; i < pProgram->Declarations.Size; i++)
  {
    TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];

    StrBuilder_Clear(&pProgram->sbPreDeclaration);

    StrBuilder sbDeclaration = STRBUILDER_INIT;
    TAnyDeclaration_CodePrint(pProgram, options, pItem, &sbDeclaration);

    StrBuilder_Append(&sb, pProgram->sbPreDeclaration.c_str);
    StrBuilder_Append(&sb, sbDeclaration.c_str);

    StrBuilder_Destroy(&sbDeclaration);

    StrBuilder_Append(output, sb.c_str);


    StrBuilder_Clear(&sb);
    k++;
  }
  StrBuilder_Destroy(&sb);

}


static const char* GetFreeStr(TProgram* program)
{
	TDeclaration* pDeclarationDestroy =
		SymbolMap_FindFunction(&program->GlobalScope,
			"Free");

	return pDeclarationDestroy ? "Free" : "free";
}

static const char* GetMallocStr(TProgram* program)
{
	TDeclaration* pDeclarationDestroy =
		SymbolMap_FindFunction(&program->GlobalScope,
			"Malloc");

	return pDeclarationDestroy ? "Malloc" : "malloc";
}


static const char* GetFalseStr(TProgram* program)
{
	bool bHasFalse =
		MacroMap_Find(&program->Defines, "false") != NULL;

	return bHasFalse ? "false" : "0";
}

static const char* GetNullStr(TProgram* program)
{
	bool bHasFalse =
		MacroMap_Find(&program->Defines, "NULL") != NULL;

	return bHasFalse ? "NULL" : "0";
}



static void PrintIfNotNullLn(TProgram* program,
	Options* options,
	const char* pInitExpressionText, //(x->p->i = 0)    
	StrBuilder* fp)
{
	bool bHasNULL =
		MacroMap_Find(&program->Defines, "NULL") != NULL;

	if (bHasNULL)
	{
		StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
			"if (%s != NULL)",
			pInitExpressionText);
	}
	else
	{
		StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
			"if (%s)",
			pInitExpressionText);
	}
}


static bool FindHighLevelFunction(TProgram* program,
	Options* options,
	TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
	TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
	TParameterTypeList * pArgsOpt, //parametros do create /init
	TInitializer* pInitializerOpt,
	const char* pInitExpressionText, //(x->p->i = 0)    
	const char* pszAutoPointerLenExpressionOpt,
	const Action action,
	Search search,
	const char* nameToFind,
	StrBuilder* fp)
{
	if (nameToFind == NULL)
	{
		//pode ser null struct sem nome
		return false;
	}




	bool bComplete = false;

	//TPointerList_Printf(&pDeclatator->PointerList);

	//TODO FAZER FLAGS e OLHAR P TIPO E DECLARATOR AMBOS
	bool bIsPointerToObject = TPointerList_IsPointerToObject(&pDeclatator->PointerList);
	bool bIsAutoPointerToObject = TPointerList_IsAutoPointerToObject(&pDeclatator->PointerList);
	bool bIsAutoPointerToAutoPointer = TPointerList_IsAutoPointerToAutoPointer(&pDeclatator->PointerList);
	bool bIsAutoPointerToPointer = TPointerList_IsAutoPointerToPointer(&pDeclatator->PointerList);
	bool bIsPointer = TPointerList_IsPointer(&pDeclatator->PointerList);
	bool bIsAutoPointerSizeToObject = TPointerList_IsAutoPointerSizeToObject(&pDeclatator->PointerList);

	if (action == ActionDestroy || action == ActionDestroyContent)
	{
		if (bIsPointer)
		{
			if (bIsAutoPointerSizeToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
			{
				//nao procurar delete bIsAutoPointerSizeToObject
				//nao eh ponteiro
				if (search == SearchAll ||
					search == SearchDelete)
				{
					//vamos procurar pela funcao conceito _Delete
					TDeclaration* pDeclarationDestroy =
						SymbolMap_FindObjFunction(&program->GlobalScope,
							nameToFind,
							"Delete");
					if (pDeclarationDestroy)
					{
						if (bIsAutoPointerToObject)
						{
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
								"%s_Delete(%s);",
								nameToFind,
								pInitExpressionText);
							bComplete = true;
						}
						else if (bIsAutoPointerToAutoPointer)
						{

							if (pszAutoPointerLenExpressionOpt)
							{
								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

								options->IdentationLevel++;

								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
									"%s_Delete(%s[i]);",
									nameToFind,
									pInitExpressionText);

								options->IdentationLevel--;
								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
									"%s((void*)%s);",
									GetFreeStr(program),
									pInitExpressionText);
							}
							else
							{
								//1 auto pointer para 1 autopointer
								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
									"%s_Delete(%s[0]);",
									nameToFind,
									pInitExpressionText);

								StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
									"%s((void*)%s);",
									GetFreeStr(program),
									pInitExpressionText);
							}

							bComplete = true;
						}
					}
					else
					{
						if (search == SearchAll ||
							search == SearchDestroy)
						{
							//se nao achou delete procura a destroy 
							//e depois chama free
							TDeclaration* pDeclarationDestroy2 =
								SymbolMap_FindObjFunction(&program->GlobalScope,
									nameToFind,
									"Destroy");
							if (pDeclarationDestroy2)
							{
								if (bIsAutoPointerToObject)
								{
									StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
										"%s_Destroy(%s);",
										nameToFind,
										pInitExpressionText);

									StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
										"%s((void*)%s);",
										GetFreeStr(program),
										pInitExpressionText);
								}
								else if (bIsAutoPointerToAutoPointer)
								{
									if (pszAutoPointerLenExpressionOpt)
									{
										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

										options->IdentationLevel++;

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s_Destroy(%s[i]);",
											nameToFind,
											pInitExpressionText);

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s((void*)%s[i]);",
											GetFreeStr(program),
											pInitExpressionText);

										options->IdentationLevel--;
										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s((void*)%s);",
											GetFreeStr(program),
											pInitExpressionText);
									}
									else
									{
										//1 auto pointer para 1 auto pointer

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s_Destroy(%s[0]);",
											nameToFind,
											pInitExpressionText);

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s((void*)%s[0]);",
											GetFreeStr(program),
											pInitExpressionText);

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s((void*)%s);",
											GetFreeStr(program),
											pInitExpressionText);
									}

								}
								else if (bIsAutoPointerSizeToObject)
								{
									if (pszAutoPointerLenExpressionOpt)
									{
										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

										options->IdentationLevel++;

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s_Destroy(%s[i]);",
											nameToFind,
											pInitExpressionText);

										// StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
										//   "free((void*)%s[i]);",
										// pInitExpressionText);

										options->IdentationLevel--;
										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s((void*)%s);",
											GetFreeStr(program),
											pInitExpressionText);
									}
									else
									{
										//1 auto pointer para 1 auto pointer

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s_Destroy(%s[0]);",
											nameToFind,
											pInitExpressionText);

										// StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
										//   "free((void*)%s[0]);",
										//   pInitExpressionText);

										StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
											"%s((void*)%s);",
											GetFreeStr(program),
											pInitExpressionText);
									}
								}

								bComplete = true;
							}
						}
					}
				}
			}
			else if (bIsAutoPointerToPointer)
			{
				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
					"%s((void*)%s);",
					GetFreeStr(program),
					pInitExpressionText);

				//nada
				bComplete = true;
			}
			else
			{
				if (action != ActionDestroyContent)
				{
					//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = NULL;", pInitExpressionText);
					bComplete = true;
				}
			}

		}
		else
		{
			//nao eh ponteiro
			if (!bIsAutoPointerToPointer)
			{
				if (search == SearchAll ||
					search == SearchDestroy)
				{
					//vamos procurar pela funcao conceito _Destroy
					TDeclaration* pDeclarationDestroy =
						SymbolMap_FindObjFunction(&program->GlobalScope,
							nameToFind,
							"Destroy");
					if (pDeclarationDestroy)
					{
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
							"%s_Destroy(&%s);",
							nameToFind,
							pInitExpressionText);
						bComplete = true;
					}
				}
			}

		}
	}
	else if (action == ActionDelete)
	{
		//nao eh ponteiro
		if (search == SearchAll ||
			search == SearchDelete)
		{
			//vamos procurar pela funcao conceito _Delete
			TDeclaration* pDeclarationDestroy =
				SymbolMap_FindObjFunction(&program->GlobalScope,
					nameToFind,
					"Delete");
			if (pDeclarationDestroy)
			{
				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
					"%s_Delete(%s);",
					nameToFind,
					pInitExpressionText);
				bComplete = true;
			}
			else
			{
				if (search == SearchAll ||
					search == SearchDestroy)
				{
					//se nao achou delete procura a destroy 
					//e depois chama free
					TDeclaration* pDeclarationDestroy2 =
						SymbolMap_FindObjFunction(&program->GlobalScope,
							nameToFind,
							"Destroy");
					if (pDeclarationDestroy2)
					{
						StrBuilder_AppendFmtLn(fp, 4 * 1,
							"%s_Destroy(%s);",
							nameToFind,
							pInitExpressionText);

						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
							"%s((void*)%s);",
							GetFreeStr(program),
							pInitExpressionText);
						bComplete = true;
					}
				}

			}
		}
		else
		{
			//nao procurar pela delete mas procurar pela destroy
			//posso procurar pela destroy
			//se nao achou delete procura a destroy 
			//e depois chama free
			if (search == SearchAll ||
				search == SearchDestroy)
			{
				TDeclaration* pDeclarationDestroy =
					SymbolMap_FindObjFunction(&program->GlobalScope,
						nameToFind,
						"Destroy");
				if (pDeclarationDestroy)
				{
					PrintIfNotNullLn(program, options, pInitExpressionText, fp);



					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"{");

					options->IdentationLevel++;
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"%s_Destroy(%s);",
						nameToFind,
						pInitExpressionText);
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"%s((void*)%s);",
						GetFreeStr(program),
						pInitExpressionText);
					options->IdentationLevel--;
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"}",
						pInitExpressionText);

					bComplete = true;
				}
			}

		}
	}
	else if (action == ActionInit)
	{
		if (bIsPointer)
		{
			StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
				"%s = %s;",
				pInitExpressionText,
				GetNullStr(program));
			bComplete = true;
		}
		else
		{
			if (search == SearchAll ||
				search == SearchInit)
			{
				TDeclaration* pDeclarationInit =
					SymbolMap_FindObjFunction(&program->GlobalScope,
						nameToFind,
						"Init");
				if (pDeclarationInit)
				{
					StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
						"%s_Init(&%s",
						nameToFind,
						pInitExpressionText);

					TParameterTypeList_GetArgsString(pArgsOpt, fp);

					StrBuilder_Append(fp, ");\n");

					bComplete = true;
				}
			}

		}
	}
	else if (action == ActionInitContent)
	{
		if (search == SearchAll ||
			search == SearchInit)
		{
			TDeclaration* pDeclarationInit =
				SymbolMap_FindObjFunction(&program->GlobalScope,
					nameToFind,
					"Init");
			if (pDeclarationInit)
			{

				if (bIsPointer)
				{
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"%s_Init(%s);",
						nameToFind,
						pInitExpressionText);
				}
				else
				{
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"%s_Init(&%s);",
						nameToFind,
						pInitExpressionText);
				}
				bComplete = true;
			}

		}
	}
	else if (action == ActionCreate)
	{
		if (search == SearchAll ||
			search == SearchInit)
		{
			TDeclaration* pDeclarationInit =
				SymbolMap_FindObjFunction(&program->GlobalScope,
					nameToFind,
					"Init");
			if (pDeclarationInit)
			{
				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
					"struct %s *p = (struct %s *) %s(sizeof * p);",
					nameToFind,
					nameToFind,
					GetMallocStr(program));


				PrintIfNotNullLn(program, options, "p", fp);


				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
					"{");
				options->IdentationLevel++;

				StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
					"%s_Init(p",
					nameToFind);

				if (TParameterTypeList_HasNamedArgs(pArgsOpt))
				{
					StrBuilder_Append(fp, ", ");
					TParameterTypeList_GetArgsString(pArgsOpt, fp);
				}

				StrBuilder_Append(fp, ");\n");


				options->IdentationLevel--;

				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
					"}");

				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
					"return p;");

				bComplete = true;
			}

		}
	}
	else if (action == ActionStaticInit)
	{
		if (pInitializerOpt)
		{
			StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "/*%s=*/", pInitExpressionText);
			Options options2 = *options;
			TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);

		}
		else if (bIsPointer)
		{
			StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
			bComplete = true;
		}


	}
	return bComplete;
}


//Verifica se tem "cara" de ser o vector
static bool IsVector(TStructUnionSpecifier* pStructUnionSpecifier)
{
	bool bHasVector = false;
	bool bHasSize = false;
	bool bHasCapacity = false;

	if (pStructUnionSpecifier)
	{
		//Vou analisar a "digital" da struct
		//ok tem a definicao completa da struct
		for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
		{
			TAnyStructDeclaration* pAnyStructDeclaration =
				pStructUnionSpecifier->StructDeclarationList.pItems[i];

			TStructDeclaration* pStructDeclaration =
				TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
			if (pStructDeclaration)
			{
				TStructDeclarator* pStructDeclarator =
					pStructDeclaration->DeclaratorList.pHead;

				while (pStructDeclarator)
				{
					const char* structDeclaratorName =
						TDeclarator_GetName(pStructDeclarator->pDeclarator);

					bool bIsPointer1 =
						TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

					if (bIsPointer1)
					{
						bHasVector = true;
					}
					else  if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
					{
						if (strcmp(structDeclaratorName, "Size") == 0)
						{
							bHasSize = true;
						}
						else if (strcmp(structDeclaratorName, "Capacity") == 0)
						{
							bHasCapacity = true;
						}
					}

					pStructDeclarator = (pStructDeclarator)->pNext;
				}
			}
		}
	}

	return bHasSize && bHasCapacity && bHasVector;
}

void UnionTypeDefault(TProgram* program,
	Options* options,
	const char* structName,
	TParameterTypeList * pArgsOpt, //parametros
	const char* parameterName0,
	const char* functionSuffix,
	StrBuilder* fp)
{
	Map2 map = MAPSTRINGTOPTR_INIT;
	FindUnionSetOf(program, structName, &map);

	StrBuilder strid = STRBUILDER_INIT;
	FindRuntimeID(program, structName, &strid);

	StrBuilder args = STRBUILDER_INIT;

	if (pArgsOpt != NULL)
	{
		//lista argumentos separados por virgula
		TParameterTypeList_GetArgsString(pArgsOpt, &args);
	}
	else
	{
		StrBuilder_Append(&args, parameterName0);
	}

	struct TemplateVar vars0[] = {
		{ "p", parameterName0 },
	{ "id", strid.c_str }
	};

	StrBuilder_Template(fp,
		"switch ($p->$id)\n"
		"{\n",
		vars0,
		sizeof(vars0) / sizeof(vars0[0]),
		options->IdentationLevel);

	StrBuilder_Destroy(&strid);

	for (int i = 0; i < (int)map.nHashTableSize; i++)
	{
		if (map.pHashTable[i])
		{
			StrBuilder idvalue = STRBUILDER_INIT;

			FindIDValue(program,
				(const char*)map.pHashTable[i]->Key,
				&idvalue);

			struct TemplateVar vars[] = {
			{ "type", (const char*)map.pHashTable[i]->Key },
			{ "suffix", functionSuffix },
			{ "value", idvalue.c_str },
	  { "args", args.c_str }
			};
			if ((int)map.pHashTable[i]->pValue == 2)
			{
				//2 is struct
				StrBuilder_Template(fp,
					" case $value:\n"
					"  $type\b_$suffix((struct $type*)$args);\n"
					" break;\n",
					vars,
					sizeof(vars) / sizeof(vars[0]),
					options->IdentationLevel);
			}
			else
			{
				//1 is typedef
				StrBuilder_Template(fp,
					" case $value:\n"
					"  $type\b_$suffix(($type*)$args);\n"
					" break;\n",
					vars,
					sizeof(vars) / sizeof(vars[0]),
					options->IdentationLevel);
			}
			StrBuilder_Destroy(&idvalue);
		}
	}

	StrBuilder_Template(fp,
		" default:\n"
		" break;\n"
		"}\n",
		NULL,
		0,
		options->IdentationLevel);

	StrBuilder_Destroy(&args);

	Map2_Destroy(&map);
}

void InstanciateDestroy2(TProgram* program,
	Options* options,
	TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
	TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
	TInitializer* pInitializerOpt, //usado para inicializacao estatica
	TParameterTypeList * pArgsOpt, //parametros do create /init
	const char* pInitExpressionText, //(x->p->i = 0)    
	const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
												//se passar null eh pq nao interessa
	const Action action,
	Search search,
	bool* pbHasInitializers,
	StrBuilder* fp)
{
	if (pInitializerOpt && pbHasInitializers)
	{
		*pbHasInitializers = true;
	}


	bool bIsPointerToObject = TPointerList_IsPointerToObject(&pDeclatator->PointerList);
	bool bIsAutoPointerToObject = TPointerList_IsAutoPointerToObject(&pDeclatator->PointerList);
	bool bIsAutoPointerToAutoPointer = TPointerList_IsAutoPointerToAutoPointer(&pDeclatator->PointerList);
	bool bIsAutoPointerToPointer = TPointerList_IsAutoPointerToPointer(&pDeclatator->PointerList);
	bool bIsPointer = TPointerList_IsPointer(&pDeclatator->PointerList);

	TDeclarationSpecifier* pMainSpecifier =
		TSpecifierQualifierList_GetMainSpecifier(pSpecifierQualifierList);

	if (pMainSpecifier == NULL)
	{
		//error
		return;
	}

	if (pMainSpecifier->Type == TSingleTypeSpecifier_ID)
	{
		TSingleTypeSpecifier* pSingleTypeSpecifier =
			(TSingleTypeSpecifier*)pMainSpecifier;

		if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
		{
			bool bComplete = false;
			TDeclarator declarator;
			TDeclarator_Init(&declarator);
			//Pode ter uma cadeia de typdefs
			//ele vai entrandando em cada uma ...
			//ate que chega no fim recursivamente
			//enquanto ele vai andando ele vai tentando
			//algo com o nome do typedef
			TDeclarationSpecifiers* pDeclarationSpecifiers =
				SymbolMap_FindTypedefFirstTarget(&program->GlobalScope,
					pSingleTypeSpecifier->TypedefName,
					&declarator);
			if (pDeclarationSpecifiers)
			{
				ForEachListItem(TPointer, pItem, &pDeclatator->PointerList)
				{
					TPointer * pNew = TPointer_Create();
					TPointer_Copy(pNew, pItem);
					TPointerList_PushBack(&declarator.PointerList, pNew);
				}

				//TPointerList_Printf(&declarator.PointerList);

				if (action == ActionCreate)
				{
					//create do typedef eh um pouco difernet
					//das outras

					//vou deixar o malloc aqui fora
					//existe typedef p struct sem nome
					//entao queremos usar o nome do typedef
					//typedef struct { int i; } X; X* X_Create();
					//para poder fazer 
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"%s *p = (%s*) %s(sizeof * p);",
						pSingleTypeSpecifier->TypedefName,
						pSingleTypeSpecifier->TypedefName,
						GetMallocStr(program));

					PrintIfNotNullLn(program, options, "p", fp);

					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"{");

					options->IdentationLevel++;

					/////////////////
					//vou ver se tem init para typedef

					TDeclaration* pDeclarationInit =
						SymbolMap_FindObjFunction(&program->GlobalScope,
							pSingleTypeSpecifier->TypedefName,
							"Init");

					if (pDeclarationInit)
					{
						StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
							"%s_Init(p",
							pSingleTypeSpecifier->TypedefName);

						if (TParameterTypeList_HasNamedArgs(pArgsOpt))
						{
							StrBuilder_Append(fp, ", ");
							TParameterTypeList_GetArgsString(pArgsOpt, fp);
						}

						StrBuilder_Append(fp, ");\n");

						bComplete = true;
					}
					////////////////


					if (!bComplete)
					{

						//passa a informacao do tipo correto agora
						InstanciateDestroy2(program,
							options,
							(TSpecifierQualifierList*)pDeclarationSpecifiers,
							&declarator,
							NULL,
							pArgsOpt,
							"p",
							NULL /*not used*/,
							ActionInitContent,
							SearchNone, //se tivesse init ja tinha achado
							pbHasInitializers,
							fp);
					}

					options->IdentationLevel--;
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"}");

					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"return p;");

				}
				else
				{
					bComplete = FindHighLevelFunction(program,
						options,
						pSpecifierQualifierList,//<-dupla para entender o tipo
						pDeclatator,                        //<-dupla para entender o tipo
						pArgsOpt, //parametros do create /init
						pInitializerOpt,
						pInitExpressionText, //(x->p->i = 0)    
						pszAutoPointerLenExpressionOpt,
						action,
						search,
						pSingleTypeSpecifier->TypedefName,
						fp);


					if (!bComplete)
					{
						Action action2 = action;

						//passa a informacao do tipo correto agora
						InstanciateDestroy2(program,
							options,
							(TSpecifierQualifierList*)pDeclarationSpecifiers,
							&declarator,
							pInitializerOpt,
							pArgsOpt,
							pInitExpressionText,
							pszAutoPointerLenExpressionOpt,
							action2,
							search,
							pbHasInitializers,
							fp);
					}
				}

				TDeclarator_Destroy(&declarator);
			}
			else
			{
				//nao achou a declaracao
				ASSERT(false);
			}

		}
		else
		{
			//nao eh typedef, deve ser int, double etc..
			if (action == ActionDestroy)
			{
				if (bIsAutoPointerToObject)
				{
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
				}
				else if (bIsAutoPointerToAutoPointer)
				{
					if (pszAutoPointerLenExpressionOpt)
					{
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

						options->IdentationLevel++;
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s[i]);", GetFreeStr(program), pInitExpressionText);
						options->IdentationLevel--;
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
					}
					else
					{
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s[0]);", GetFreeStr(program), pInitExpressionText);
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
					}

					//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
				}
				else
				{
					//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = 0;", pInitExpressionText);
				}
			}
			else if (action == ActionInit)
			{
				if (pInitializerOpt)
				{
					StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
					Options options2 = *options;
					TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
					StrBuilder_Append(fp, ";\n");
				}
				else
				{


					if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
					{
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetNullStr(program));
					}
					else
					{
						if (TSpecifierQualifierList_IsBool(pSpecifierQualifierList))
						{
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetFalseStr(program));
						}
						else
						{
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = 0;", pInitExpressionText);
						}

					}
				}
			}
			else if (action == ActionStaticInit)
			{
				if (pInitializerOpt)
				{
					StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "/*%s=*/", pInitExpressionText);
					Options options2 = *options;
					TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
				}
				else
				{
					if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
					{
						StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
					}
					else
					{
						StrBuilder_AppendFmt(fp, "/*%s=*/0", pInitExpressionText);
					}
				}
			}
		}
	}
	else if (pMainSpecifier->Type == TStructUnionSpecifier_ID)
	{
		TStructUnionSpecifier* pStructUnionSpecifier =
			(TStructUnionSpecifier*)pMainSpecifier;

		//Indica se consegui fazer sem entrar na struct
		bool bComplete = false;


		bComplete = FindHighLevelFunction(program,
			options,
			pSpecifierQualifierList,//<-dupla para entender o tipo
			pDeclatator,                        //<-dupla para entender o tipo
			pArgsOpt,
			pInitializerOpt,
			pInitExpressionText, //(x->p->i = 0)    
			pszAutoPointerLenExpressionOpt,
			action,
			search,
			pStructUnionSpecifier->Name,
			fp);

		//Exemplos
		//struct Y *pY e é para destruir o conteudo
		//struct Y *pY e NAO é para destruir o conteudo
		//struct Y * auto pY; e é para destruir o conteudo ou nao
		//struct Y y; //eh para destruir o conteudo
		if (!bComplete) //se for para entrar na struct
		{
			if (pStructUnionSpecifier &&
				pStructUnionSpecifier->Name != NULL)
			{
				//se nao eh completa tenta achar
				//vou procurar a definicao completa da struct
				pStructUnionSpecifier =
					SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
			}

			bool bIsUnionTypes = pStructUnionSpecifier &&
				pStructUnionSpecifier->Token2 == TK__UNION;


			if (pStructUnionSpecifier &&
				pStructUnionSpecifier->StructDeclarationList.Size > 0)
			{
				if (action == ActionDelete)
				{
					PrintIfNotNullLn(program, options, pInitExpressionText, fp);
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{", pInitExpressionText);
					options->IdentationLevel++;
				}
				else if (action == ActionDestroy)
				{
					if (bIsAutoPointerToObject)
					{
						PrintIfNotNullLn(program, options, pInitExpressionText, fp);
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
						options->IdentationLevel++;
					}
					else if (bIsAutoPointerToAutoPointer)
					{

						PrintIfNotNullLn(program, options, pInitExpressionText, fp);
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
						options->IdentationLevel++;

						if (pszAutoPointerLenExpressionOpt)
						{
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
							options->IdentationLevel++;
						}
						else
						{
							//ASSERT(false);
						}

					}

				}
				else if (action == ActionCreate)
				{
					//struct sem nome tem que ser criada
					//com typedef que chama outro codigo
					ASSERT(pStructUnionSpecifier->Name != NULL);

					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"struct %s* p = (struct %s*) %s(sizeof * p);",
						pStructUnionSpecifier->Name,
						pStructUnionSpecifier->Name,
						GetMallocStr(program));

					PrintIfNotNullLn(program, options, pInitExpressionText, fp);
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"{");
					options->IdentationLevel++;
				}
				else if (action == ActionStaticInit)
				{
					//if (bCanApplyFunction)
					//{
					//o primeiro nao precisa do {

					//  StrBuilder_AppendFmt(fp, "/*%s=*/{", pInitExpressionText);
					//}
				}

				if (bIsUnionTypes)
				{
					if (action == ActionDelete)
					{
						options->IdentationLevel++;
						UnionTypeDefault(program,
							options,
							pStructUnionSpecifier->Name,
							NULL, /*args*/
							pInitExpressionText,
							"Delete",
							fp);
						options->IdentationLevel--;
					}
					else if (action == ActionDestroyContent ||
						action == ActionDestroy)
					{
						options->IdentationLevel++;
						UnionTypeDefault(program,
							options,
							pStructUnionSpecifier->Name,
							NULL, /*args*/
							pInitExpressionText,
							"Destroy",
							fp);
						options->IdentationLevel--;
					}
					else
					{

					}
				}
				else
				{
					//ok tem a definicao completa da struct
					for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
					{



						if (action == ActionStaticInit && i > 0)
						{
							StrBuilder_Append(fp, ", ");
						}

						TAnyStructDeclaration* pAnyStructDeclaration =
							pStructUnionSpecifier->StructDeclarationList.pItems[i];

						TStructDeclaration* pStructDeclaration =
							TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

						if (pStructDeclaration != NULL)
						{
							TStructDeclarator* pStructDeclarator =
								pStructDeclaration->DeclaratorList.pHead;

							StrBuilder strVariableName = STRBUILDER_INIT;
							StrBuilder strPonterSizeExpr = STRBUILDER_INIT;


							while (pStructDeclarator)
							{
								//O padrao eh ser o inicializador do tipo
								TInitializer* pStructMemberInitializer =
									pStructDeclarator->pInitializer;

								TPrimaryExpressionValue initializerExpression;
								TPrimaryExpressionValue_Init(&initializerExpression);


								StrBuilder_Clear(&strVariableName);
								StrBuilder_Clear(&strPonterSizeExpr);

								const char* structDeclaratorName =
									TDeclarator_GetName(pStructDeclarator->pDeclarator);
								if (action != ActionStaticInit)
								{
									if (pInitExpressionText)
										StrBuilder_Set(&strVariableName, pInitExpressionText);


									if (bIsAutoPointerToAutoPointer)
									{
										if (pszAutoPointerLenExpressionOpt)
										{
											StrBuilder_Append(&strVariableName, "[i]");
										}
										else
										{
											StrBuilder_Append(&strVariableName, "[0]");
										}
									}

									if (bIsPointer)
									{
										StrBuilder_Append(&strVariableName, "->");
									}
									else
									{
										StrBuilder_Append(&strVariableName, ".");
									}
								}
								else
								{
									StrBuilder_Append(&strVariableName, ".");
								}

								StrBuilder_Append(&strVariableName, structDeclaratorName);


								Action action2 = action;
								if (action == ActionDestroyContent ||
									action == ActionDelete)
								{
									//destroy normal
									action2 = ActionDestroy;
								}
								else if (action == ActionInitContent)
								{

									TParameter* pParameter = NULL;
									if (pArgsOpt)
									{
										pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
										if (pParameter != NULL)
										{
											pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
											initializerExpression.token = TK_IDENTIFIER;
											String_Set(&initializerExpression.lexeme, structDeclaratorName);
										}
									}

									action2 = ActionInit;
								}
								else if (action == ActionCreate)
								{
									TParameter* pParameter = NULL;
									if (pArgsOpt)
									{
										pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
										if (pParameter != NULL)
										{
											pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
											initializerExpression.token = TK_IDENTIFIER;
											String_Set(&initializerExpression.lexeme, structDeclaratorName);
										}
									}

									action2 = ActionInit;
								}

								if (action2 == ActionDestroy)
								{

									//Tem que detectar isso aqui!
									// String * _auto pItems;
									// X * _auto * _auto pItems;
									//sef or ele vai precisar da informacao do _size
									// X * _auto * _auto _size(Size) pItems;
									//e dai ele passa a string para  funcao gerar


									const char * pszSize =
										TPointerList_GetSize(&pStructDeclarator->pDeclarator->PointerList);
									if (pszSize)
									{
										if (pInitExpressionText)
											StrBuilder_Set(&strPonterSizeExpr, pInitExpressionText);

										if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
										{
											StrBuilder_Append(&strPonterSizeExpr, "->");
										}
										else
										{
											StrBuilder_Append(&strPonterSizeExpr, ".");
										}
										StrBuilder_Append(&strPonterSizeExpr, pszSize);
									}
									else
									{
										//nao tem size
									}
								}

								//Se for destroy e sor 
								InstanciateDestroy2(program,
									options,
									&pStructDeclaration->SpecifierQualifierList,
									pStructDeclarator->pDeclarator,
									pStructMemberInitializer,
									NULL, //nao passa os args
									strVariableName.c_str,
									strPonterSizeExpr.c_str,
									action2,
									SearchAll,
									pbHasInitializers,
									fp);



								//Variavel local
								TPrimaryExpressionValue_Destroy(&initializerExpression);

								pStructDeclarator = (pStructDeclarator)->pNext;
							}

							StrBuilder_Destroy(&strVariableName);
							StrBuilder_Destroy(&strPonterSizeExpr);

						}
					}
				}

				if (action == ActionDestroy)
				{
					if (bIsAutoPointerToObject)
					{
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
						options->IdentationLevel--;
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

					}
					else if (bIsAutoPointerToAutoPointer)
					{
						if (pszAutoPointerLenExpressionOpt)
						{
							options->IdentationLevel--;
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); //fecha  for
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
							options->IdentationLevel--;
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
						}
						else
						{
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
							options->IdentationLevel--;
							StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
						}


						//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
					}
				}
				else if (action == ActionDestroyContent)
				{
					if (bIsAutoPointerToAutoPointer)
					{
						//    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
						//  options->IdentationLevel--;
						//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
						//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
					}
				}
				else if (action == ActionDelete)
				{
					if (bIsUnionTypes)
					{

					}
					else
					{
						StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
					}
					options->IdentationLevel--;
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

				}
				else if (action == ActionCreate)
				{
					options->IdentationLevel--;
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"}");

					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
						"return p;");
				}
				else if (action == ActionStaticInit)
				{
					//if (bCanApplyFunction)
					//{
					//  //o primeiro nao tem 
					//StrBuilder_Append(fp, "}");
					//}
				}
			}
			else
			{
				//error nao tem a definicao completa da struct
				StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
			}
		}//complete

	}
	else if (pMainSpecifier->Type == TEnumSpecifier_ID)
	{
		TEnumSpecifier *pEnumSpecifier =
			TDeclarationSpecifier_As_TEnumSpecifier(pMainSpecifier);


		//nao eh typedef, deve ser int, double etc..
		if (action == ActionDestroy)
		{
			if (bIsAutoPointerToObject)
			{
				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
			}
			else if (bIsAutoPointerToAutoPointer)
			{
				ASSERT(false);
				StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
			}
			else
			{
				//StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = 0;", pInitExpressionText);
			}
		}
		else if (action == ActionInit)
		{
			if (pInitializerOpt)
			{
				StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
				Options options2 = *options;
				TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
				StrBuilder_Append(fp, ";\n");
			}
			else
			{
				//TODO achar a definicao completa do enum
				const char* firstValue =
					pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
					"0";

				if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
				{
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetNullStr(program));
				}
				else
				{
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, firstValue);
				}
			}

		}
		else if (action == ActionInitContent)
		{
			if (pInitializerOpt)
			{
				StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
				Options options2 = *options;
				TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
				StrBuilder_Append(fp, ";");
			}
			else
			{
				//TODO achar a definicao completa do enum
				const char* firstValue =
					pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
					"0";

				if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
				{
					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "*%s = %s;", pInitExpressionText, GetNullStr(program));
				}
				else
				{

					StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, firstValue);
				}
			}
		}
		else if (action == ActionStaticInit)
		{
			if (pInitializerOpt)
			{
				StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
				Options options2 = *options;
				TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
			}
			else
			{
				//TODO achar a definicao completa do enum
				const char* firstValue =
					pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
					"0";

				if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
				{
					StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
				}
				else
				{
					StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, firstValue);
				}
			}
		}
	}
	else
	{
		ASSERT(false);
	}

}



bool IsSuffix(const char* s, const char* suffix)
{
	bool bResult = false;
	int len = strlen(s);
	int len2 = strlen(suffix);
	if (len > len2)
	{
		const char* pEndPart = &s[len - len2];
		if (strcmp(pEndPart, suffix) == 0)
		{
			bResult = true;
		}
	}
	return bResult;

}

TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers)
{
	if (specifiers == NULL)
		return NULL;

	TStructUnionSpecifier* pTStructUnionSpecifier =
		TDeclarationSpecifier_As_TStructUnionSpecifier(specifiers->pData[0]);

	if (pTStructUnionSpecifier == NULL)
	{
		TSingleTypeSpecifier *pSingleTypeSpecifier =
			TDeclarationSpecifier_As_TSingleTypeSpecifier(specifiers->pData[0]);

		if (pSingleTypeSpecifier != NULL &&
			pSingleTypeSpecifier->Token == TK_IDENTIFIER)
		{
			const char * typedefName = pSingleTypeSpecifier->TypedefName;

			TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
			if (pDeclaration)
			{
				if (pDeclaration->Specifiers.Size > 1)
				{
					pTStructUnionSpecifier =
						TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pData[1]);
				}
			}
		}
	}

	//Procura pela definicao completa da struct
	if (pTStructUnionSpecifier &&
		pTStructUnionSpecifier->Name != NULL)
	{
		pTStructUnionSpecifier =
			SymbolMap_FindStructUnion(&program->GlobalScope, pTStructUnionSpecifier->Name);
	}


	return pTStructUnionSpecifier;
}

