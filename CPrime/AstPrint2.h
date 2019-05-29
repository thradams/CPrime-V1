#pragma once
#pragma source

#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"
#include "StrBuilder.h"
#include "Macro.h"
#include "Map.h"
#include "Options.h"



void TProgram_PrintAstToXML(TProgram * pProgram,
                            const char * fileName,
                            const char * inputFileName);
