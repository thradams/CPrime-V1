#pragma once

#include "..\CodePrint.h"

//implementa funcoes especiais
bool UnionPlugin_BuildDestroy(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             bool bVariableNameIsPointer,
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool UnionPlugin_Type_CodePrint(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                               bool b, StrBuilder* fp);

//Implementa 'default'
bool UnionPlugin_CodePrint(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                          bool b,
                          StrBuilder* fp);
