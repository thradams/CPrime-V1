#include "amalgamation.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Path.h"
#include "Mem.h"
#include <string.h>

 char *strdup(const char *s) {
  char *d = malloc(strlen(s) + 1);
  if (d != NULL) strcpy(d, s);
  return d;
}

struct Header
{
  char * fileName;
  struct Header* pNext;
};

struct Header* s_included = 0;


void MarkAsIncluded(const char* filename)
{
  
  struct Header* pNew = Malloc(sizeof * pNew);
  pNew->fileName = strdup(filename);
  pNew->pNext = 0;

  if (s_included == NULL)
  {
    s_included = pNew;
  }
  else
  {
    pNew->pNext = s_included;
    s_included = pNew;
  }
}

int strcicmp(wchar_t const *a, wchar_t const *b)
{
  for (;; a++, b++) {
    int d = tolower(*a) - tolower(*b);
    if (d != 0 || !*a)
      return d;
  }
  return 0;
}


bool IsAlreadyIncluded(const char* filename)
{
  bool result = false;
  struct Header* pCurrent = s_included;
  while (pCurrent)
  {
    if (strcmp(pCurrent->fileName, filename) == 0)
    {
      result = true;
      break;
    }
    pCurrent = pCurrent->pNext;
  }
  return result;
}

void FreeList()
{
  struct Header* pCurrent = s_included;
  while (pCurrent)
  {
    struct Header* pNext = pCurrent->pNext;
    Free(pCurrent->fileName);
    Free(pCurrent);
    pCurrent = pNext;
  }

}


WriteResult Write(char* fileNameRelative, bool bIsSystemHeader, FILE* out)
{

  WriteResult result = NOT_FOUND;
  String fullPath = STRING_INIT;

  if (bIsSystemHeader)
  {
    //Normaliza o nome do arquivo
    GetFullPath(fileNameRelative, &fullPath);
  }
  else
  {
    String_Set(&fullPath, fileNameRelative);
  }
  

  String fullDir = STRING_INIT;
  GetFullDir(fileNameRelative, &fullDir);

  if (IsAlreadyIncluded(fullPath))
  {    
    return ALREADY_INCLUDED;
  }

  
  MarkAsIncluded(fullPath);

  char previous = '\0';

  FILE * input = fopen(fullPath, "r");

  if (input)
  {   
    //para debug
    //fprintf(out, "#line 0 \"%s\" \n", fullPath);
    result = INCLUDED;
    char c = '\0';

    while (!feof(input))
    {
      previous = c;
      c = fgetc(input);
      if ((previous == '\0' || previous == '\n') && c == '#')
      {
        c = fgetc(input);
        char linebuffer[500];
        int i = 0;
        linebuffer[i] = '#';
        i++;
        while (c != '\n' && c != EOF)
        {
          linebuffer[i] = c;
          c = fgetc(input);
          i++;
        }
        linebuffer[i] = '\0';
        const char * pChar = linebuffer;

        pChar++; //skip #

        while (*pChar == ' ') //skip spaces
          pChar++;

        if (strncmp(pChar, "pragma", sizeof("pragma") - 1) == 0)
        {
          pChar += sizeof("pragma") - 1; //skip pragma

          while (*pChar == ' ') //skip spaces
            pChar++;

          if (strncmp(pChar, "once", sizeof("once") - 1) == 0)
          {
            //nothing
          }
          else
          {
            fputs(linebuffer, out);
            fputs("\n", out);
          }
        }
        else if (strncmp(pChar, "include", sizeof("include") - 1) == 0)
        {
          pChar += sizeof("include") - 1; //match include

          while (*pChar == ' ') //skip spaces          
            pChar++;

          bool bIsSystemHeader = (*pChar == '<');
          if (*pChar == '"' || *pChar == '<')
          {
            pChar++;//match " or <

            char fileName[200] = { 0 };

            if (!bIsSystemHeader)
            {              
              //faz o nome ser relativo a este arquivo
              strcat(fileName, fullDir);
            }

            char fileName0[200] = { 0 };

            int k = 0;
            while (*pChar)
            {
              if (*pChar == '\"' || *pChar == '>')
              {
                break;
              }
              fileName0[k] = *pChar;
              pChar++;
              k++;
            }

            strcat(fileName, fileName0);

            WriteResult wr = Write(fileName, bIsSystemHeader, out);
            if (wr == NOT_FOUND)
            {
                //arquivo externo
                fputs(linebuffer, out);
                fputs("\n", out);
            }
            else if (wr == ALREADY_INCLUDED)
            {
              //fputs("//ja incluido ", out);
              //fputs(linebuffer, out);
              //fputs("\n", out);
            }
            
          }
          else
          {
            fputs(linebuffer, out);
            fputs("\n", out);
          }
        }
        else
        {
          fputs(linebuffer, out);
          fputs("\n", out);
        }
      }
      else
      {
        if (c != EOF)
        {
          fputc(c, out);
        }
      }
    }
    fclose(input);
    //para debug
    //fprintf(out, "//%s }\n", fullPath);
  }

  String_Destroy(&fullPath);
  String_Destroy(&fullDir);
  fullPath = 0;

  return result;
}

/*

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("usage merge.txt out.c");
    return 1;
  }

  FILE * out = fopen(argv[2], "w");
  if (out)
  {
    Write(argv[1], out);
    fclose(out);
  }

  FreeList();
  return 0;
}
*/
