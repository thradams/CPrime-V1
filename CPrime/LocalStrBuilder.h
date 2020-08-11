#pragma once
#pragma source

#include <stdlib.h>



# //BEGIN_EXPORT

#define LOCALSTRBUILDER_NCHARS 7

struct LocalStrBuilder
{
    char* c_str;
    int size;
    int capacity;
    char chars[LOCALSTRBUILDER_NCHARS + 1];

};


void LocalStrBuilder_Init(struct LocalStrBuilder* p);

void LocalStrBuilder_Swap(struct LocalStrBuilder* pA, struct LocalStrBuilder* pB);

void LocalStrBuilder_Destroy(struct LocalStrBuilder* p);

void LocalStrBuilder_Reserve(struct LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Print(struct LocalStrBuilder* p);

void LocalStrBuilder_Clear(struct LocalStrBuilder* p);

void LocalStrBuilder_Grow(struct LocalStrBuilder* p, int nelements);

void LocalStrBuilder_Append(struct LocalStrBuilder* p, const char* source);
void LocalStrBuilder_AppendChar(struct LocalStrBuilder* p, char ch);
void LocalStrBuilder_Set(struct LocalStrBuilder* p, const char* source);

// #END_EXPORT

