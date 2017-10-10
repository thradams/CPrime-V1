#include "CodePrint.h"
#include "Array.h"
#include "Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "ListTemplate.h"
#include "UnionTemplate.h"
#include "MapTemplate.h"
#include "ArrayTemplate.h"

#define SIZEOFARRAY(x) (sizeof(x)/sizeof((x)[0]))

bool (*InstanciateSpecialFunctionsFunctions[])(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    BuildType buildType,
    StrBuilder* fp) = 
{
    ListPlugin_InstanciateSpecialFunctions,
    UnionPlugin_InstanciateSpecialFunctions,
    MapPlugin_InstanciateSpecialFunctions,
    ArrayPlugin_InstanciateSpecialFunctions
};

bool(*Type_CodePrint[])(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    StrBuilder* fp) =
{
    ListPlugin_InstanciateType,
    UnionPlugin_InstanciateType,
    MapPlugin_InstanciateType,
    ArrayPlugin_InstanciateType
};
bool(*CodePrint[])(TProgram* program,
    Options * options,
    TDeclaration* p,
    
    StrBuilder* fp) =
{
    ListPlugin_InstanciateFunction,
    UnionPlugin_InstanciateFunction,
    MapPlugin_InstanciateFunction,
    ArrayPlugin_InstanciateFunction
};


//Instancia as funcoes especias new create delete
bool AllPlugin_InstanciateSpecialFunctions(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
 
    BuildType buildType,
    StrBuilder* fp)
{
    bool bInstanciated = false;
    
    for (int i = 0;  i < SIZEOFARRAY(InstanciateSpecialFunctionsFunctions); i++)
    {
        bInstanciated = InstanciateSpecialFunctionsFunctions[i](program,
            pStructUnionSpecifier,
            pVariableName,
           
            buildType,
            fp);
        if (bInstanciated)
            break;
    }
    return bInstanciated;
}


void Output_Append(StrBuilder* p,
    Options* options,
    const char* source);

//Gera estrutura de ad
bool AllPlugin_InstanciateType(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    StrBuilder* fp)
{

    bool bInstanciated = false;
    for (int i = 0; i < 4/* SIZEOFARRAY(Type_CodePrint)*/; i++)
    {
        bInstanciated = Type_CodePrint[i](program,
            options,
            p,
          
            fp);
        if (bInstanciated)
            break;
    }
 
    return bInstanciated;
}


bool IsSuffix(const char* s, const char* suffix);
TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers);

//Implementa 'default'
bool AllPlugin_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,    
    StrBuilder* fp)
{
    bool bInstanciated = false;
    for (int i = 0; i < SIZEOFARRAY(CodePrint); i++)
    {
        bInstanciated = CodePrint[i](program,
            options,
            p,            
            fp);
        if (bInstanciated)
            break;
    }
    return bInstanciated;
}
