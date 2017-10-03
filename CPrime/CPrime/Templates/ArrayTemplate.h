#pragma once

#include "..\CodePrint.h"

//implementa funcoes especiais
bool ArrayPlugin_InstanciateSpecialFunctions(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool ArrayPlugin_InstanciateType(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                               StrBuilder* fp);

//Implementa 'default'
bool ArrayPlugin_InstanciateFunction(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                        
                          StrBuilder* fp);
