#pragma once

#include "..\CodePrint.h"

//implementa funcoes especiais
bool AllPlugin_BuildDestroy(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             bool bVariableNameIsPointer,
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool AllPlugin_Type_CodePrint(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                               bool b, StrBuilder* fp);

//Implementa 'default'
bool AllPlugin_CodePrint(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                          bool b,
                          StrBuilder* fp);
