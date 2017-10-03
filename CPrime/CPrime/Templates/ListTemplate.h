#pragma once

#include "..\CodePrint.h"

//implementa funcoes especiais
bool ListPlugin_InstanciateSpecialFunctions(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                           
                             BuildType buildType,
    StrBuilder* fp);

//instancia o tipo
bool ListPlugin_InstanciateType(TProgram* program,
                               Options * options,
                               TStructUnionSpecifier* p,
                                StrBuilder* fp);

//Implementa 'default'
bool ListPlugin_InstanciateFunction(TProgram* program,
                          Options * options,
                          TDeclaration* p,
                        
                          StrBuilder* fp);
