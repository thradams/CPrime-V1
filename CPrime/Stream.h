#pragma once
#include "StringEx.h"
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>

struct SStream
{
    //name to identify this stream
    String NameOrFullPath;
    String FullDir2;

    //stream content and length
    String Text;
    int TextLen;

    int CurrentPos;
    wchar_t CurrentChar;

    int CurrentLine;
    int CurrentCol;

};



bool SStream_Init(struct SStream* pfStream,
    const char* name,
    const char* psz);

bool SStream_InitFile(struct SStream* pfStream,
    const char* fileName);

void SStream_Destroy(struct SStream* pfStream);

wchar_t SStream_LookAhead(struct SStream* pStream);

void SStream_Match(struct SStream* pStream);
bool SStream_MatchChar(struct SStream* pStream, wchar_t ch);

