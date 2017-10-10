#pragma once

#include "CodePrint.h"

//implementa funcoes especiais
bool AllPlugin_InstanciateSpecialFunctions(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool AllPlugin_InstanciateType(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                               StrBuilder* fp);

//Implementa 'default'
bool AllPlugin_CodePrint(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                          StrBuilder* fp);
