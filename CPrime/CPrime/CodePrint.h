#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "..\Parser\Ast.h"
#include "..\Base\StrBuilder.h"
#include "..\Parser\Macro.h"
#include "..\Base\Map.h"

typedef struct Options
{
    bool bExpandMacros;
    bool bIncludeComments;
    //MacroMap  Expanded;
    StrBuilder TemplateDeclarations;
    StrBuilder TemplateInstanciation;
    Map  Templates;
} Options;

#define OPTIONS_INIT {false, true, STRBUILDER_INIT, STRBUILDER_INIT , MAP_INIT}
void Options_Destroy(Options* options);
 
void TProgram_PrintCodeToFile(TProgram * pProgram,
                              Options* options,
                              const char * fileName,	                        
	                            const char* userpath);

