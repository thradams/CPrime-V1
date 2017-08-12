#pragma once

//These macros allow to compile using C

#ifndef CPRIME

#define Array(T) { T *pData; int Size, Capacity;}
#define List(T) { T pHead; T pTail; }
#define Map(T) {  MapItem2** pHashTable; unsigned int HashTableSize; int Count; }

#define Union(...) { int type; }

#define _defval(x)
#define _default
#define _auto

#else

#endif

