#pragma once
#pragma source

#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"


void SyntaxTree_PrintAstToFile(struct SyntaxTree* pProgram,
                               const char* fileName,
                               const char* inputFileName);



void PrintLiteralString(FILE* fp, const char* psz);
