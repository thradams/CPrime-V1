#pragma once

#include "..\CodePrint.h"

//implementa funcoes especiais
bool UnionPlugin_InstanciateSpecialFunctions(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool UnionPlugin_InstanciateType(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                                StrBuilder* fp);

//Implementa 'default'
bool UnionPlugin_InstanciateFunction(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                          
                          StrBuilder* fp);
