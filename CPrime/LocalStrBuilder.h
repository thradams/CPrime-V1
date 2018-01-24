#pragma once

#include <stdlib.h>

#define LOCALSTRBUILDER_NCHARS 7

typedef struct
{
  char* c_str;
  int size;
  int capacity;
  char chars[LOCALSTRBUILDER_NCHARS + 1];

} LocalStrBuilder;


void LocalStrBuilder_Init(LocalStrBuilder* p);

void LocalStrBuilder_Swap(LocalStrBuilder* pA, LocalStrBuilder* pB);

void LocalStrBuilder_Destroy(LocalStrBuilder* p);

void LocalStrBuilder_Reserve(LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Print(LocalStrBuilder* p);

void LocalStrBuilder_Clear(LocalStrBuilder* p);

void LocalStrBuilder_Grow(LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Append(LocalStrBuilder* p, const char* source);
void LocalStrBuilder_AppendChar(LocalStrBuilder* p, char ch);
void LocalStrBuilder_Set(LocalStrBuilder* p, const char* source);

