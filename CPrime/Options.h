#pragma once
#pragma source
#include <stdbool.h>

enum CompilerTarget
{
    CompilerTarget_Annotated,
    CompilerTarget_Preprocessed,
    CompilerTarget_CXX
};

struct Options
{
    bool bExpandMacros;
    bool bIncludeComments /*@=1*/;

    enum CompilerTarget Target;

    //imprime na forma para declarar um tipo, remove o resto
    bool bCannonical;

    bool bAmalgamate;

    bool bNoImplicitTag;
};

#define OPTIONS_INIT {false, true, CompilerTarget_Annotated,  false, false, false}
void Options_Destroy(struct Options* options);