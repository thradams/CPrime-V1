#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "ListTemplate.h"
#include "UnionTemplate.h"
#include "MapTemplate.h"
#include "ArrayTemplate.h"

bool (*BuildDestroyFunctions[])(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    bool bVariableNameIsPointer,
    BuildType buildType,
    StrBuilder* fp) = 
{
    ListPlugin_BuildDestroy,
    UnionPlugin_BuildDestroy,
    MapPlugin_BuildDestroy,
    ArrayPlugin_BuildDestroy
};


//Instancia as funcoes especias new create delete
void AllPlugin_BuildDestroy(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    bool bVariableNameIsPointer,
    BuildType buildType,
    StrBuilder* fp)
{
    bool bInstanciated = false;
    for (int i = 0; 
         i < sizeof(BuildDestroyFunctions) / sizeof(BuildDestroyFunctions[0]); 
         i++)
    {
        bInstanciated = BuildDestroyFunctions[i](program,
            pStructUnionSpecifier,
            pVariableName,
            bVariableNameIsPointer,
            buildType,
            fp);
        if (bInstanciated)
            break;
    }
    //return bInstanciated;
}


void Output_Append(StrBuilder* p,
    const char* source);

//Gera estrutura de ad
bool AllPlugin_Type_CodePrint(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    bool b, StrBuilder* fp)
{
    ListPlugin_Type_CodePrint(program,
                              options,
                              p,
                              b, fp);

    UnionPlugin_Type_CodePrint(program,
                              options,
                              p,
                              b, fp);

    MapPlugin_Type_CodePrint(program,
                               options,
                               p,
                               b, fp);

    ArrayPlugin_Type_CodePrint(program,
                             options,
                             p,
                             b, fp);


    return true;
}


bool IsSuffix(const char* s, const char* suffix);
TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers);

//Implementa 'default'
bool AllPlugin_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    ListPlugin_CodePrint( program,
                         options,
                         p,
                         b,
                         fp);

    MapPlugin_CodePrint(program,
                         options,
                         p,
                         b,
                         fp);

    UnionPlugin_CodePrint(program,
                        options,
                        p,
                        b,
                        fp);

    ArrayPlugin_CodePrint(program,
                          options,
                          p,
                          b,
                          fp);

    return false;
}
