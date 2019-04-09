#include "Array.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "StringEx.h"
#include "Mem.h"

bool Array_Reserve(Array* p, int nelements)
{
    bool result = true;
    if(nelements > p->capacity)
    {
        void** pnew = p->pItems;
        pnew = (void**)Realloc(pnew, nelements * sizeof(void*));
        if(pnew)
        {
            p->pItems = pnew;
            p->capacity = nelements;
        }
        else
        {
            result = false /*nomem*/;
        }
    }
    return result;
}


bool Array_Grow(Array* p, int nelements)
{
    bool result = true;
    if(nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;
        if(new_nelements < nelements)
        {
            new_nelements = nelements;
        }
        result = Array_Reserve(p, new_nelements);
    }
    return result;
}


void* Array_PopGet(Array* p)
{
	void* pItem = 0;
	if (p->size > 0)
	{
		pItem = p->pItems[p->size - 1];
		p->pItems[p->size - 1] = NULL;
		p->size--;		
	}
	else
	{
		//assert(false);
	}
	return pItem;
}

void Array_Pop(Array* p, void(*pfDestroyData)(void*))
{
	void* pItem = Array_PopGet(p);
    if(pfDestroyData)
    {
       pfDestroyData(pItem);
    }
}

void* Array_Top(Array* p)
{
    //assert(p->size > 0);
    return p->pItems[p->size - 1];
}

bool Array_Push(Array* p, void* pItem)
{
    bool result = Array_Grow(p, p->size + 1);
    if(result == true)
    {
        p->pItems[p->size] = pItem;
        p->size++;
    }
    return result;
}

void Array_Clear(Array* p, void(*pfDestroyData)(void*))
{
    for(int i = 0; i < p->size; i++)
    {
        if(pfDestroyData)
            pfDestroyData(p->pItems[i]);
    }
    Free(p->pItems);
    p->pItems = NULL;
    p->size = 0;
    p->capacity = 0;
}


void Array_Init(Array* p)
{
    p->capacity = 0;
    p->size = 0;
    p->pItems = NULL;    
}

void Array_Destroy(Array* st, void (*pfDestroyData)(void*))
{
    Array_Clear(st, pfDestroyData);
}

void Array_Swap(Array* p1, Array* p2)
{
    int c = p1->capacity;
    int s = p1->size;
    void** pp = p1->pItems;
    p1->capacity = p2->capacity;
    p1->size = p2->size;
    p1->pItems = p2->pItems;
    p2->capacity = c;
    p2->size = s;
    p2->pItems = pp;
}


bool StrArray_Reserve(struct StrArray* p, int nelements)
{
    return Array_Reserve((Array*)p, nelements);
}

bool StrArray_Push(struct StrArray* p, const char* pItem)
{
    String s;
    String_InitWith(&s, pItem);
    
    {
        bool result = Array_Push((Array*)p, s);
        if(result != true)
        {
            String_Destroy(&s);
        }
    }
    return true;
}

static void Array_DeleteStrVoid(void* p)
{
    String_Destroy((String*)(&p));
}

void StrArray_Clear(struct StrArray* p)
{
    Array_Clear((Array*)p, Array_DeleteStrVoid);
}

void StrArray_Init(struct StrArray* p)
{
    Array_Init((Array*)p);
}

void StrArray_Destroy(struct StrArray* p)
{
    Array_Destroy((Array*)p, &Array_DeleteStrVoid);
}

void StrArray_Swap(struct StrArray* p1, struct StrArray* p2)
{
    struct StrArray temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}



void* Array_PopFront(Array* p)
{
	void* pItem = NULL;
	//assert(p->size > 0);
	if (p->size > 0)
	{
		pItem = p->pItems[0];
		if (p->size > 1)
		{
			memmove(p->pItems, p->pItems + 1, sizeof(void*) * (p->size - 1));
		}
		p->size--;
	}
	return pItem;
}




