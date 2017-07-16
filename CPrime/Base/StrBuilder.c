

#include "StrBuilder.h"
#include <string.h>
#include <stdlib.h>

#include <stdlib.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#ifdef USE_UTF8
#include  "Utf8.h"
#endif
#include "StringEx.h"



Result StrBuilder_Init(StrBuilder* p, size_t capacity)
{
  Result result = RESULT_OK;
  p->c_str = NULL;
  p->size = 0;
  p->capacity = 0;

  if (capacity > 0)
  {
    result = StrBuilder_Reserve(p, capacity);
  }

  return result;
}

void StrBuilder_Swap(StrBuilder* str1,
                     StrBuilder* str2)
{
  StrBuilder temp_Moved = *str1;
  *str1 = *str2;
  *str2 =  temp_Moved;
}

void StrBuilder_Destroy(StrBuilder* p)
{
  if (p)
  {
    free(p->c_str);
    p->c_str = NULL;
    p->size = 0;
    p->capacity = 0;
  }
}

Result StrBuilder_Reserve(StrBuilder* p, size_t nelements)
{
  Result r = RESULT_OK;

  if (nelements > p->capacity)
  {
    char* pnew = (char*)realloc(p->c_str,
                                (nelements + 1) * sizeof(p->c_str[0]));

    if (pnew)
    {
      if (p->c_str == NULL)
      {
        pnew[0] = '\0';
      }

      p->c_str = pnew;
      p->capacity = nelements;
    }

    else
    {
      r = RESULT_OUT_OF_MEM;
    }
  }

  return r;
}

static Result StrBuilder_Grow(StrBuilder* p, size_t nelements)
{
  Result r = RESULT_OK;

  if (nelements > p->capacity)
  {
    size_t new_nelements = p->capacity + p->capacity / 2;

    if (new_nelements < nelements)
    {
      new_nelements = nelements;
    }

    r = StrBuilder_Reserve(p, new_nelements);
  }

  return r;
}

Result StrBuilder_SetN(StrBuilder* p,
                       const char* source,
                       size_t nelements)
{
  Result r = StrBuilder_Grow(p, nelements);

  if (r == 0)
  {
    strncpy_s(p->c_str, p->capacity + 1, source, nelements);
    p->c_str[nelements] = '\0';
    p->size = nelements;
  }

  return r;
}

Result StrBuilder_Set(StrBuilder* p,
                      const char* source)
{
  StrBuilder_Clear(p);
  return StrBuilder_SetN(p, source, strlen(source));
}

Result StrBuilder_AppendN(StrBuilder* p,
                          const char* source,
                          size_t nelements)
{
  if (IsEmptyStr(source))
  {
    return RESULT_OK;
  }

  Result r = StrBuilder_Grow(p, p->size + nelements);

  if (r == RESULT_OK)
  {
    strncpy_s(p->c_str + p->size,
              (p->capacity + 1) - p->size,
              source,
              nelements);
    p->c_str[p->size + nelements] = '\0';
    p->size += nelements;
  }

  return r;
}

Result StrBuilder_Append(StrBuilder* p,
                         const char* source)
{
  if (IsEmptyStr(source))
  {
    return RESULT_OK;
  }

  return StrBuilder_AppendN(p, source, strlen(source));
}

void StrBuilder_Clear(StrBuilder* p)
{
  if (p->c_str != NULL)
  {
    p->c_str[0] = '\0';
    p->size = 0;
  }
}

char* StrBuilder_Release(StrBuilder* p)
{
  char* pResult = p->c_str;

  if (pResult != NULL)
  {
    p->c_str = NULL;
    p->size = 0;
    p->capacity = 0;
  }

  return pResult;
}

Result StrBuilder_AppendInt(StrBuilder* p, int i)
{
  Result r = RESULT_FAIL;
  char buffer[20];
#ifdef ITOA
  itoa(i, buffer, 10);
#else
  _itoa_s(i, buffer, sizeof(buffer), 10);
#endif
  r = StrBuilder_Append(p, buffer);
  return r;
}

void StrBuilder_Attach(StrBuilder* pStrBuilder,
                       char*  psz,
                       size_t nBytes)
{
  if (psz != NULL)
  {
    ASSERT(nBytes > 0);
    StrBuilder_Destroy(pStrBuilder);
    pStrBuilder->c_str = psz;
    pStrBuilder->capacity = nBytes - 1;
    pStrBuilder->size = 0;
    pStrBuilder->c_str[0] = '\0';
  }
}

Result StrBuilder_AppendWChar(StrBuilder* p, wchar_t wch)
{
#ifdef USE_UTF8
  char buffer[5] = { 0 };
  int nbytes = EncodeCharToUTF8Bytes(wch, buffer);
  return StrBuilder_AppendN(p, buffer, nbytes);
#else
  char ch = (char)wch;
  return StrBuilder_AppendN(p, &ch, 1);
#endif
}


Result StrBuilder_AppendChar(StrBuilder* p, char ch)
{
  return StrBuilder_AppendN(p, &ch, 1);
}

Result StrBuilder_AppendW(StrBuilder* p, const wchar_t* psz)
{
  Result result = RESULT_FAIL;

  while (*psz)
  {
    result = StrBuilder_AppendWChar(p, *psz);

    if (result != RESULT_OK)
    {
      break;
    }

    psz++;
  }

  return result;
}


void StrBuilder_Trim(StrBuilder* p)
{
  StrBuilder temp;
  StrBuilder_Init(&temp, p->size);
  bool bCopy = false;

  for (size_t i = 0; i < p->size; i++)
  {
    char ch = p->c_str[i];

    if (!bCopy && ch != ' ')
    {
      //a partir de agora copia
      bCopy = true;
    }

    if (bCopy)
      StrBuilder_AppendChar(&temp, ch);
  }

  //indice do ultimo que nao eh espaco
  int k = ((int)(temp.size)) - 1;

  for (; k >= 0; k--)
  {
    char ch = temp.c_str[k];

    if (ch != ' ')
    {
      break;
    }
  }

  temp.c_str[k + 1] = '\0';
  temp.size = k + 1;
  StrBuilder_Swap(&temp, p);
  StrBuilder_Destroy(&temp);
}



Result StrBuilder_AppendUpper(StrBuilder *p, const char*  s)
{
  if (s != NULL)
  {
    while (*s)
    {
      StrBuilder_AppendChar(p, toupper(*s));
      s++;
    }
  }

  return RESULT_OK;
}
