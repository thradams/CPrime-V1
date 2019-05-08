#pragma once
#include "StringEx.h"
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>

struct Stream
{
    //name to identify this stream
    String NameOrFullPath;
    String FullDir2;

    //stream content and length
    String Text;
    int TextLen;

    wchar_t Character;
    int Position;
    int Line;
    int Column;
};



bool Stream_Init(struct Stream* pfStream,
    const char* name,
    const char* psz);

bool Stream_InitFile(struct Stream* pfStream,
    const char* fileName);

void Stream_Destroy(struct Stream* pfStream);

wchar_t Stream_LookAhead(struct Stream* pStream);

void Stream_Match(struct Stream* pStream);
bool Stream_MatchChar(struct Stream* pStream, wchar_t ch);

