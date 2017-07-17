#pragma once

#include "CodePrint.h"

bool StructTemplate_CodePrint(TProgram* program, Options * options, TStructUnionSpecifier* p, bool b, StrBuilder* fp);

bool Std_Template_CodePrint(TProgram* program,
                            Options * options,
                            TDeclaration* p,
                            bool b,
                            StrBuilder* fp);
