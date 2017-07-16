#pragma once
#include "Result.h"
#include "StringEx.h"
#include <stdio.h>

typedef struct
{
    //name to identify this stream
    String NameOrFullPath;
    String FullDir2;

    //stream content and length
    String text;
    size_t text_length;

    size_t position;
    wchar_t currentChar;

    int currentLine;
    int currentCol;

} SStream;



Result SStream_Init(SStream* pfStream,
                    const char* name,
                    const char* psz);

Result SStream_InitFile(SStream* pfStream,
                        const char* fileName);

void SStream_Destroy(SStream* pfStream);

wchar_t SStream_LookAhead(SStream* pStream);

void SStream_Match(SStream* pStream);
bool SStream_MatchChar(SStream* pStream, wchar_t ch);
