#pragma once
#include "Array.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum
{
  NOT_FOUND,
  ALREADY_INCLUDED,
  INCLUDED
} WriteResult;

WriteResult Write(char* name, bool bIsSystemHeader, FILE* out);

void FreeList();