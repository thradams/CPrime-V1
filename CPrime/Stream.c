
#include "Stream.h"
#include "StringEx.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "StrBuilder.h"

#include <ctype.h>
#include "Path.h"
#include "Mem.h"

bool LoadFile(const char* filename, const char** out, int* szOut)
{
    bool result = false;
    int lSize = 0;
    FILE* fp = (FILE*)fopen(filename, "rb");

    if (fp)
    {
        fseek(fp, 0L, SEEK_END);
        lSize = ftell(fp);
        rewind(fp);
        char* buffer = (char*)Malloc(lSize + 1);

        if (buffer)
        {
            /*int fr =*/ fread(buffer, 1, lSize, fp);

            if (feof(fp))
            {
                //ok leu tudo
            }

            if (!ferror(fp))
            {
                //ok
                buffer[lSize] = '\0';
                *out = buffer;
                buffer = NULL;
                result = true;
                *szOut = lSize;
            }

            Free(buffer);
        }

        fclose(fp);
    }

    return result;
}


bool Stream_InitFile(struct Stream* pStream,
                     const char* fullPath)
{
    //assert(IsFullPath(fullPath));
    pStream->NameOrFullPath = StrDup(fullPath);
    pStream->FullDir2 = NULL;
    pStream->Line = 1;
    pStream->Column = 1;
    pStream->Position = 0;
    bool result = LoadFile(fullPath, (const char**)& pStream->Text,
                           &pStream->TextLen);

    if (result)
    {
        //O objetivo aqui eh pegar o diretorio
        GetFullDir(fullPath, &pStream->FullDir2);

        if (pStream->Text != NULL &&
            pStream->Text[0] != '\0')
        {
            //unicode?
            pStream->Character = pStream->Text[0];
        }

        else
        {
            pStream->Character = '\0';
        }
    }

    return result;
}

bool Stream_Init(struct Stream* pStream, const char* name, const char* Text)
{
    pStream->Line = 1;
    pStream->Column = 1;
    pStream->Position = 0;
    pStream->Text = StrDup(Text);
    pStream->NameOrFullPath = StrDup(name);
    pStream->FullDir2 = StrDup("");

    if (Text != NULL)
    {
        pStream->TextLen = (int)strlen(Text);
    }

    else
    {
        pStream->TextLen = 0;
    }

    if (pStream->Text != NULL &&
        pStream->Text[0] != '\0')
    {
        //unicode?
        pStream->Character = pStream->Text[0];
    }

    else
    {
        pStream->Character = '\0';
    }

    return true;
}


void Stream_Destroy(struct Stream* pStream) /*@default*/
{
    Free((void*)pStream->NameOrFullPath);
    Free((void*)pStream->FullDir2);
    Free((void*)pStream->Text);
}


wchar_t Stream_LookAhead(struct Stream* pStream)
{
    if (pStream->Position + 1 >= pStream->TextLen)
    {
        return '\0';
    }

    return pStream->Text[pStream->Position + 1];
}

bool Stream_MatchChar(struct Stream* pStream, wchar_t ch)
{
    bool b = pStream->Character == ch;
    Stream_Match(pStream);
    return b;
}

void Stream_Match(struct Stream* pStream)
{
    if (pStream->Position >= pStream->TextLen)
    {
        pStream->Character = L'\0';
        return;
    }

    pStream->Column++;
    pStream->Position++;

    if (pStream->Position == pStream->TextLen)
    {
        pStream->Character = '\0';
    }

    else
    {
        pStream->Character = pStream->Text[pStream->Position];
    }

    if (pStream->Character == '\n')
    {
        pStream->Line++;
        pStream->Column = 0;
    }
}

