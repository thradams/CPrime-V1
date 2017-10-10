#pragma once

#include "CodePrint.h"

//implementa funcoes especiais
bool MapPlugin_InstanciateSpecialFunctions(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool MapPlugin_InstanciateType(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                                StrBuilder* fp);

//Implementa 'default'
bool MapPlugin_InstanciateFunction(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                          
                          StrBuilder* fp);
