
struct StrArray
{
    const char* /*@auto*/ * /*@auto*/ /*@[Size]*/ data;
    int Size;
    int Capacity;
};

void StrArray_Destroy(struct StrArray* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        free((void*)p->data[i]);
    }
    free((void*)p->data);
}

void StrArray_PushBack(struct StrArray* p, const char* s) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        const char** pnew = p->data;
        pnew = (const char**)realloc(pnew, n * sizeof(const char*));
        if (pnew)
        {
            p->data = pnew;
            p->Capacity = n;
        }
    }
    p->data[p->Size] = s;
    p->Size++;
}