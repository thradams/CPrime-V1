#pragma once

#include "..\CodePrint.h"

//implementa funcoes especiais
void ListPlugin_BuildDestroy(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             bool bVariableNameIsPointer,
                             BuildType buildType);

//instancia o tipo
bool ListPlugin_Type_CodePrint(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                               bool b, StrBuilder* fp);

//Implementa 'default'
bool ListPlugin_CodePrint(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                          bool b,
                          StrBuilder* fp);
