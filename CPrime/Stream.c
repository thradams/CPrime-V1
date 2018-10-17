
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
  FILE*  fp = (FILE* ) fopen(filename, "rb");

  if (fp)
  {
    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);
    char*  buffer = (char*)Malloc(lSize + 1);

    if (buffer)
    {
      /*int fr =*/ fread(buffer, 1, lSize , fp);

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


bool SStream_InitFile(struct SStream* pStream,
                        const char* fullPath)
{
  //assert(IsFullPath(fullPath));
  String_InitWith(&pStream->NameOrFullPath, fullPath);
  String_InitWith(&pStream->FullDir2, NULL);
  pStream->CurrentLine = 1;
  pStream->CurrentCol = 1;
  pStream->CurrentPos = 0;
  bool result = LoadFile(fullPath, (const char**)&pStream->Text,
                           &pStream->TextLen);

  if (result)
  {
    //O objetivo aqui eh pegar o diretorio
    GetFullDir(fullPath, &pStream->FullDir2);

    if (pStream->Text != NULL &&
        pStream->Text[0] != '\0')
    {
      //unicode?
      pStream->CurrentChar = pStream->Text[0];
    }

    else
    {
      pStream->CurrentChar = '\0';
    }
  }

  return result;
}

bool SStream_Init(struct SStream* pStream, const char* name, const char*  Text)
{
  pStream->CurrentLine = 1;
  pStream->CurrentCol = 1;
  pStream->CurrentPos = 0;
  String_InitWith(&pStream->Text, Text);
  String_InitWith(&pStream->NameOrFullPath, name);
  String_InitWith(&pStream->FullDir2, "");

  if (Text != NULL)
  {
    pStream->TextLen = strlen(Text);
  }

  else
  {
    pStream->TextLen = 0;
  }

  if (pStream->Text != NULL &&
      pStream->Text[0] != '\0')
  {
    //unicode?
    pStream->CurrentChar = pStream->Text[0];
  }

  else
  {
    pStream->CurrentChar = '\0';
  }

  return true;
}


void SStream_Destroy(struct SStream* pStream) /*default*/
{
    String_Destroy(&pStream->NameOrFullPath);
    String_Destroy(&pStream->FullDir2);
    String_Destroy(&pStream->Text);
}


wchar_t SStream_LookAhead(struct SStream* pStream)
{
  if (pStream->CurrentPos + 1 >= pStream->TextLen)
  {
    return '\0';
  }

  return pStream->Text[pStream->CurrentPos + 1];
}

bool SStream_MatchChar(struct SStream* pStream, wchar_t ch)
{
    bool b = pStream->CurrentChar == ch;
    SStream_Match(pStream);
    return b;
}

void SStream_Match(struct SStream* pStream)
{
  if (pStream->CurrentPos >= pStream->TextLen)
  {
    pStream->CurrentChar = L'\0';
    return;
  }

  pStream->CurrentCol++;
  pStream->CurrentPos++;

  if (pStream->CurrentPos == pStream->TextLen)
  {
    pStream->CurrentChar = '\0';
  }

  else
  {
    pStream->CurrentChar = pStream->Text[pStream->CurrentPos];
  }

  if (pStream->CurrentChar == '\n')
  {
    pStream->CurrentLine++;
    pStream->CurrentCol = 0;
  }
}

