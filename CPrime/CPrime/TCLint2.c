#include "TCLint2.h"

#include "AstMatch.h"
#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


#if 0
typedef struct
{
  TParameterDeclaration *  pParameter;
  TDeclaration*  pDeclaration0;
  TDeclarator* pDeclarator0;

  int nUses;

  //
  //
  bool bIsOwner;
  bool bDestructorCalled;
  bool bMoved;
} TVariable;

#define TVARIABLE_INIT {NULL, NULL, NULL, 0, false, false, false}
TDeclarator* TVariable_GetDeclarator(TVariable *p)
{
  if (p->pParameter != NULL)
  {
    return &p->pParameter->Declarator;
  }

  return p->pDeclarator0;
}

TDeclarationSpecifiers* TVariable_GetSpecifiers(TVariable* p)
{
  if (p->pParameter != NULL)
  {
    return &p->pParameter->Specifiers;
  }

  return &p->pDeclaration0->Specifiers;
}

TSingleTypeSpecifier * TVariable_GetSingleSpecifier(TVariable* p)
{
  TDeclarationSpecifiers* pDeclarationSpecifiers =
    TVariable_GetSpecifiers(p);

  if (pDeclarationSpecifiers)
  {
    return TTypeSpecifier_As_TSingleTypeSpecifier(pDeclarationSpecifiers->pTypeSpecifierOpt);
  }

  return NULL;
}


TVariable* TVariable_Create()
{
  TVariable* p = (TVariable*)malloc(sizeof * p);

  if (p)
  {
    TVariable temp_Moved = TVARIABLE_INIT;
    *p =  temp_Moved;
  }

  return p;
}

void TVariable_Destroy(TVariable* p)
{
}

void TVariable_Delete(TVariable* p)
{
  if (p)
  {
    TVariable_Destroy(p);
    free(p);
  }
}

void TVariable_DeleteVoid(void* p)
{
  TVariable_Delete((TVariable*)p);
}


typedef Map TVariablesMap;

void TVariablesMap_Init(TVariablesMap* p)
{
  Map_Init(p, 100);
}

void TVariablesMap_Destroy(TVariablesMap* p)
{
  Map_Destroy(p, &TVariable_DeleteVoid);
}

void TVariablesMap_Add(TVariablesMap* p, const char* key, TVariable* pVariable)
{
  Map_Set(p, key, pVariable);
}

TVariable* TVariablesMap_Find(TVariablesMap* p, const char* key)
{
  return (TVariable*)Map_Find2(p, key);
}

static const char* GetTypedefName(TTypeSpecifier* pTypeSpecifier)
{
  const char* typeName = NULL;
  TSingleTypeSpecifier * pSingleTypeSpecifier =
    TTypeSpecifier_As_TSingleTypeSpecifier(pTypeSpecifier);

  if (pSingleTypeSpecifier &&
      pSingleTypeSpecifier->bIsTypeDef)
  {
    typeName = pSingleTypeSpecifier->TypedefName;
  }

  return typeName;
}

typedef Array TVariablesMapStack;
#define TVARIABLESMAPSTACK_INIT ARRAY_INIT
void TVariablesMapStack_Destroy(TVariablesMapStack* p)
{
  Array_Destroy(p, NULL);
}

void TVariablesMapStack_Push(TVariablesMapStack* p, TVariablesMap* pMap)
{
  Array_Push(p, (void*)pMap);
}

void TVariablesMapStack_Pop(TVariablesMapStack* p)
{
  Array_Pop(p, NULL);
}


static void TInitializerList_Analise(TProgram* pProgram,
                                     TDeclaration * pDeclaration,
                                     TDeclarator* pDeclarator,
                                     TInitializerList*p,
                                     TVariablesMapStack* pStackNames);

static void TDeclarator_Analise(TProgram* pProgram, TDeclaration* pDeclaration, TDeclarator* p, TVariablesMapStack* pStackNames);
static void TAnyDeclaration_Analise(TProgram* pProgram, TAnyDeclaration *pDeclaration);
static void TTypeSpecifier_Analise(TProgram* pProgram, TTypeSpecifier* p, TVariablesMapStack* pStackNames);
static void TAnyStructDeclaration_Analise(TProgram* pProgram, TAnyStructDeclaration* p, TVariablesMapStack* pStackNames);
static void TTypeQualifier_Analise(TProgram* pProgram, TTypeQualifier* p);
static void TDeclaration_Analise(TProgram* pProgram, TDeclaration* p, TVariablesMapStack* pStackNames);
static void TExpression_Analise(TProgram* pProgram, TExpression * p, const char* name, TVariablesMapStack* pStackNames);
static void TStatement_Analise(TProgram* pProgram, TStatement * p, TVariablesMapStack* pStackNames);
static void TBlockItem_Analise(TProgram* pProgram, TBlockItem * p, TVariablesMapStack* pStackNames);
static void TInitializer_Analise(TProgram* pProgram,
                                 TDeclaration * pDeclaration,
                                 TDeclarator* pDeclarator,
                                 TInitializer*  pInitializer,
                                 TVariablesMapStack* pStackNames);

static void TPointer_Analise(TProgram* pProgram, TPointer* pPointer);
static void TParameterDeclaration_Analise(TProgram* pProgram, TParameterDeclaration* p, TVariablesMapStack* pStackNames);

static void TInitializerListItem_Analise(TProgram* pProgram,
    TDeclaration * pDeclaration,
    TDeclarator* pDeclarator,
    TInitializerListItem* p,
    TVariablesMapStack* pStackNames);


static void TExpression_TypeOf(TProgram* pProgram,
                               TExpression *  p,
                               TVariablesMapStack* pStackNames,
                               TDeclarationSpecifiers** ppSpecifiers,
                               TDeclarator**ppDeclarator);


static bool IsDestructorDeclarator(TDeclarator *pDeclarator)
{
  bool bResult = false;

  for (size_t i = 0; i < pDeclarator->PointerList.size; i++)
  {
    if (pDeclarator->PointerList.pItems[i]->Qualifier.bIsDestructor)
    {
      bResult = true;
      break;
    }
  }

  return bResult;
}

static void CheckIfDestructorWasCalled(TProgram* pProgram, TVariablesMap* pDeclarationsMap);

static TVariable* TVariablesMapStack_FindVariable(TVariablesMapStack* pStackNames,
    const char* identifierName)
{
  TVariable* pResult = NULL;

  for (int k = pStackNames->size - 1; k >= 0; k--)
  {
    TVariablesMap* pDeclarationsMap = (TVariablesMap*)pStackNames->pItems[k];

    TVariable* pVariable =
      TVariablesMap_Find(pDeclarationsMap, identifierName);

    if (pVariable)
    {
      pResult = pVariable;
      break;
    }
  }

  return pResult;
}


static bool IsPointer(TDeclarator *pDeclarator)
{

  bool bIsPointer = false;


  for (size_t i = 0; i < pDeclarator->PointerList.size; i++)
  {
    if (pDeclarator->PointerList.pItems[i]->bPointer)
    {
      bIsPointer = true;
      break;
    }
  }

  return bIsPointer;
}

static bool IsNonNullPointer(TDeclarator *pDeclarator)
{

  bool bIsPointer = false;
  bool bIsPointerOpt = false;

  for (size_t i = 0; i < pDeclarator->PointerList.size; i++)
  {
    if (pDeclarator->PointerList.pItems[i]->Qualifier.bIsOpt)
    {
      bIsPointerOpt = true;
      break;
    }

    if (pDeclarator->PointerList.pItems[i]->bPointer)
    {
      bIsPointer = true;
    }
  }

  return bIsPointer && !bIsPointerOpt;
}



static void CheckIfDestructorWasCalled(TProgram *pProgram,
                                       TVariablesMap* pDeclarationsMap)
{
#if 0
  //Passar por cada variavel do escopo
  //ver se ela tem destructor
  //e ver se o destructor foi chamado

  for (size_t i = 0; i < pDeclarationsMap->buckets.size; i++)
  {
    Bucket*  data = pDeclarationsMap->buckets.data[i];

    if (data != NULL)
    {
      for (size_t k = 0; k < data->size; k++)
      {
        BucketItem* node = data->data[k];
        TVariable*  pVariable =
          (TVariable* )node->data;



        if (pVariable != NULL &&
            pVariable->bIsOwner)
        {

          if (!pVariable->bDestructorCalled &&
              !pVariable->bMoved)
          {
            TDeclarator* pDeclaratorLocal =
              TVariable_GetDeclarator(pVariable);
            printf("%s(%d): warning: destructor of %s was not called.\n", pProgram->Files2.pItems[pDeclaratorLocal->Position.FileIndex]->FullPath, pDeclaratorLocal->Position.Line, pDeclaratorLocal->Name);
          }

        }
      }
    }
  }
#endif
}

static bool IsTypedefWithDestructor(TProgram* pProgram,
                                    TTypeSpecifier*  pTypeSpecifier)
{
  bool bResult = false;
#if 0
  //Para saber se eh um tipo com destructor
  //eh preciso ver se o declarator do typedef foi
  //marcado como _dtor
  //
  

  TSingleTypeSpecifier *  pSingleTypeSpecifier =
    TTypeSpecifier_As_TSingleTypeSpecifier(pTypeSpecifier);

  if (pSingleTypeSpecifier != NULL &&
      pSingleTypeSpecifier->bIsTypeDef)
  {
    TDeclaration * pDeclaration2 =
      TProgram_FindDeclaration(pProgram, pSingleTypeSpecifier->TypedefName);

    if (pDeclaration2)
    {
      TDeclarator* pDeclaratorTarget =
        TDeclaration_FindDeclarator(pDeclaration2, pSingleTypeSpecifier->TypedefName);

      if (pDeclaratorTarget &&
          pDeclaratorTarget->Qualifiers.bIsDestructor)
      {
        bResult = true;
      }
    }
  }
#endif
  return bResult;
}

static bool TDeclarator_IsOwner(TProgram* pProgram,
                                TTypeSpecifier* pTypeSpecifier,
                                TTypeQualifier* pTypeQualifier,
                                TDeclarator* pDeclarator)
{
  bool bResult = false;
  bool bIsPointer = false;
  bool bIsOwner = false;

  for (int i = 0; i < pDeclarator->PointerList.size; i++)
  {
    if (pDeclarator->PointerList.pItems[i]->bPointer)
    {
      bIsPointer = true;
    }

    else if (pDeclarator->PointerList.pItems[i]->Qualifier.bIsOwner)
    {
      bIsOwner = true;
    }
  }

  if (bIsPointer)
  {
    //Se for ponteiro, tem que ver se tem o qualificador _owner
    bResult = bIsOwner;
  }

  else
  {
    //se nao for ponteiro, tem que ver se o tipo
    //tem destructor
    if (IsTypedefWithDestructor(pProgram, pTypeSpecifier))
    {
      bResult = true;
    }
  }

  return bResult;
}

static void TCompoundStatement_Analise(TProgram* pProgram,
                                       TParameterList*  pParameterList,
                                       TCompoundStatement * p,
                                       TVariablesMapStack* pStackNames)
{
#if 0
  //variaveis locais
  TVariablesMap declarationsMap;
  TVariablesMap_Init(&declarationsMap);

  if (pParameterList != NULL)
  {
    //Adiciona os paremetros da funcao como se fossem
    //variaveis locais
    for (int i = 0; i < pParameterList->size; i++)
    {
      if (pParameterList->pItems[i]->Declarator.Name)
      {
        TVariable* pVariable = TVariable_Create();
        pVariable->pParameter = pParameterList->pItems[i];

        pVariable->bIsOwner = TDeclarator_IsOwner(pProgram,
                              pVariable->pParameter->Specifiers.pTypeSpecifierOpt,
                              &pVariable->pParameter->Specifiers.TypeQualifiers,
                              &pParameterList->pItems[i]->Declarator);

        TVariablesMap_Add(&declarationsMap,
                          pVariable->pParameter->Declarator.Name,
                          pVariable);
      }

      else
      {
        //F(void)
      }
    }
  }

  TVariablesMapStack_Push(pStackNames, &declarationsMap);

  for (size_t j = 0; j < p->BlockItemList.size; j++)
  {
    TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
    TBlockItem_Analise(pProgram, pBlockItem, pStackNames);
  }

  //Verifica se esqueceu de chamar destructor nas variaveis locais
  //deste escopo
  CheckIfDestructorWasCalled(pProgram, &declarationsMap);

  //TODO variaveis nao usadas

  TVariablesMapStack_Pop(pStackNames);
  TVariablesMap_Destroy(&declarationsMap);
#endif
}


static void TLabeledStatement_Analise(TProgram* pProgram, TLabeledStatement * p, TVariablesMapStack* pStackNames)
{
  if (p->token == TK_CASE)
  {
    //fprintf(fp, "case ");
    if (p->pStatementOpt)
    {
      TExpression_Analise(pProgram, p->pExpression, "", pStackNames);
    }

    //fprintf(fp, " :\n");
    TStatement_Analise(pProgram, p->pStatementOpt, pStackNames);
  }

  else if (p->token == TK_DEFAULT)
  {
    //fprintf(fp, "default:\n");
    TStatement_Analise(pProgram, p->pStatementOpt, pStackNames);
  }

  else if (p->token == TK_IDENTIFIER)
  {
    //fprintf(fp, "%s:", p->Identifier);
  }



}

static void TForStatement_Analise(TProgram* pProgram, TForStatement * p, TVariablesMapStack* pStackNames)
{

  //fprintf(fp, "for (");
  if (p->pInitDeclarationOpt)
  {
    TAnyDeclaration_Analise(pProgram, p->pInitDeclarationOpt);

    if (p->pExpression2)
    {
      TExpression_Analise(pProgram, p->pExpression2, "expr2", pStackNames);
    }

    //fprintf(fp, ";");
    TExpression_Analise(pProgram, p->pExpression3, "expr3", pStackNames);
  }

  else
  {
    TExpression_Analise(pProgram, p->pExpression1, "expr1", pStackNames);
    //fprintf(fp, ";");
    TExpression_Analise(pProgram, p->pExpression2, "expr2", pStackNames);
    //fprintf(fp, ";");
    TExpression_Analise(pProgram, p->pExpression3, "expr3", pStackNames);
  }


  //fprintf(fp, ")");

  TStatement_Analise(pProgram, p->pStatement, pStackNames);


}


static void TWhileStatement_Analise(TProgram* pProgram, TWhileStatement * p, TVariablesMapStack* pStackNames)
{
  TExpression_Analise(pProgram, p->pExpression, "expr", pStackNames);
  TStatement_Analise(pProgram, p->pStatement, pStackNames);
}


static void TReturnStatement_Analise(TProgram* pProgram, TReturnStatement * p, TVariablesMapStack* pStackNames)
{
  TExpression_Analise(pProgram, p->pExpression, "return-statement", pStackNames);
  CheckIfDestructorWasCalled(pProgram, (TVariablesMap*)Array_Top(pStackNames));
}

static void TDoStatement_Analise(TProgram* pProgram, TDoStatement * p, TVariablesMapStack* pStackNames)
{
  TStatement_Analise(pProgram, p->pStatement, pStackNames);
  TExpression_Analise(pProgram, p->pExpression, "expr", pStackNames);
}


static TParameterList *GetParameterList(TDeclaration* pDeclaration)
{
  TParameterList* pResult = NULL;

  if (pDeclaration->Declarators.size == 1)
  {
    if (pDeclaration->Declarators.pItems[0]->pDeclaratorOpt != NULL)
    {
      pResult =
        pDeclaration->Declarators.pItems[0]->pDeclaratorOpt->pParametersOpt;
    }
  }

  return pResult;
}

static bool IsDestructorArgument(TPointerList* pPointerList)
{
  bool bPointer = false;
  bool bDestructor = false;

  for (int i = 0; i < pPointerList->size; i++)
  {
    if (pPointerList->pItems[i]->bPointer)
    {
      bPointer = true;
    }

    if (pPointerList->pItems[i]->Qualifier.bIsDestructor)
    {
      bDestructor = true;
    }
  }

  return bPointer && bDestructor;
}


static const char* IsDestrutorOf(TProgram* pProgram, const char* functionName)
{
  const char* typeName = NULL;
  TDeclaration*  pDeclaration =
    TProgram_FindDeclaration(pProgram, functionName);

  if (pDeclaration != NULL)
  {
    if (pDeclaration->Declarators.size == 1)
    {
      TParameterList *  pParameterList =
        GetParameterList(pDeclaration);

      if (pParameterList != NULL && pParameterList->size > 0)
      {
        if (IsDestructorArgument(&pParameterList->pItems[0]->Declarator.PointerList))
        {
          typeName =
            GetTypedefName(pParameterList->pItems[0]->Specifiers.pTypeSpecifierOpt);
        }
      }
    }
  }

  return typeName;
}

static void CheckDestructorCallOnExpressionLocalVariablePointer(TProgram* pProgram,
    TPostfixExpressionCore * pPostfixExpressionCore,
    TVariablesMapStack* pStackNames)
{
  bool bResult = false;

  if (pPostfixExpressionCore &&
      pPostfixExpressionCore->token == TK_LEFT_PARENTHESIS)
  {
    TPrimaryExpressionValue *pTPrimaryExpressionValue =
      TExpression_As_TPrimaryExpressionValue(pPostfixExpressionCore->pExpressionLeft);

    if (pTPrimaryExpressionValue)
    {

      TPrimaryExpressionValue *pTPrimaryExpressionValue2 =
        TExpression_As_TPrimaryExpressionValue(pPostfixExpressionCore->pExpressionRight);

      if (pTPrimaryExpressionValue2)
      {
        TVariable* pVariable = TVariablesMapStack_FindVariable(pStackNames,
                               pTPrimaryExpressionValue2->lexeme);

        if (pVariable)
        {
          TDeclarator * pDeclarator =
            TVariable_GetDeclarator(pVariable);

          if (pDeclarator)
          {
            TSingleTypeSpecifier * pSingleTypeSpecifier
              = TVariable_GetSingleSpecifier(pVariable);

            if (pSingleTypeSpecifier &&
                pSingleTypeSpecifier->bIsTypeDef)
            {
              const char*  typeStr =
                IsDestrutorOf(pProgram, pTPrimaryExpressionValue->lexeme);

              if (typeStr != NULL)
              {
                if (strcmp(typeStr, pSingleTypeSpecifier->TypedefName) == 0)
                {
                  pVariable->bDestructorCalled = true;
                }
              }

            }
          }
        }
      }
    }
  }
}

static void CheckDestructorCallOnExpressionLocalVariable(TProgram* pProgram,
    TPostfixExpressionCore * pPostfixExpressionCore,
    TVariablesMapStack* pStackNames)
{
  bool bResult = false;

  if (pPostfixExpressionCore &&
      pPostfixExpressionCore->token == TK_LEFT_PARENTHESIS)
  {
    TPrimaryExpressionValue *pTPrimaryExpressionValue =
      TExpression_As_TPrimaryExpressionValue(pPostfixExpressionCore->pExpressionLeft);

    if (pTPrimaryExpressionValue)
    {
      TUnaryExpressionOperator *pUnaryExpressionOperator =
        TExpression_As_TUnaryExpressionOperator(pPostfixExpressionCore->pExpressionRight);

      if (pUnaryExpressionOperator &&
          pUnaryExpressionOperator->token == TK_AMPERSAND)
      {
        TPrimaryExpressionValue *pTPrimaryExpressionValue2 =
          TExpression_As_TPrimaryExpressionValue(pUnaryExpressionOperator->pExpressionLeft);

        if (pTPrimaryExpressionValue2)
        {
          TVariable* pVariable = TVariablesMapStack_FindVariable(pStackNames,
                                 pTPrimaryExpressionValue2->lexeme);

          if (pVariable)
          {
            TDeclarator * pDeclarator = TVariable_GetDeclarator(pVariable);

            if (pDeclarator)
            {
              TSingleTypeSpecifier * pSingleTypeSpecifier
                = TVariable_GetSingleSpecifier(pVariable);

              if (pSingleTypeSpecifier &&
                  pSingleTypeSpecifier->bIsTypeDef)
              {

                const char*  typeStr =
                  IsDestrutorOf(pProgram, pTPrimaryExpressionValue->lexeme);

                if (typeStr != NULL)
                {
                  if (strcmp(typeStr, pSingleTypeSpecifier->TypedefName) == 0)
                  {
                    pVariable->bDestructorCalled = true;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}


static void TExpressionStatement_Analise(TProgram* pProgram,
    TExpressionStatement * p,
    TVariablesMapStack* pStackNames)
{
  TExpression_Analise(pProgram, p->pExpression, "", pStackNames);
}


static void TJumpStatement_Analise(TProgram* pProgram,
                                   TJumpStatement * p,
                                   TVariablesMapStack* pStackNames)
{
  if (p->pExpression)
  {
    TExpression_Analise(pProgram, p->pExpression, "statement", pStackNames);
  }

  if (p->token == TK_BREAK ||
      p->token == TK_DEFAULT)
  {
  }



}

static void TAsmStatement_Analise(TProgram* pProgram,
                                  TAsmStatement * p)
{
}

static void TSwitchStatement_Analise(TProgram* pProgram,
                                     TSwitchStatement * p,
                                     TVariablesMapStack* pStackNames)
{
  TExpression_Analise(pProgram, p->pConditionExpression, "expr", pStackNames);
  TStatement_Analise(pProgram, p->pExpression, pStackNames);
}


static void TIfStatement_Analise(TProgram* pProgram,
                                 TIfStatement * p,
                                 TVariablesMapStack* pStackNames)
{
  TExpression_Analise(pProgram, p->pConditionExpression, "expr", pStackNames);

  if (p->pStatement->type != TCompoundStatement_ID)
  {
  }

  if (p->pStatement)
  {
    TStatement_Analise(pProgram, p->pStatement, pStackNames);
  }

  if (p->pElseStatement)
  {
    TStatement_Analise(pProgram, p->pElseStatement, pStackNames);
  }
}

static void TStatement_Analise(TProgram* pProgram,
                               TStatement *  p,
                               TVariablesMapStack* pStackNames)
{
  if (p == NULL)
  {
    return;
  }

  switch (p->type)
  {
    case TExpressionStatement_ID:
      TExpressionStatement_Analise(pProgram, (TExpressionStatement*)p, pStackNames);
      break;

    case TSwitchStatement_ID:
      TSwitchStatement_Analise(pProgram, (TSwitchStatement*)p, pStackNames);
      break;

    case TLabeledStatement_ID:
      TLabeledStatement_Analise(pProgram, (TLabeledStatement*)p, pStackNames);
      break;

    case TForStatement_ID:
      TForStatement_Analise(pProgram, (TForStatement*)p, pStackNames);
      break;

    case TJumpStatement_ID:
      TJumpStatement_Analise(pProgram, (TJumpStatement*)p, pStackNames);
      break;

    case TAsmStatement_ID:
      TAsmStatement_Analise(pProgram, (TAsmStatement*)p);
      break;

    case TCompoundStatement_ID:
      TCompoundStatement_Analise(pProgram, NULL, (TCompoundStatement*)p, pStackNames);
      break;

    case TIfStatement_ID:
      TIfStatement_Analise(pProgram, (TIfStatement*)p, pStackNames);
      break;

    case TDoStatement_ID:
      TDoStatement_Analise(pProgram, (TDoStatement*)p, pStackNames);
      break;

    case TReturnStatement_ID:
      TReturnStatement_Analise(pProgram, (TReturnStatement*)p, pStackNames);
      break;

    default:
      ASSERT(false);
      break;
  }


}

static void TBlockItem_Analise(TProgram* pProgram,
                               TBlockItem *  p,
                               TVariablesMapStack* pStackNames)
{
  if (p == NULL)
  {
    ASSERT(false);
    return;
  }


  switch (p->type)
  {
    case TStaticAssertDeclaration_ID:
      break;

    case TSwitchStatement_ID:

      TSwitchStatement_Analise(pProgram, (TSwitchStatement*)p, pStackNames);

      break;

    case TJumpStatement_ID:

      TJumpStatement_Analise(pProgram, (TJumpStatement*)p, pStackNames);

      break;

    case TForStatement_ID:

      TForStatement_Analise(pProgram, (TForStatement*)p, pStackNames);

      break;

    case TIfStatement_ID:

      TIfStatement_Analise(pProgram, (TIfStatement*)p, pStackNames);

      break;

    case TWhileStatement_ID:

      TWhileStatement_Analise(pProgram, (TWhileStatement*)p, pStackNames);

      break;

    case TDoStatement_ID:

      TDoStatement_Analise(pProgram, (TDoStatement*)p, pStackNames);

      break;

    case TDeclaration_ID:
      TDeclaration_Analise(pProgram, (TDeclaration*)p, pStackNames);
      break;

    case TLabeledStatement_ID:

      TLabeledStatement_Analise(pProgram, (TLabeledStatement*)p, pStackNames);

      break;

    case TCompoundStatement_ID:
      break;

    case TExpressionStatement_ID:

      TExpressionStatement_Analise(pProgram, (TExpressionStatement*)p, pStackNames);

      break;

    case TReturnStatement_ID:

      TReturnStatement_Analise(pProgram, (TReturnStatement*)p, pStackNames);

      break;

    case TAsmStatement_ID:

      TAsmStatement_Analise(pProgram, (TAsmStatement*)p);

      break;

    default:
      ASSERT(false);
      break;
  }


}

static void TPostfixExpressionCore_Analise(TProgram* pProgram,
    TPostfixExpressionCore * p,
    TVariablesMapStack* pStackNames)
{
  if (p->pExpressionLeft)
  {
    TExpression_Analise(pProgram, p->pExpressionLeft, "l", pStackNames);
  }

  if (p->pInitializerList)
  {
    TInitializerList_Analise(pProgram, NULL, NULL, p->pInitializerList, pStackNames);
  }

  switch (p->token)
  {
    case TK_FULL_STOP:
      break;

    case TK_ARROW:
      break;

    case TK_LEFT_SQUARE_BRACKET:
      //fprintf(fp, "[");
      TExpression_Analise(pProgram, p->pExpressionRight, "r", pStackNames);
      //fprintf(fp, "]");
      break;

    case TK_LEFT_PARENTHESIS:
    {
	  //aqui tem o nome da funcao e a parte de dentro
	  //
      //fprintf(fp, "(");
      TExpression_Analise(pProgram, p->pExpressionRight, "r", pStackNames);
      //fprintf(fp, ")");
    }
    break;

    case TK_PLUSPLUS:
      //fprintf(fp, "++");

      break;

    case TK_MINUSMINUS:
      //fprintf(fp, "--");

      break;
      break;
  }


  if (p->pNext)
  {
    TPostfixExpressionCore_Analise(pProgram, p->pNext, pStackNames);
  }
}

static void TPostfixExpressionCore_TypeOf(TProgram* pProgram,
    TPostfixExpressionCore * p,
    TVariablesMapStack* pStackNames,
    TDeclarationSpecifiers** ppSpecifiers,
    TDeclarator**ppDeclarator)
{
  if (p->pExpressionLeft)
  {
    TDeclarationSpecifiers* pSpecifiersLocal = NULL;
    TDeclarator* pDeclaratorLocal = NULL;
    TExpression_TypeOf(pProgram,
                       p->pExpressionLeft,
                       pStackNames,
                       &pSpecifiersLocal,
                       &pDeclaratorLocal);
  }

  if (p->pInitializerList)
  {
    TInitializerList_Analise(pProgram, NULL, NULL, p->pInitializerList, pStackNames);
  }

  switch (p->token)
  {
    case TK_FULL_STOP:
      break;

    case TK_ARROW:
      break;

    case TK_LEFT_SQUARE_BRACKET:
      //fprintf(fp, "[");
      TExpression_Analise(pProgram, p->pExpressionRight, "r", pStackNames);
      //fprintf(fp, "]");
      break;

    case TK_LEFT_PARENTHESIS:
    {
      const char* funcName =
        MatchIdentifier(p->pExpressionLeft);

      if (funcName)
      {
        //O tipo eh o retorno da funcao
        TDeclaration *pDeclaration =
          TProgram_FindDeclaration(pProgram, funcName);

        if (pDeclaration != NULL)
        {
          *ppSpecifiers = &pDeclaration->Specifiers;
          *ppDeclarator = pDeclaration->Declarators.pItems[0];
          //pDeclaration->
        }
		else
		{
			//nao achou esta funcao
		}
      }

      else
      {

      }


      //fprintf(fp, "(");
      //TExpression_Analise(pProgram, p->pExpressionRight, "r", pStackNames);
      //fprintf(fp, ")");
    }
    break;

    case TK_PLUSPLUS:
      //fprintf(fp, "++");

      break;

    case TK_MINUSMINUS:
      //fprintf(fp, "--");

      break;
      break;
  }


  if (p->pNext)
  {
    TDeclarationSpecifiers* pSpecifiersLocal = NULL;
    TDeclarator* pDeclaratorLocal = NULL;
    TPostfixExpressionCore_TypeOf(pProgram, p->pNext, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);
  }
}

static TVariable* GetVariable(TExpression * pExpression,
                              TVariablesMapStack* pStackNames)
{
  TVariable *pVariable = NULL;
  const char* varStr =
    MatchIdentifier(pExpression);

  if (varStr)
  {
    pVariable =
      TVariablesMapStack_FindVariable(pStackNames, varStr);
  }

  return pVariable;
}

static void TExpression_Analise(TProgram* pProgram,
                                TExpression *  p,
                                const char* name,
                                TVariablesMapStack* pStackNames)
{
  if (p == NULL)
  {
    //ASSERT(false);
    return;

  }

  /////////////////

  switch (p->type)
  {
      CASE(TBinaryExpression) :
      {
        TBinaryExpression* pBinaryExpression =
          (TBinaryExpression*)p;

        TExpression_Analise(pProgram, pBinaryExpression->pExpressionLeft, "l-expr", pStackNames);
        TExpression_Analise(pProgram, pBinaryExpression->pExpressionRight, "r-expr", pStackNames);

        //Verifica se esta comparando ou setando null
        //em um ponteiro nao nulo

        TVariable *  pVariable =
          GetVariable(pBinaryExpression->pExpressionLeft, pStackNames);

        if (pVariable != NULL)
        {
          TDeclarator * pDeclarator =
            TVariable_GetDeclarator(pVariable);

          if (IsNonNullPointer(pDeclarator))
          {
            if (MatchNULL(pBinaryExpression->pExpressionRight))
            {
              if (pBinaryExpression->token == TK_EQUALS_SIGN)
              {
                printf("%s(%d): warning: NULL is not assignable to '%s'.Use  if it can be null.\n", pProgram->Files2.pItems[pBinaryExpression->Position.FileIndex]->FullPath, pBinaryExpression->Position.Line, pDeclarator->Name);
              }

              else if (pBinaryExpression->token == TK_EQUALEQUAL ||
                       pBinaryExpression->token == TK_NOTEQUAL)
              {
                printf("%s(%d): warning: Variable '%s' is not null by definition. Use  if it can be null.\n", pProgram->Files2.pItems[pBinaryExpression->Position.FileIndex]->FullPath, pBinaryExpression->Position.Line, pDeclarator->Name);
              }
            }
          }
        }
      }
      break;

      CASE(TTernaryExpression) :
      {
        TTernaryExpression* pTernaryExpression =
          (TTernaryExpression*)p;

        TExpression_Analise(pProgram, pTernaryExpression->pExpressionLeft, "l-expr", pStackNames);
        //fprintf(fp, " ? ");
        TExpression_Analise(pProgram, pTernaryExpression->pExpressionMiddle, "m-expr", pStackNames);
        //fprintf(fp, " : ");
        TExpression_Analise(pProgram, pTernaryExpression->pExpressionRight, "r-expr", pStackNames);
      }
      break;

      CASE(TPrimaryExpressionValue) :
      {
        TPrimaryExpressionValue* pPrimaryExpressionValue =
          (TPrimaryExpressionValue*)p;

        if (pPrimaryExpressionValue->pExpressionOpt != NULL)
        {
          //fprintf(fp, "(");
          TExpression_Analise(pProgram, pPrimaryExpressionValue->pExpressionOpt, "expr", pStackNames);
          //fprintf(fp, ")");
        }

        else
        {
          //fprintf(fp, "%s", pPrimaryExpressionValue->lexeme);
        }
      }
      break;

      CASE(TPostfixExpressionCore) :
      {
        TPostfixExpressionCore* pPostfixExpressionCore =
          (TPostfixExpressionCore*)p;

        TPostfixExpressionCore_Analise(pProgram, pPostfixExpressionCore, pStackNames);

        CheckDestructorCallOnExpressionLocalVariable(pProgram,
            pPostfixExpressionCore,
            pStackNames);

        CheckDestructorCallOnExpressionLocalVariablePointer(pProgram,
            pPostfixExpressionCore,
            pStackNames);
      }
      break;

      CASE(TUnaryExpressionOperator) :
      {
        TUnaryExpressionOperator* pTUnaryExpressionOperator =
          (TUnaryExpressionOperator*)p;

        if (pTUnaryExpressionOperator->token == TK_SIZEOF)
        {
          if (pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt != NULL)
          {
            //fprintf(fp, "sizeof (");
            TTypeQualifier_Analise(pProgram, &pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers);
            TTypeSpecifier_Analise(pProgram, pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, pStackNames);
            TDeclarator_Analise(pProgram, NULL, &pTUnaryExpressionOperator->TypeName.Declarator, pStackNames);
            //fprintf(fp, ")");
          }

          else
          {
            //fprintf(fp, "sizeof ");
            TExpression_Analise(pProgram, pTUnaryExpressionOperator->pExpressionLeft, "expr", pStackNames);
            //fprintf(fp, "");
          }
        }

        else
        {
          TExpression_Analise(pProgram, pTUnaryExpressionOperator->pExpressionLeft, "expr", pStackNames);

          if (pTUnaryExpressionOperator->token == TK_MOVE)
          {
            //Marca como movido
            TVariable *pVariable =
              GetVariable(pTUnaryExpressionOperator->pExpressionLeft, pStackNames);

            if (pVariable)
            {
              //movido
              pVariable->bMoved = true;
            }
          }
        }
      }
      break;

      CASE(TCastExpressionType) :
      {
        TCastExpressionType * pCastExpressionType =
          (TCastExpressionType*)p;


        //fprintf(fp, "(");
        TTypeQualifier_Analise(pProgram, &pCastExpressionType->TypeName.Specifiers.TypeQualifiers);
        TTypeSpecifier_Analise(pProgram, pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, pStackNames);
        TDeclarator_Analise(pProgram, NULL, &pCastExpressionType->TypeName.Declarator, pStackNames);
        //fprintf(fp, ")");
        TExpression_Analise(pProgram, pCastExpressionType->pExpression, "expr", pStackNames);
      }
      break;

    default:

      ASSERT(false);
  }
}



static void TExpression_TypeOf(TProgram* pProgram,
                               TExpression *  p,
                               TVariablesMapStack* pStackNames,
                               TDeclarationSpecifiers** ppSpecifiers,
                               TDeclarator**ppDeclarator)
{
  if (p == NULL)
  {
    //ASSERT(false);
    return;

  }

  /////////////////

  switch (p->type)
  {
      CASE(TBinaryExpression) :
      {
        TBinaryExpression* pBinaryExpression =
          (TBinaryExpression*)p;

        TDeclarationSpecifiers* pSpecifiersLocal = NULL;
        TDeclarator* pDeclaratorLocal = NULL;
        TExpression_TypeOf(pProgram, pBinaryExpression->pExpressionLeft, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);

        TDeclarationSpecifiers* pSpecifiersLocal2 = NULL;
        TDeclarator* pDeclaratorLocal2 = NULL;

        TExpression_TypeOf(pProgram, pBinaryExpression->pExpressionRight, pStackNames, &pSpecifiersLocal2, &pDeclaratorLocal2);

        //Verifica se esta comparando ou setando null
        //em um ponteiro nao nulo

        TVariable *  pVariable =
          GetVariable(pBinaryExpression->pExpressionLeft, pStackNames);

        if (pVariable != NULL)
        {
          TDeclarator * pDeclarator =
            TVariable_GetDeclarator(pVariable);

          if (IsNonNullPointer(pDeclarator))
          {
            if (MatchNULL(pBinaryExpression->pExpressionRight))
            {
              if (pBinaryExpression->token == TK_EQUALS_SIGN)
              {
                printf("%s(%d): warning: NULL is not assignable to '%s'.Use  if it can be null.\n", pProgram->Files2.pItems[pBinaryExpression->Position.FileIndex]->FullPath, pBinaryExpression->Position.Line, pDeclarator->Name);
              }

              else if (pBinaryExpression->token == TK_EQUALEQUAL ||
                       pBinaryExpression->token == TK_NOTEQUAL)
              {
                printf("%s(%d): warning: Variable '%s' is not null by definition. Use  if it can be null.\n", pProgram->Files2.pItems[pBinaryExpression->Position.FileIndex]->FullPath, pBinaryExpression->Position.Line, pDeclarator->Name);
              }
            }
          }
        }
      }
      break;

      CASE(TTernaryExpression) :
      {
        TTernaryExpression* pTernaryExpression =
          (TTernaryExpression*)p;

        TDeclarationSpecifiers* pSpecifiersLocal = NULL;
        TDeclarator* pDeclaratorLocal = NULL;

        TExpression_TypeOf(pProgram, pTernaryExpression->pExpressionLeft, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);
        //fprintf(fp, " ? ");
        TExpression_TypeOf(pProgram, pTernaryExpression->pExpressionMiddle, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);
        //fprintf(fp, " : ");
        TExpression_TypeOf(pProgram, pTernaryExpression->pExpressionRight, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);
      }
      break;

      CASE(TPrimaryExpressionValue) :
      {
        TPrimaryExpressionValue* pPrimaryExpressionValue =
          (TPrimaryExpressionValue*)p;

        if (pPrimaryExpressionValue->pExpressionOpt != NULL)
        {
          //fprintf(fp, "(");
          TExpression_TypeOf(pProgram, pPrimaryExpressionValue->pExpressionOpt, pStackNames, ppSpecifiers, ppDeclarator);
          //fprintf(fp, ")");
        }

        else
        {
          if (pPrimaryExpressionValue->token == TK_DECIMAL_INTEGER ||
              pPrimaryExpressionValue->token == TK_HEX_INTEGER)
          {
            //ppSpecifiers = NULL;
            //ppDeclarator = NULL;

            static TDeclarationSpecifiers specifiers =
              TDECLARATION_SPECIFIERS_INIT;

            static TSingleTypeSpecifier singleTypeSpecifier = TBUILDINTYPE_SPECIFIER_INIT;
            singleTypeSpecifier.bIsInt = true;
            specifiers.pTypeSpecifierOpt = TSingleTypeSpecifier_As_TTypeSpecifier(&singleTypeSpecifier);

            *ppSpecifiers = &specifiers;

            static TDeclarator declarator = TDECLARATOR_INIT;
            *ppDeclarator = &declarator;

          }

          //fprintf(fp, "%s", pPrimaryExpressionValue->lexeme);
        }
      }
      break;

      CASE(TPostfixExpressionCore) :
      {
        TPostfixExpressionCore* pPostfixExpressionCore =
          (TPostfixExpressionCore*)p;

        TPostfixExpressionCore_TypeOf(pProgram, pPostfixExpressionCore, pStackNames, ppSpecifiers, ppDeclarator);


      }
      break;

      CASE(TUnaryExpressionOperator) :
      {
        TUnaryExpressionOperator* pTUnaryExpressionOperator =
          (TUnaryExpressionOperator*)p;

        if (pTUnaryExpressionOperator->token == TK_SIZEOF)
        {
          //return int sizeof
          //if (pTUnaryExpressionOperator->TypeName.pTypeSpecifier != NULL)
          //{
          //fprintf(fp, "sizeof (");
          //TTypeQualifier_Analise(pProgram, &pTUnaryExpressionOperator->TypeName.qualifiers);
          //TTypeSpecifier_Analise(pProgram, pTUnaryExpressionOperator->TypeName.pTypeSpecifier, pStackNames);
          //TDeclarator_Analise(pProgram, NULL, &pTUnaryExpressionOperator->TypeName.declarator, pStackNames);
          //fprintf(fp, ")");
          //}

          //else
          //{
          //fprintf(fp, "sizeof ");
          //TExpression_TypeOf(pProgram, pTUnaryExpressionOperator->pExpressionLeft, pStackNames);
          //fprintf(fp, "");
          //}
        }

        else
        {
          TDeclarationSpecifiers* pSpecifiersLocal = NULL;
          TDeclarator* pDeclaratorLocal = NULL;
          TExpression_TypeOf(pProgram, pTUnaryExpressionOperator->pExpressionLeft, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);

        }
      }
      break;

      CASE(TCastExpressionType) :
      {
        TCastExpressionType * pCastExpressionType =
          (TCastExpressionType*)p;

        *ppSpecifiers = &pCastExpressionType->TypeName.Specifiers;
        *ppDeclarator = &pCastExpressionType->TypeName.Declarator;
      }
      break;

    default:

      ASSERT(false);
  }
}

static bool TEnumerator_Analise(TProgram *pProgram, TEnumerator *pTEnumerator,
                                TVariablesMapStack *pStackNames)
{

  //fprintf(fp, "%s", pTEnumerator->Name);

  if (pTEnumerator->pExpression)
  {
    //fprintf(fp, " = ");
    TExpression_Analise(pProgram, pTEnumerator->pExpression, "expr", pStackNames);

    //int r;
    //EvaluateConstantExpression(pTEnumerator->pExpression,  &r);

  }

  else
  {
    //vou criar uma expressionp enum?
  }

  return true;
}

static void TEnumSpecifier_Analise(TProgram* pProgram, TEnumSpecifier* p, TVariablesMapStack* pStackNames)
{

  //fprintf(fp, " enum ");
  //fprintf(fp, " %s", p->Name);
  //fprintf(fp, "\n{\n");

  for (size_t i = 0; i < p->EnumeratorList.size; i++)
  {
    TEnumerator *pTEnumerator = p->EnumeratorList.pItems[i];

    TEnumerator_Analise(pProgram, pTEnumerator, pStackNames);

    if (i + 1 < p->EnumeratorList.size)
    {
    }//fprintf(fp, ",\n");
    else
    {
    }	//fprintf(fp, "\n");

  }



}

static bool StructRequirsesDestructor(TProgram* pProgram, TStructUnionSpecifier* p)
{
  //Verifica se pelo um item da struct tem destructor

  bool bRequireDestructor = false;

  for (size_t i = 0; i < p->StructDeclarationList.size; i++)
  {
    TAnyStructDeclaration *  pStructDeclaration = p->StructDeclarationList.pItems[i];
    TStructDeclaration *  pStructDeclarationBase =
      TAnyStructDeclaration_As_TStructDeclaration(pStructDeclaration);

    if (pStructDeclaration != NULL)
    {
      if (IsTypedefWithDestructor(pProgram, pStructDeclarationBase->pSpecifier))
      {
        bRequireDestructor = true;
        break;
      }

    }
  }

  return bRequireDestructor;
}

static void TStructUnionSpecifier_Analise(TProgram* pProgram, TStructUnionSpecifier* p, TVariablesMapStack* pStackNames)
{


  if (p->bIsStruct)
  {
  }
  else
  {
  }

  //fprintf(fp, " %s", p->Name);

  if (p->StructDeclarationList.size > 0)
  {
    for (size_t i = 0; i < p->StructDeclarationList.size; i++)
    {
      TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
      TAnyStructDeclaration_Analise(pProgram, pStructDeclaration, pStackNames);
    }
  }



}

static void TSingleTypeSpecifier_Analise(TProgram* pProgram, TSingleTypeSpecifier* p)
{
  int i = 0;

  if (p->bIsVoid)
  {
    //fprintf(fp, " void");

  }

  if (p->bIsUnsigned)
  {
    //fprintf(fp, " unsigned");

  }

  if (p->bIsBool)
  {
    //fprintf(fp, " _Bool");

  }

  if (p->bIsChar)
  {
    //fprintf(fp, " char");

  }

  if (p->bIsShort)
  {
    //fprintf(fp, " short");

  }

  for (int j = 0; j < p->nLong; j++)
  {
    //fprintf(fp, " long");

  }

  if (p->bIsInt)
  {
    //fprintf(fp, " int");

  }

  if (p->bIsDouble)
  {
    //fprintf(fp, " double");

  }

  if (p->bIsFloat)
  {
    //fprintf(fp, " float");

  }
}

static void TTypeSpecifier_Analise(TProgram* pProgram,
                                   TTypeSpecifier*  p,
                                   TVariablesMapStack* pStackNames)
{
  if (p == NULL)
  {
    //declaracao vazia: ;
    return;
  }

  switch (p->type)
  {
      CASE(TStructUnionSpecifier) :
        TStructUnionSpecifier_Analise(pProgram, (TStructUnionSpecifier*)p, pStackNames);
        break;

        CASE(TEnumSpecifier) :
        TEnumSpecifier_Analise(pProgram, (TEnumSpecifier*)p, pStackNames);
        break;

        CASE(TSingleTypeSpecifier) :
        TSingleTypeSpecifier_Analise(pProgram, (TSingleTypeSpecifier*)p);
        break;

      default:
        break;
    }


  }

  static void TDesignator_Analise(TProgram* pProgram, TDesignator* p, TVariablesMapStack* pStackNames)
{

  //
  if (p->Name)
  {
    //.identifier
    //fprintf(fp, ".%s", p->Name);
  }

  else
  {
    //[constant-expression]
    TExpression_Analise(pProgram, p->pExpression, "index", pStackNames);
  }

  //fprintf(fp, "}");

}

static void TInitializerList_Analise(TProgram* pProgram,
                                     TDeclaration * pDeclaration,
                                     TDeclarator* pDeclarator,
                                     TInitializerList*p,
                                     TVariablesMapStack* pStackNames)
{


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
    {
      //fprintf(fp, ",");
    }

    TInitializerListItem* pItem = p->pItems[i];
    TInitializerListItem_Analise(pProgram, pDeclaration, pDeclarator, pItem, pStackNames);
  }


}


static void TInitializer_Analise(TProgram* pProgram,
                                 TDeclaration * pDeclaration,
                                 TDeclarator* pDeclarator,
                                 TInitializer*  pInitializer,
                                 TVariablesMapStack* pStackNames)
{
  if (pInitializer == NULL)
  {
    return;
  }

  if (pInitializer->type == TInitializerListType_ID)
  {
    TInitializerListType* pInitializerListType =
      (TInitializerListType*)pInitializer;
    TInitializerList_Analise(pProgram,
                             NULL,
                             NULL,
                             &pInitializerListType->InitializerList,
                             pStackNames);
  }

  else
  {
    TExpression* pExpression =
      (TExpression*)pInitializer;

    TDeclarationSpecifiers* pSpecifiersLocal = NULL;
    TDeclarator* pDeclaratorLocal = NULL;
    TExpression_TypeOf(pProgram, pExpression, pStackNames, &pSpecifiersLocal, &pDeclaratorLocal);

    if (pDeclaratorLocal != NULL &&
        pDeclarator != NULL &&
        pDeclaration != NULL)
    {
      if (IsPointer(pDeclarator))
      {
        bool bIsNullAssigment = MatchNULL(pExpression);

        bool bNonNullPointerLeft = IsNonNullPointer(pDeclarator);

        if (bNonNullPointerLeft)
        {
          if (bIsNullAssigment)
          {
            printf("%s(%d): warning: NULL is not assignable to '%s'.Use  if it can be null.\n", pProgram->Files2.pItems[pDeclaration->FileIndex]->FullPath, pDeclaration->Line, pDeclarator->Name);
          }
        }

        if (IsPointer(pDeclaratorLocal) && !bIsNullAssigment)
        {

          bool bNonNullPointerRight =
            IsNonNullPointer(pDeclaratorLocal);

          if (bNonNullPointerLeft != bNonNullPointerRight)
          {
            printf("%s(%d): warning: Invalid qualifiers . %s\n", pProgram->Files2.pItems[pDeclaration->FileIndex]->FullPath, pDeclaration->Line, pDeclarator->Name);
          }


          //
          bool bIsOwner = TDeclarator_IsOwner(pProgram, pDeclaration->Specifiers.pTypeSpecifierOpt,
                                              &pDeclaration->Specifiers.TypeQualifiers,
                                              pDeclarator);

          bool bIsOwner2 = TDeclarator_IsOwner(pProgram, pSpecifiersLocal->pTypeSpecifierOpt,
                                               &pSpecifiersLocal->TypeQualifiers,
                                               pDeclaratorLocal);

          if (!bIsNullAssigment &&
              bIsOwner != bIsOwner2)
          {
            printf("%s(%d): warning: Incompatible qualifiers . %s\n", pProgram->Files2.pItems[pDeclaration->FileIndex]->FullPath, pDeclaration->Line, pDeclarator->Name);
          }
        }
      }


    }

    TExpression_Analise(pProgram, pExpression, "", pStackNames);
  }
}


static void TPointerList_Analise(TProgram* pProgram, TPointerList *p)
{


  for (size_t i = 0; i < p->size; i++)
  {
    TPointer * pItem = p->pItems[i];
    TPointer_Analise(pProgram, pItem);
  }


}

static void TParameterList_Analise(TProgram* pProgram, TParameterList *p, TVariablesMapStack* pStackNames)
{


  for (size_t i = 0; i < p->size; i++)
  {
    if (i > 0)
    {
      //fprintf(fp, ",");
    }

    TParameterDeclaration * pItem = p->pItems[i];

    TParameterDeclaration_Analise(pProgram, pItem, pStackNames);
  }


}



static void TDeclarator_PrintCore(TProgram* pProgram,
                                  TDeclaration* pDeclaration,
                                  TDeclarator* p,
                                  TVariablesMapStack* pStackNames)
{

#if 0
  if (p->token == TK_LEFT_PARENTHESIS &&
      p->pParametersOpt == NULL)
  {
    // ( declarator )
    //fprintf(fp, "(");
  }

  if (p->PointerList.size > 0)
  {
    TPointerList_Analise(pProgram, &p->PointerList);
  }



  TTypeQualifier_Analise(pProgram, &p->Qualifiers);

  if (p->Name != NULL)
  {
    if (pStackNames && pStackNames->size > 0)
    {
      //Coloca o declarador no mapa quando ele é usado
      //na variaveis locais
      TVariablesMap* pDeclarationsMap =
        (TVariablesMap*)pStackNames->pItems[pStackNames->size - 1];

      //verificar se ja existe e enviar warning de hidden

      if (TDeclaration_As_TAnyDeclaration(pDeclaration))
      {
        TVariable * pVariable = TVariable_Create();
        pVariable->pDeclaration0 = pDeclaration;
        pVariable->pDeclarator0 = p;


        pVariable->bIsOwner = TDeclarator_IsOwner(pProgram,
                              pDeclaration->Specifiers.pTypeSpecifierOpt,
                              &pDeclaration->Specifiers.TypeQualifiers,
                              p);

        TVariablesMap_Add(pDeclarationsMap,
                          p->Name,
                          pVariable);
      }
    }

    //fprintf(fp, " %s", p->Name);
  }

  if (p->pParametersOpt != NULL)
  {
    TParameterList_Analise(pProgram, p->pParametersOpt, pStackNames);
  }

  if (p->token == TK_LEFT_SQUARE_BRACKET)
  {
    //tem que revisar..isso fica no p->pDeclaratorOpt
    //fprintf(fp, "[");
    TExpression_Analise(pProgram, p->pExpression, "", pStackNames);
    //fprintf(fp, "]");

  }




  else
  {
    ////fprintf(fp, "\"name\": null");
  }

  if (p->token == TK_LEFT_PARENTHESIS &&
      p->pParametersOpt == NULL)
  {
    // ( declarator )
    //fprintf(fp, ")");
  }

  if (p->pDeclaratorOpt)
  {
    TDeclarator_PrintCore(pProgram, pDeclaration, p->pDeclaratorOpt, pStackNames);
  }



#endif
}

static void TDeclarator_Analise(TProgram* pProgram,
                                TDeclaration * pDeclaration,
                                TDeclarator* p,
                                TVariablesMapStack* pStackNames)
{
  TDeclarator_PrintCore(pProgram, pDeclaration, p, pStackNames);

  if (p->pInitializer != NULL)
  {
    //Deduzir o tipo do initializer
    //se for opt contamina o declarator
    TInitializer_Analise(pProgram,
                         pDeclaration,
                         p,
                         p->pInitializer,
                         pStackNames);
  }

}


static void TDeclaratorList_Analise(TProgram* pProgram,
                                    TDeclaration* pDeclaration,
                                    TDeclaratorList *p,
                                    TVariablesMapStack* pStackNames)
{
  for (size_t i = 0; i < p->size; i++)
  {
    TDeclarator* pItem = p->pItems[i];
    TDeclarator_Analise(pProgram, pDeclaration, pItem, pStackNames);
  }
}

static void TStructDeclaration_Analise(TProgram* pProgram, TStructDeclaration* p, TVariablesMapStack* pStackNames)
{
  TTypeQualifier_Analise(pProgram, &p->Qualifier);
  TTypeSpecifier_Analise(pProgram, p->pSpecifier, pStackNames);



  TDeclaratorList_Analise(pProgram, NULL, &p->DeclaratorList, pStackNames);
}

static void TAnyStructDeclaration_Analise(TProgram* pProgram, TAnyStructDeclaration* p, TVariablesMapStack* pStackNames)
{
  switch (p->type)
  {
    case TStructDeclaration_ID:
      TStructDeclaration_Analise(pProgram, (TStructDeclaration*)p, pStackNames);
      break;

    default:
      ASSERT(false);
      break;
  }


}

static void StorageSpecifier_Analise(TProgram* pProgram, TStorageSpecifier* p)
{

  if (p->bIsAuto)
  {
    //fprintf(fp, " auto");

  }

  if (p->bIsExtern)
  {
    //fprintf(fp, " extern");

  }

  if (p->bIsRegister)
  {
    //fprintf(fp, " register");

  }

  if (p->bIsStatic)
  {
    //fprintf(fp, " static");

  }




  if (p->bIsThread_local)
  {
    //fprintf(fp, " [Thread_local]");

  }

  if (p->bIsTypedef)
  {
    //fprintf(fp, " typedef");

  }


}

static void TFunctionSpecifier_Analise(TProgram* pProgram, TFunctionSpecifier* p)
{
  if (p->bIsInline)
  {
    //fprintf(fp, " inline");

  }

  if (p->bIsNoReturn)
  {
    //fprintf(fp, " [noreturn]");

  }

}



static void TTypeQualifier_Analise(TProgram* pProgram, TTypeQualifier* p)
{

  if (p->bIsAtomic)
  {
    //fprintf(fp, " _Atomic");

  }

  if (p->bIsConst)
  {
    //fprintf(fp, " const");

  }

  if (p->bIsRestrict)
  {
    //fprintf(fp, " restrict");

  }

  if (p->bIsVolatile)
  {
    //fprintf(fp, " volatile");

  }

}

static void TPointer_Analise(TProgram* pProgram, TPointer* pPointer)
{
  TTypeQualifier_Analise(pProgram, &pPointer->Qualifier);
}

static void TDeclarationSpecifiers_Analise(TProgram* pProgram, TDeclarationSpecifiers* pDeclarationSpecifiers, TVariablesMapStack* pStackNames)
{
  TFunctionSpecifier_Analise(pProgram, &pDeclarationSpecifiers->FunctionSpecifiers);
  StorageSpecifier_Analise(pProgram, &pDeclarationSpecifiers->StorageSpecifiers);
  TTypeQualifier_Analise(pProgram, &pDeclarationSpecifiers->TypeQualifiers);
  TTypeSpecifier_Analise(pProgram, pDeclarationSpecifiers->pTypeSpecifierOpt, pStackNames);
}


//Verifica o padrao:
//varName->structMemberName
//return true false
static bool CheckStructMember(TExpression *pExpression,
                              const char* varName,
                              const char* structMemberName)
{
  bool bResult = false;
  //varName->XXX
  TPostfixExpressionCore *  pRight =
    MatchStructPointerMember(varName, pExpression);

  if (pRight != NULL)
  {
    if (pRight->Identifier != NULL &&
        strcmp(pRight->Identifier, structMemberName) == 0)
    {
      bResult = true;
    }
  }

  return bResult;
}



static bool CheckFunctionOnStructItem2(TExpressionStatement* p,
                                       const char* funcName,
                                       const char* structVariablePointer,
                                       const char* structMemberName)
{
  bool bMatch = false;

  TPostfixExpressionCore * pPostfixExpressionCoreFirst =
    TExpression_As_TPostfixExpressionCore(p->pExpression);

  if (pPostfixExpressionCoreFirst &&
      pPostfixExpressionCoreFirst->token == TK_LEFT_PARENTHESIS)
  {
    TPrimaryExpressionValue *pTPrimaryExpressionValueLeft =
      TExpression_As_TPrimaryExpressionValue(pPostfixExpressionCoreFirst->pExpressionLeft);

    if (pTPrimaryExpressionValueLeft)
    {
      if (strcmp(pTPrimaryExpressionValueLeft->lexeme, funcName) == 0)
      {
        bMatch = CheckStructMember(pPostfixExpressionCoreFirst->pExpressionRight,
                                   structVariablePointer,
                                   structMemberName);

      }
    }
  }

  return bMatch;
}


bool CheckDestructorImplementation(TProgram* pProgram,
                                   TDeclaration* p)
{
  //Verifica se a declaracoa eh uma funcao declaracao de destructor
  // Se tem este padrao T_Destroy(T *p)
  // depois ve se T eh struct
  // passa para cada parte de T e ve se tem destructor
  // se tem passa pelas expressoes vendo se chamou o destructor

  bool bIsDestructor = false;

  if (p->Declarators.size == 1 && p->pCompoundStatementOpt != NULL)
  {
    const char* typeName =
      IsDestrutorOf(pProgram, p->Declarators.pItems[0]->Name);

    if (typeName)
    {
      TDeclaration* pStructDeclaration =
        TProgram_FindDeclaration(pProgram, typeName);

      if (pStructDeclaration)
      {
        TStructUnionSpecifier*  pStructUnionSpecifier =
          TTypeSpecifier_As_TStructUnionSpecifier(pStructDeclaration->Specifiers.pTypeSpecifierOpt);

        if (pStructUnionSpecifier != NULL)
        {
          for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
          {
            TAnyStructDeclaration * pAnyStructDeclaration =
              pStructUnionSpecifier->StructDeclarationList.pItems[i];
            TStructDeclaration *  pStructDeclaration =
              TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

            if (pStructDeclaration != NULL)
            {
              TSingleTypeSpecifier * pSingleTypeSpecifierLocal =
                TTypeSpecifier_As_TSingleTypeSpecifier(pStructDeclaration->pSpecifier);

              if (pSingleTypeSpecifierLocal != NULL)
              {
                //Para cada declarador da struct
                for (int j = 0; j < pStructDeclaration->DeclaratorList.size; j++)
                {
                  TDeclarator *  pDeclarator =
                    pStructDeclaration->DeclaratorList.pItems[j];

                  if (pDeclarator != NULL &&
                      TDeclarator_IsOwner(pProgram,
                                          pStructDeclaration->pSpecifier,
                                          &pDeclarator->Qualifiers,
                                          pDeclarator))
                  {
                    bool bDestructorCallFound = false;

                    for (int k = 0;
                         k < p->pCompoundStatementOpt->BlockItemList.size && !bDestructorCallFound;
                         k++)
                    {
                      //Vou procurar pela chamada do destroy deste cara
                      TBlockItem *pBlockItem =
                        p->pCompoundStatementOpt->BlockItemList.pItems[k];

                      TExpressionStatement*  pExpression =
                        TBlockItem_As_TExpressionStatement(pBlockItem);

                      if (pExpression != NULL)
                      {
                        const char* funcName = NULL;
                        TExpression * pCallArgs =
                          MatchFunctionCall(pExpression->pExpression,
                                            &funcName);

                        if (pCallArgs)
                        {
                          const char* structMemberTypedefName =
                            GetTypedefName(pStructDeclaration->pSpecifier);

                          const char* typeName2 =
                            IsDestrutorOf(pProgram, funcName);

                          if (typeName2 && structMemberTypedefName)
                          {
                            if (strcmp(typeName2, structMemberTypedefName) == 0)
                            {
                              //Achou a chamada de uma funcao
                              //que eh destructor do tipo que eh o tipo
                              //do declarator que esta sendo procurado
                              //TODO: poderia verificar melhor os parametros
                              //certinho
                              bDestructorCallFound = true;
                            }
                          }
                        }

                        //verifica se esta destruindo o item
                        //F(&x->y);
                      }
                    }

                    if (!bDestructorCallFound)
                    {
                      printf("%s(%d): warning: destructor not called for name %s\n", pProgram->Files2.pItems[p->FileIndex]->FullPath, p->Line, pDeclarator->Name);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return bIsDestructor;
}

static void StructAutomaticOwn(TProgram* pProgram, TDeclaration* p)
{
  //Verifica se algum item da struct tem destructor
  //se tiver marca os declaradores da struct como
  //tendo destructor tb
  if (p->Specifiers.StorageSpecifiers.bIsTypedef)
  {
    TStructUnionSpecifier *  pStructUnionSpecifier =
      TTypeSpecifier_As_TStructUnionSpecifier(p->Specifiers.pTypeSpecifierOpt);

    if (pStructUnionSpecifier != NULL)
    {
      if (StructRequirsesDestructor(pProgram, pStructUnionSpecifier))
      {
        for (int i = 0; i < p->Declarators.size; i++)
        {
          p->Declarators.pItems[i]->Qualifiers.bIsDestructor = true;
        }
      }
    }
  }
}
static void TDeclaration_Analise(TProgram* pProgram, TDeclaration* p, TVariablesMapStack* pStackNames)
{
  TDeclarationSpecifiers_Analise(pProgram, &p->Specifiers, pStackNames);
  TDeclaratorList_Analise(pProgram, p, &p->Declarators, pStackNames);


  //Faz o  automatico para typedef da struct
  StructAutomaticOwn(pProgram, p);

  if (p->pCompoundStatementOpt != NULL)
  {
    //se for um destructor, verifica se chamou
    //o destructor das partes
    CheckDestructorImplementation(pProgram, p);

    TParameterList* pParametersOpt = NULL;

    if (p->Declarators.pItems[0]->pDeclaratorOpt)
    {
      pParametersOpt =
        p->Declarators.pItems[0]->pDeclaratorOpt->pParametersOpt;
      //if (pParametersOpt)
      //{
      //pParametersOpt->pItems[0]->Declarator.
      //}
    }


    TCompoundStatement_Analise(pProgram,
                               pParametersOpt,
                               p->pCompoundStatementOpt, pStackNames);
  }

  else
  {
    //fprintf(fp, ";");
  }
}


static void TParameterDeclaration_Analise(TProgram* pProgram, TParameterDeclaration* p, TVariablesMapStack* pStackNames)
{
  TDeclarationSpecifiers_Analise(pProgram, &p->Specifiers, pStackNames);

  if (IsDestructorDeclarator(&p->Declarator))
  {
    TSingleTypeSpecifier * pSingleTypeSpecifier =
      TTypeSpecifier_As_TSingleTypeSpecifier(p->Specifiers.pTypeSpecifierOpt);

    if (pSingleTypeSpecifier &&
        pSingleTypeSpecifier->bIsTypeDef)
    {
      TDeclaration *  pDeclaration =
        TProgram_FindDeclaration(pProgram, pSingleTypeSpecifier->TypedefName);

      if (pDeclaration != NULL)
      {
        TDeclarator *pDeclarator =
          TDeclaration_FindDeclarator(pDeclaration, pSingleTypeSpecifier->TypedefName);

        pDeclarator->Qualifiers.bIsDestructor = true;
        //pDeclarator->
        //pDeclaration->Declarators
      }
    }

    //achar o tipo
    //e marcar ele como tendo destrutor
    //String_Destroy(String* _dtor x);
    //p->Specifiers.pTypeSpecifierOpt
  }

  TDeclarator_Analise(pProgram, NULL, &p->Declarator, pStackNames);
}

static void TAnyDeclaration_Analise(TProgram* pProgram, TAnyDeclaration *pDeclaration)
{
  switch (pDeclaration->type)
  {
    case TStaticAssertDeclaration_ID:
      break;

    case TDeclaration_ID:
    {
      TVariablesMapStack array = TVARIABLESMAPSTACK_INIT;

      TDeclaration_Analise(pProgram, (TDeclaration*)pDeclaration, &array);
      TVariablesMapStack_Destroy(&array);
    }
    break;

    default:
      ASSERT(false);
      break;
  }
}

static void TDesignatorList_Analise(TProgram* pProgram, TDesignatorList *p, TVariablesMapStack* pStackNames)
{
  for (size_t i = 0; i < p->size; i++)
  {
    TDesignator* pItem = p->pItems[i];
    TDesignator_Analise(pProgram, pItem, pStackNames);
  }
}


static void TInitializerListItem_Analise(TProgram* pProgram,
    TDeclaration * pDeclaration,
    TDeclarator* pDeclarator,
    TInitializerListItem* p,
    TVariablesMapStack* pStackNames)
{
  if (p->pDesignatorList)
  {
    TDesignatorList_Analise(pProgram, p->pDesignatorList, pStackNames);
  }

  TInitializer_Analise(pProgram, pDeclaration, pDeclarator, p->pInitializer, pStackNames);
}


static void TDeclarations_Analise(TProgram* pProgram, TDeclarations *p)
{
  for (size_t i = 0; i < p->size; i++)
  {
    TAnyDeclaration* pItem = p->pItems[i];
    TAnyDeclaration_Analise(pProgram, pItem);
  }
}


void TProgram_Analize(TProgram * pProgram)
{
  for (size_t i = 0; i < pProgram->Declarations.size; i++)
  {
    TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
    int fileIndex = TAnyDeclaration_GetFileIndex(pItem);
    TFile *pFile = pProgram->Files2.pItems[fileIndex];
    const char * path = pFile->FullPath;
	//este cara aqui pode adicionar mais declaracoes antes dele
	//que vao ser as do template
	TAnyDeclaration_Analise(pProgram, pItem);
	//tb pode ser out declaracoes que serao a definicao das funcoes template
  }
  //adicionar no fim.. as funcao criadas.
  //se fosse fazer compialcao separada isso teria que ser
  //um aquivo separado json? que depois um linker iria juntar
}



#endif
