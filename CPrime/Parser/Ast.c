#include "Ast.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

void TCompoundStatement_Destroy(TCompoundStatement *p)
{
  ArrayT_Destroy(TBlockItem, &p->BlockItemList);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TLabeledStatement_Destroy(TLabeledStatement *p)
{
  TStatement_Delete(p->pStatementOpt);
  String_Destroy(&p->Identifier);
  TExpression_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TForStatement_Destroy(TForStatement *p)
{
  TAnyDeclaration_Delete(p->pInitDeclarationOpt);
  TExpression_Delete(p->pExpression1);
  TExpression_Delete(p->pExpression2);
  TExpression_Delete(p->pExpression3);
  TStatement_Delete(p->pStatement);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
  TScannerItemList_Destroy(&p->ClueList4);
}

void TWhileStatement_Destroy(TWhileStatement *p)
{
  TExpression_Delete(p->pExpression);
  TStatement_Delete(p->pStatement);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
}

void TReturnStatement_Destroy(TReturnStatement *p)
{
  TExpression_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TDoStatement_Destroy(TDoStatement *p)
{
  TExpression_Delete(p->pExpression);
  TStatement_Delete(p->pStatement);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
  TScannerItemList_Destroy(&p->ClueList4);

}

void TExpressionStatement_Destroy(TExpressionStatement *p)
{
  TExpression_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
}

void TJumpStatement_Destroy(TJumpStatement *p)
{
  TExpression_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TAsmStatement_Destroy(TAsmStatement *p)
{
  p->Type.Type = TypeNull;
  TScannerItemList_Destroy(&p->ClueList);
}

void TSwitchStatement_Destroy(TSwitchStatement *p)
{
  TExpression_Delete(p->pConditionExpression);
  TStatement_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
}

void TIfStatement_Destroy(TIfStatement *p)
{
  TExpression_Delete(p->pConditionExpression);
  TStatement_Delete(p->pStatement);
  TStatement_Delete(p->pElseStatement);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);

}

void TStatement_Destroy(TStatement* p)
{
  switch (p->Type)
  {
  case TExpressionStatement_ID:
    TExpressionStatement_Destroy((TExpressionStatement*)p);
    break;
  case TSwitchStatement_ID:
    TSwitchStatement_Destroy((TSwitchStatement*)p);
    break;
  case TLabeledStatement_ID:
    TLabeledStatement_Destroy((TLabeledStatement*)p);
    break;
  case TForStatement_ID:
    TForStatement_Destroy((TForStatement*)p);
    break;
  case TJumpStatement_ID:
    TJumpStatement_Destroy((TJumpStatement*)p);
    break;
  case TAsmStatement_ID:
    TAsmStatement_Destroy((TAsmStatement*)p);
    break;
  case TCompoundStatement_ID:
    TCompoundStatement_Destroy((TCompoundStatement*)p);
    break;
  case TIfStatement_ID:
    TIfStatement_Destroy((TIfStatement*)p);
    break;
  case TDoStatement_ID:
    TDoStatement_Destroy((TDoStatement*)p);
    break;
  case TReturnStatement_ID:
    TReturnStatement_Destroy((TReturnStatement*)p);
    break;
  default:
    ASSERT(false);
    break;
  }
}

void TBlockItem_Destroy(TBlockItem* p)
{

  switch (p->Type)
  {
  case TDeclaration_ID:
    TDeclaration_Destroy((TDeclaration*)p);
    break;
  case TJumpStatement_ID:
    TJumpStatement_Destroy((TJumpStatement*)p);
    break;
  case TAsmStatement_ID:
    TAsmStatement_Destroy((TAsmStatement*)p);
    break;
  case TSwitchStatement_ID:
    TSwitchStatement_Destroy((TSwitchStatement*)p);
    break;
  case TExpressionStatement_ID:
    TExpressionStatement_Destroy((TExpressionStatement*)p);
    break;
  case TCompoundStatement_ID:
    TCompoundStatement_Destroy((TCompoundStatement*)p);
    break;
  case TLabeledStatement_ID:
    TLabeledStatement_Destroy((TLabeledStatement*)p);
    break;
  case TForStatement_ID:
    TForStatement_Destroy((TForStatement*)p);
    break;
  case TWhileStatement_ID:
    TWhileStatement_Destroy((TWhileStatement*)p);
    break;
  case TIfStatement_ID:
    TIfStatement_Destroy((TIfStatement*)p);
    break;
  case TReturnStatement_ID:
    TReturnStatement_Destroy((TReturnStatement*)p);
    break;
  case TDoStatement_ID:
    TDoStatement_Destroy((TDoStatement*)p);
    break;
    //Statement
  default:
    ASSERT(false);
    break;
  }

}

void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue* p)
{
  TExpression_Delete(p->pExpressionOpt);
  String_Destroy(&p->lexeme);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TPostfixExpressionCore_Destroy(TPostfixExpressionCore* p)
{
  TInitializerList_Destroy(&p->InitializerList);
  String_Destroy(&p->Identifier);
  String_Destroy(&p->lexeme);
  TExpression_Delete(p->pExpressionLeft);
  TExpression_Delete(p->pExpressionRight);
  TTypeName_Delete(p->pTypeName);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
  TScannerItemList_Destroy(&p->ClueList4);
}

void TBinaryExpression_Destroy(TBinaryExpression* p)
{
  TExpression_Delete(p->pExpressionLeft);
  TExpression_Delete(p->pExpressionRight);
  TScannerItemList_Destroy(&p->ClueList0);
  
}

void TUnaryExpressionOperator_Destroy(TUnaryExpressionOperator* p)
{
  TExpression_Delete(p->pExpressionLeft);
  TTypeName_Destroy(&p->TypeName);  
  TScannerItemList_Destroy(&p->ClueList0);
}

void TCastExpressionType_Destroy(TCastExpressionType* p)
{
  TExpression_Delete(p->pExpression);
  TTypeName_Destroy(&p->TypeName);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TTernaryExpression_Destroy(TTernaryExpression* p)
{
  TExpression_Delete(p->pExpressionLeft);
  TExpression_Delete(p->pExpressionMiddle);
  TExpression_Delete(p->pExpressionRight);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TExpression_Destroy(TExpression* p)
{
  switch (p->Type)
  {
    CASE(TPrimaryExpressionValue) :
      TPrimaryExpressionValue_Destroy((TPrimaryExpressionValue*)p);
    break;
    CASE(TPostfixExpressionCore) :
      TPostfixExpressionCore_Destroy((TPostfixExpressionCore*)p);
    break;
    CASE(TBinaryExpression) :
      TBinaryExpression_Destroy((TBinaryExpression*)p);
    break;
    CASE(TUnaryExpressionOperator) :
      TUnaryExpressionOperator_Destroy((TUnaryExpressionOperator*)p);
    break;
    CASE(TCastExpressionType) :
      TCastExpressionType_Destroy((TCastExpressionType*)p);
    break;

    CASE(TTernaryExpression) :
      TTernaryExpression_Destroy((TTernaryExpression*)p);
    break;

  default:
    ASSERT(false);
    break;
  }

}


void TStaticAssertDeclaration_Destroy(TStaticAssertDeclaration* p)
{
  p->Type.Type = TypeNull;
  TExpression_Delete(p->pConstantExpression);
  String_Destroy(&p->Text);

  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
  TScannerItemList_Destroy(&p->ClueList4);
  TScannerItemList_Destroy(&p->ClueList5);
}

void TEnumerator_Destroy(TEnumerator* p)
{
  String_Destroy(&p->Name);
  TExpression_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
}

void TEnumSpecifier_Destroy(TEnumSpecifier* p)
{
  String_Destroy(&p->Name);
  List_Destroy(TEnumerator, &p->EnumeratorList);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);

}

void TStructUnionSpecifier_Destroy(TStructUnionSpecifier* p)
{
  String_Destroy(&p->Name);
  String_Destroy(&p->TemplateName);
  ArrayT_Destroy(TAnyStructDeclaration, &p->StructDeclarationList);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
  TTemplateTypeSpecifierArgumentList_Destroy((TTemplateTypeSpecifierArgumentList*)&p->Args);
}

void TSingleTypeSpecifier_Destroy(TSingleTypeSpecifier* p)
{
  String_Destroy(&p->TypedefName);
  TScannerItemList_Destroy(&p->ClueList0);
}


void TTypeSpecifier_Destroy(TTypeSpecifier* p)
{
  switch (p->Type)
  {
  case TSingleTypeSpecifier_ID:
    TSingleTypeSpecifier_Destroy((TSingleTypeSpecifier*)p);
    break;
  case TEnumSpecifier_ID:
    TEnumSpecifier_Destroy((TEnumSpecifier*)p);
    break;
  case TStructUnionSpecifier_ID:
    TStructUnionSpecifier_Destroy((TStructUnionSpecifier*)p);
    break;
  default:
    ASSERT(false);
    break;
  }
}

void TDeclarator_Destroy(TDeclarator* p)
{
  List_Destroy(TPointer, &p->PointerList);
  TDirectDeclarator_Delete(p->pDirectDeclarator);
  TScannerItemList_Destroy(&p->ClueList);
}

void TInitDeclarator_Destroy(TInitDeclarator* p)
{
  //nao deletar aqui
  //TInitDeclarator_Delete(p->pInitDeclaratorNext);
  TDeclarator_Delete(p->pDeclarator);
  TInitializer_Delete(p->pInitializer);
  TScannerItemList_Destroy(&p->ClueList0);
}



void TDirectDeclarator_Destroy(TDirectDeclarator* p)
{
  String_Destroy(&p->Identifier);
  //TParameterList_Delete(p->pParametersOpt);
  //T/PointerList_Destroy(&p->PointerList);
  TDeclarator_Delete(p->pDeclarator);
  //TInitializer_Delete(p->pInitializer);
  //TExpression_Delete(p->pExpression);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
  TScannerItemList_Destroy(&p->ClueList2);
  TScannerItemList_Destroy(&p->ClueList3);
}


const char* TDeclarator_FindName(TDeclarator*   p)
{
  TDirectDeclarator* pDirectDeclarator = p->pDirectDeclarator;
  while (pDirectDeclarator != NULL)
  {
    if (pDirectDeclarator->Identifier != NULL)
      return pDirectDeclarator->Identifier;
    if (pDirectDeclarator->pDeclarator)
    {
      const char* name =
        TDeclarator_FindName(pDirectDeclarator->pDeclarator);
      if (name != NULL)
      {
        return name;
      }
    }
    pDirectDeclarator =
      pDirectDeclarator->pDirectDeclarator;
  }
  return NULL;
}

const char* TInitDeclarator_FindName(TInitDeclarator* p)
{
  ASSERT(p->pDeclarator != NULL);
  return TDeclarator_FindName(p->pDeclarator);
}



void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p)
{
  String_Destroy(&p->TypeName);
  //TScannerItemList_Destroy(&p->ClueList);
  
}



void TStructDeclaration_Destroy(TStructDeclaration* p)
{
  List_Destroy(TInitDeclarator, &p->DeclaratorList);
  TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
  //TTypeQualifier_Destroy(&p->Qualifier);
  TScannerItemList_Destroy(&p->ClueList1);
}

void TAnyStructDeclaration_Destroy(TAnyStructDeclaration* p)
{
  switch (p->Type)
  {
  case TStructDeclaration_ID:
    TStructDeclaration_Destroy((TStructDeclaration*)p);
    break;
  case TStaticAssertDeclaration_ID:
    TStaticAssertDeclaration_Destroy((TStaticAssertDeclaration*)p);
    break;
  default:
    ASSERT(false);
    break;
  }
}

bool TPointerList_IsPointer(TPointerList* pPointerlist)
{
  bool bIsPointer = false;
  ForEachListItem(TPointer, pItem, pPointerlist)
  {
    if (pItem->bPointer)
    {
      bIsPointer = true;
      break;
    }
  }
  return bIsPointer;
}

void TPointer_Destroy(TPointer* p)
{
  //p->Qualifier.
  TScannerItemList_Destroy(&p->ClueList0);
}

bool TSpecifierQualifierList_IsTypedef(TSpecifierQualifierList* p)
{
    ASSERT(false);
    return false;
}
const char* TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList* p)
{
    ASSERT(false);
    return "";
}

void TTypeQualifier_Destroy(TTypeQualifier* p)
{
    TScannerItemList_Destroy(&p->ClueList0);
}

void TStorageSpecifier_Destroy(TStorageSpecifier* p)
{
    TScannerItemList_Destroy(&p->ClueList0);
}

void TAtomicTypeSpecifier_Destroy(TAtomicTypeSpecifier* p)
{
    TTypeName_Destroy(&p->TypeName);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    
}

void TTemplateTypeSpecifierArgument_Destroy(TTemplateTypeSpecifierArgument* p)
{
    TTypeName_Destroy(&p->TypeName);
}

void TTemplateTypeSpecifier_Destroy(TTemplateTypeSpecifier* p)
{    
    TTemplateTypeSpecifierArgumentList_Destroy(&p->Args);
    TScannerItemList_Destroy(&p->ClueList0);
    String_Destroy(&p->Identifier);
}


void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers)
{
    ForEachListItem(TTypeSpecifier, pItem, pDeclarationSpecifiers)
    {
        TTypeSpecifier* pNext = pItem->pNext;
        switch (pItem->Type)
        {
            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)pItem);
            break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_Delete((TStructUnionSpecifier*)pItem);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_Delete((TEnumSpecifier*)pItem);
            break;

            CASE(TStorageSpecifier) :
                TStorageSpecifier_Delete((TStorageSpecifier*)pItem);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_Delete((TTypeQualifier*)pItem);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_Delete((TFunctionSpecifier*)pItem);
            break;
            CASE(TAlignmentSpecifier) :
                TAlignmentSpecifier_Delete((TAlignmentSpecifier*)pItem);
            break;
            default:
            ASSERT(false);
            break;
        }
        pItem = pNext;
        if (pItem == NULL)
        {
            break;
        }
    }
}



const char* TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    const char* typeName = NULL;

    ForEachListItem(TSpecifier, pItem, pDeclarationSpecifiers)
    {
        TSingleTypeSpecifier* pSingleTypeSpecifier =
            TSpecifier_As_TSingleTypeSpecifier(pItem);
        if (pSingleTypeSpecifier != NULL)
        {
            if (pSingleTypeSpecifier->bIsTypeDef)
            {
                typeName = pSingleTypeSpecifier->TypedefName;
                break;
            }
        }
    }
    return typeName;
}

void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    ForEachListItem(TTypeSpecifier, pItem, pDeclarationSpecifiers)
    {
        TTypeSpecifier* pNext = pItem->pNext;
        switch (pItem->Type)
        {   
            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)pItem);
            break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_Delete((TStructUnionSpecifier*)pItem);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_Delete((TEnumSpecifier*)pItem);
            break;

            CASE(TStorageSpecifier) : 
                TStorageSpecifier_Delete((TStorageSpecifier*)pItem);
                break;
            CASE(TTypeQualifier) : 
                TTypeQualifier_Delete((TTypeQualifier*)pItem);
                break;
            CASE(TFunctionSpecifier) : 
                TFunctionSpecifier_Delete((TFunctionSpecifier*) pItem);
                break;
            
                CASE(TAlignmentSpecifier) : 
                TAlignmentSpecifier_Delete((TAlignmentSpecifier*)pItem);
                break;
                
                CASE(TTemplateTypeSpecifier) :
                    TTemplateTypeSpecifier_Delete((TTemplateTypeSpecifier*)pItem);
                break;
            default:
            ASSERT(false);
            break;
        }
        pItem = pNext;
        if (pItem == NULL)
            break;
    }
}

TDeclarator* TDeclaration_FindDeclarator(TDeclaration*  p, const char* name)
{
  if (p == NULL)
  {
    return NULL;
  }
  TDeclarator*  pResult = NULL;

  ForEachListItem(TInitDeclarator, pInitDeclarator, &p->InitDeclaratorList)
  {
    if (pInitDeclarator->pDeclarator &&
      pInitDeclarator->pDeclarator->pDirectDeclarator &&
      pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier)
    {
      if (strcmp(pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier, name) == 0)
      {
        pResult = pInitDeclarator->pDeclarator;
        break;
      }
    }
  }
  return pResult;
}

void TFunctionSpecifier_Destroy(TFunctionSpecifier* p)
{
    TScannerItemList_Destroy(&p->ClueList0);
}

/*
bool TDeclaration_Is_FunctionDeclaration(TDeclaration*  p)
{
  if (p != NULL && p->Declarators.size == 1)
  {
    if (p->Declarators.pItems[0]->pParametersOpt != NULL)
    {
      if (p->pCompoundStatementOpt == NULL)
      {
        return true;
      }
    }
  }
  return false;
}
*/
/*
const char* TDeclaration_GetFunctionThis(TDeclaration*  p)
{
  const char*  thisName = NULL;
  if (p != NULL && p->Declarators.size == 1)
  {
    if (p->Declarators.pItems[0]->pParametersOpt != NULL &&
        p->Declarators.pItems[0]->pParametersOpt->size >= 1)
    {
        thisName = p->Declarators.pItems[0]->pParametersOpt->pItems[0]->Declarator.Name;
    }
  }
  return thisName;
}
*/

bool TDeclaration_Is_FunctionDefinition(TDeclaration*  p)
{
  return p != NULL && p->pCompoundStatementOpt != NULL;
}

bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p)
{
    bool bIsStructOrUnion = false;
    ForEachListItem(TSpecifier, pItem, &p->Specifiers)
    {
        if (TTypeSpecifier_As_TStructUnionSpecifier(pItem))
        {
            bIsStructOrUnion = true;
            break;
        }
        
    }
    return bIsStructOrUnion;
}

//bool TDeclaration_Is_EnumDeclaration(TDeclaration* p)
//{
  //return
//    TTypeSpecifier_As_TEnumSpecifier(p->Specifiers.pTypeSpecifierOpt) != NULL;
//}


void TTemplateParameter_Destroy(TTemplateParameter* p)
{
  String_Destroy(&p->Name);
}

void TDeclaration_Destroy(TDeclaration* p)
{
  TCompoundStatement_Delete(p->pCompoundStatementOpt);
  TDeclarationSpecifiers_Destroy(&p->Specifiers);
  List_Destroy(TInitDeclarator, &p->InitDeclaratorList);
  List_Destroy(TTemplateParameter, &p->TemplateParameters);
  TScannerItemList_Destroy(&p->ClueList0);
}

void TParameterDeclaration_Swap(TParameterDeclaration* a, TParameterDeclaration* b)
{
  TParameterDeclaration temp = *a;
  *a = *b;
  *b = temp;
}

void TParameterDeclaration_Destroy(TParameterDeclaration* p)
{
  TDeclarator_Destroy(&p->Declarator);
  TDeclarationSpecifiers_Destroy(&p->Specifiers);
  TScannerItemList_Destroy(&p->ClueList0);
}

void TParameterTypeList_Destroy(TParameterTypeList* p)
{
    TParameterList_Destroy(&p->ParameterList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration* pAnyDeclaration)
{
  TDeclaration *  pDeclaration = TAnyDeclaration_As_TDeclaration(pAnyDeclaration);
  if (pDeclaration != NULL)
  {
    return TDeclaration_Is_StructOrUnionDeclaration(pDeclaration);
  }

  return false;
}


bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    bool bResult = false;
    ForEachListItem(TTypeSpecifier, pItem, pDeclarationSpecifiers)
    {
        
        switch (pItem->Type)
        {
            CASE(TStorageSpecifier) :
                if (((TStorageSpecifier*)pItem)->bIsTypedef)
                {
                    bResult = true;
                }               
            break;
        }
        
        if (bResult)
        {
            break;
        }
    }
    return bResult;
}

bool TAnyDeclaration_IsTypedef(TAnyDeclaration* pDeclaration)
{
  bool bResult = false;
  switch (pDeclaration->Type)
  {
  case TDeclaration_ID:
  {
    TDeclaration* p = (TDeclaration*)pDeclaration;    
    bResult = TDeclarationSpecifiers_IsTypedef(&p->Specifiers);
  }
  break;
  default:
    ASSERT(false);
    break;
  }
  return bResult;
}

int TAnyDeclaration_GetFileIndex(TAnyDeclaration* pDeclaration)
{
  int result = -1;
  switch (pDeclaration->Type)
  {
  case TDeclaration_ID:
    result = ((TDeclaration*)pDeclaration)->FileIndex;
    break;
  case TStaticAssertDeclaration_ID:
    break;
  default:
    ASSERT(false);
    break;
  }
  return result;
}
void TAnyDeclaration_Destroy(TAnyDeclaration* pDeclaration)
{
  switch (pDeclaration->Type)
  {
  case TDeclaration_ID:
    TDeclaration_Destroy((TDeclaration*)pDeclaration);
    break;
  default:
    ASSERT(false);
    break;
  }
}

void TDesignation_Destroy(TDesignation* pDesignation)
{
    
    List_Destroy(TDesignator, &pDesignation->DesignatorList);
    TScannerItemList_Destroy(&pDesignation->ClueList0);
    
}

void TDesignator_Destroy(TDesignator* p)
{
  TExpression_Delete(p->pExpression);
  String_Destroy(&p->Name);
  TScannerItemList_Destroy(&p->ClueList0);
  TScannerItemList_Destroy(&p->ClueList1);
}

void  TInitializerListType_Destroy(TInitializerListType* pTInitializerListType)
{
  TInitializerList_Destroy(&pTInitializerListType->InitializerList);
  TScannerItemList_Destroy(&pTInitializerListType->ClueList0);
  TScannerItemList_Destroy(&pTInitializerListType->ClueList1);
}

void TInitializer_Destroy(TInitializer* p)
{
  if (p->Type == TInitializerListType_ID)
  {
    TInitializerListType_Destroy((TInitializerListType*)p);

  }
  else
  {
    TExpression_Destroy((TExpression*)p);
  }

}

void TInitializerListItem_Destroy(TInitializerListItem* p)
{
  List_Destroy(TDesignator, &p->DesignatorList);
  TInitializer_Delete(p->pInitializer);
  TScannerItemList_Destroy(&p->ClueList);
}


Result DeclarationsMap_Add(DeclarationsMap* p, const char* name, TAnyDeclaration* pData)
{
  return MultiMap_Add(p, name, pData);
}

TDeclaration* DeclarationsMap_FindDeclaration(DeclarationsMap* p, const char* name)
{
    if (name == NULL)
    {
        return NULL;
    }

  Bucket *  pBucket =
    MultiMap_FindBucket(p, name);
  if (pBucket)
  {
    for (size_t j = 0; j < pBucket->size; j++)
    {
      if (strcmp(pBucket->data[j]->key, name) == 0)
      {
        return TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);
      }
    }
  }
  return NULL;
}

TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name)
{
  return DeclarationsMap_FindDeclaration(&p->Symbols, name);
}

TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name)
{
  TDeclaration*  pDeclaration = NULL;


  Bucket *  pBucket =
    MultiMap_FindBucket(&p->Symbols, name);
  if (pBucket)
  {
    for (size_t j = 0; j < pBucket->size; j++)
    {
      if (strcmp(pBucket->data[j]->key, name) == 0)
      {
        TDeclaration*  pDeclaration0 =
          TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);

        if (pDeclaration0 != NULL /* &&
            pDeclaration0->pCompoundStatementOpt == NULL*/)
        {
          pDeclaration = pDeclaration0;
          break;
        }
      }
    }
  }
  return pDeclaration;
}


TDeclaration* TProgram_FindFunctionDefinition(TProgram* p, const char* name)
{
  TDeclaration*  pDeclaration = NULL;
  Bucket *  pBucket = MultiMap_FindBucket(&p->Symbols, name);
  if (pBucket)
  {
    for (size_t j = 0; j < pBucket->size; j++)
    {
      if (strcmp(pBucket->data[j]->key, name) == 0)
      {
        TDeclaration*  pDeclaration0 =
          TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);

        if (pDeclaration0 != NULL &&
          pDeclaration0->pCompoundStatementOpt != NULL)
        {
          pDeclaration = pDeclaration0;
          break;
        }
      }
    }
  }
  return pDeclaration;
}


//Retorna a declaracao final do tipo entrando em cada typedef. 
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName)
{
  TDeclaration*  pDeclarationResult = NULL;
  for (;;)
  {
    Bucket *  pBucket =
      MultiMap_FindBucket(&p->Symbols, typeName);
    if (pBucket)
    {
      TDeclaration*  pDeclaration = NULL;
      for (size_t j = 0; j < pBucket->size; j++)
      {
        pDeclaration = NULL;
        if (strcmp(pBucket->data[j]->key, typeName) == 0)
        {
          pDeclaration = TAnyDeclaration_As_TDeclaration((TAnyDeclaration *)pBucket->data[j]->data);
          if (pDeclaration != NULL) 
          {
              if (TDeclarationSpecifiers_IsTypedef(&pDeclaration->Specifiers))
              {
                  TSingleTypeSpecifier *  pSingleTypeSpecifier = TTypeSpecifier_As_TSingleTypeSpecifier(pDeclaration->Specifiers.pHead);
                  if (pSingleTypeSpecifier != NULL)
                  {
                      if (pSingleTypeSpecifier->bIsTypeDef)
                      {
                          typeName = pSingleTypeSpecifier->TypedefName;
                          break;
                      }
                      else
                      {
                          //int etc..
                          pDeclarationResult = pDeclaration;
                          break;
                      }
                  }
                  else
                  {
                      pDeclarationResult = pDeclaration;
                      //enum or struct union
                      TStructUnionSpecifier* pTStructUnionSpecifier = NULL;
                      if (pDeclarationResult->Specifiers.pHead->pNext)
                      {
                          pTStructUnionSpecifier =
                              TSpecifier_As_TStructUnionSpecifier(pDeclarationResult->Specifiers.pHead->pNext);
                      }

                      if (pTStructUnionSpecifier)
                      {
                          if (pTStructUnionSpecifier->StructDeclarationList.size > 0)
                              break;
                      }
                      else
                      {
                          pDeclarationResult = pDeclaration;
                          break;
                      }
                  }
              }
              else
              {
                  pDeclarationResult = pDeclaration;
                  TStructUnionSpecifier* pTStructUnionSpecifier = NULL;
                  if (pDeclarationResult->Specifiers.pHead->pNext)
                  {
                      pTStructUnionSpecifier = TSpecifier_As_TStructUnionSpecifier(pDeclarationResult->Specifiers.pHead->pNext);
                  }
                  if (pTStructUnionSpecifier)
                  {
                      if (pTStructUnionSpecifier->StructDeclarationList.size > 0)
                          break;
                  }
                  else
                  {
                      pDeclarationResult = pDeclaration;
                      break;
                  }
              }
          }//declaration
          else
          {
              //nao achou
              break;
          }
        }//key
      }//for
      if (pDeclarationResult != NULL)
      {
        break; //ok achou
      }

      if (pDeclaration == NULL)
      {
        break;
      }
    }
    else
    {
      break;
    }
  }//for
  return pDeclarationResult;
}

/*void TDeclarations_Init(TDeclarations* p)
{
  TDeclarations temp = TDECLARATIONS_INIT;
  *p = temp;
}*/

void TProgram_Destroy(TProgram * p)
{

  StrArray_Destroy(&p->MySourceDir);

  Map_Destroy(&p->EnumMap, NULL);
  ArrayT_Destroy(TAnyDeclaration, &p->Declarations);
  ArrayT_Destroy(TFile, &p->Files2);
  DeclarationsMap_Destroy(&p->Symbols);
  MacroMap_Destroy(&p->Defines);
}



///////////////////////////////////////////

static bool TPostfixExpressionCore_CodePrint2(TPostfixExpressionCore * p,
  int *pResult)
{

  int result = *pResult;

  if (p->pExpressionLeft)
  {
    int left;
    EvaluateConstantExpression(p->pExpressionLeft, &left);
  }

  //if (p->pInitializerList)
  {
    //falta imprimeir typename
    //TTypeName_Print*
    //b = TInitializerList_CodePrint(p->pInitializerList, b, fp);
  }

  switch (p->token)
  {
  case TK_FULL_STOP:
    //fprintf(fp, ".%s", p->Identifier);
    ASSERT(false);
    break;
  case TK_ARROW:
    //fprintf(fp, "->%s", p->Identifier);
    //b = true;
    ASSERT(false);
    break;

  case TK_LEFT_SQUARE_BRACKET:
  {
    int index;
    //fprintf(fp, "[");
    EvaluateConstantExpression(p->pExpressionRight, &index);
    //fprintf(fp, "]");
    ASSERT(false);
  }
  break;

  case TK_LEFT_PARENTHESIS:
  {
    EvaluateConstantExpression(p->pExpressionRight, &result);
  }
  break;

  case TK_PLUSPLUS:
    ASSERT(false);
    break;
  case TK_MINUSMINUS:
    ASSERT(false);
    break;
  }



  if (p->pNext)
  {
    int result2 = result;
    TPostfixExpressionCore_CodePrint2(p->pNext, &result2);
    result = result2;
  }

  return true;
}

//Criado para avaliacao do #if
//Tem que arrumar para fazer os casts do enum
bool EvaluateConstantExpression(TExpression *  p, int *pResult)
{
  int result = -987654321;

  if (p == NULL)
  {
    return false;
  }
  bool b = false;

  switch (p->Type)
  {
    CASE(TBinaryExpression) :
    {
      TBinaryExpression* pBinaryExpression =
        (TBinaryExpression*)p;

      int left;
      b = EvaluateConstantExpression(pBinaryExpression->pExpressionLeft, &left);

      int right;
      b = EvaluateConstantExpression(pBinaryExpression->pExpressionRight, &right);

      switch (pBinaryExpression->token)
      {
      case TK_ASTERISK:
        result = (left * right);
        b = true;
        break;
      case TK_PLUS_SIGN:
        result = (left + right);
        b = true;
        break;
      case TK_HYPHEN_MINUS:
        result = (left - right);
        b = true;
        break;
      case TK_ANDAND:
        result = (left && right);
        b = true;
        break;
      case TK_OROR:
        result = (left || right);
        b = true;
        break;
      case TK_NOTEQUAL:
        result = (left != right);
        b = true;
        break;
      case TK_EQUALEQUAL:
        result = (left == right);
        b = true;
        break;
      case TK_GREATEREQUAL:
        result = (left >= right);
        b = true;
        break;
      case TK_LESSEQUAL:
        result = (left <= right);
        b = true;
        break;
      case TK_GREATER_THAN_SIGN:
        result = (left > right);
        b = true;
        break;
      case TK_LESS_THAN_SIGN:
        result = (left < right);
        b = true;
        break;
      case TK_AMPERSAND:
        result = (left & right);
        b = true;
        break;
      case TK_GREATERGREATER:
        result = (left >> right);
        b = true;
        break;
      case TK_LESSLESS:
        result = (left << right);
        b = true;
        break;
      case TK_VERTICAL_LINE:
        result = (left | right);
        b = true;
        break;

      case TK_SOLIDUS:
        if (right != 0)
        {
          result = (left / right);
          b = true;
        }
        else
        {
          b = false;
          //SetError
        }
        break;
        

      default:
        //TODO ADD THE OPERADOR?
        ASSERT(false);
        b = false;
      }

      //if (pBinaryExpression->)
    }
    break;

    CASE(TTernaryExpression) :
    {
      int e1, e2, e3;
      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionLeft, &e1);

      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionMiddle, &e2);

      b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionRight, &e3);
      ASSERT(false);
    }
    break;

    CASE(TPrimaryExpressionValue) :
    {
      TPrimaryExpressionValue* pPrimaryExpressionValue =
        (TPrimaryExpressionValue*)p;

      if (pPrimaryExpressionValue->pExpressionOpt != NULL)
      {
        b = EvaluateConstantExpression(pPrimaryExpressionValue->pExpressionOpt, &result);
      }
      else
      {
        switch (pPrimaryExpressionValue->token)
        {
        case TK_IDENTIFIER:
          result = 0; //para macro
          b = true;
          break;

        case TK_DECIMAL_INTEGER:
          result = atoi(pPrimaryExpressionValue->lexeme);
          b = true;
          break;

        case TK_HEX_INTEGER:
          result = strtol(pPrimaryExpressionValue->lexeme, NULL, 16);
          b = true;
          break;

        case TK_CHAR_LITERAL:
          if (pPrimaryExpressionValue->lexeme != NULL)
          {
            //vem com 'A'
            result = pPrimaryExpressionValue->lexeme[1];
            b = true;
          }
          else
          {
            result = 0;
          }
          break;
        default:
          b = false;
          ASSERT(0);
          break;
        }

      }
    }
    break;

    CASE(TPostfixExpressionCore) :
    {
      TPostfixExpressionCore* pPostfixExpressionCore =
        (TPostfixExpressionCore*)p;
      b = TPostfixExpressionCore_CodePrint2(pPostfixExpressionCore, &result);
      ASSERT(false);
    }
    break;

    CASE(TUnaryExpressionOperator) :
    {

      TUnaryExpressionOperator* pTUnaryExpressionOperator =
        (TUnaryExpressionOperator*)p;

      if (pTUnaryExpressionOperator->token == TK_SIZEOF)
      {

        //if (TDeclarationSpecifiers_IsTypedef(pTUnaryExpressionOperator->TypeName.SpecifierQualifierList))
        {

          //b = TTypeQualifier_CodePrint2(&pTUnaryExpressionOperator->TypeName.qualifiers, false, fp);
          //b = TTypeSpecifier_CodePrint2(pTUnaryExpressionOperator->TypeName.pTypeSpecifier, b, fp);
          // b = TDeclarator_CodePrint(&pTUnaryExpressionOperator->TypeName.declarator, b, fp);


        }
        //else
        {
          b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionLeft, &result);
        }
      }
      else
      {
        int localResult;
        b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionLeft, &localResult);
        switch (pTUnaryExpressionOperator->token)
        {
        case TK_EXCLAMATION_MARK:
          result = !localResult;
          b = true;
          break;
        case TK_HYPHEN_MINUS:
          result = -localResult;
          b = true;
          break;
        default:
          ASSERT(false);
        }
      }


    }
    break;

    CASE(TCastExpressionType) :
    {
      TCastExpressionType * pCastExpressionType =
        (TCastExpressionType*)p;


      //b = TTypeQualifier_CodePrint2(&pCastExpressionType->TypeName.qualifiers, false, fp);
      //b = TTypeSpecifier_CodePrint2(pCastExpressionType->TypeName.pTypeSpecifier, b, fp);
      //b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.declarator, b, fp);

      b = EvaluateConstantExpression(pCastExpressionType->pExpression, &result);
      ASSERT(false);

    }
    break;

  default:
    ASSERT(false);
  }

  ASSERT(result != -987654321);
  *pResult = result;
  return b;
}

