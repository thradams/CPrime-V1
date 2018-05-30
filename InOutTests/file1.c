
typedef char * /*@auto*/ String;
struct X
{
	String Name;
	int i;
};

struct X* X_Create() /*@default*/
{
    struct X *p = (struct X *) malloc(sizeof * p);
    if (p)
    {
        X_Init(p);
    }
    return p;
}
void X_Init(struct X* p) /*@default*/
{
    p->Name = 0;
    p->i = 0;
}
void X_Destroy(struct X* p) /*@default*/
{
    free((void*)p->Name);
}
void X_Delete(struct X* p) /*@default*/
{
    if (p)
    {
        X_Destroy(p);
        free((void*)p);
    }
}

int main()
{
	struct X x =/*@default*/ {0};
	return 1;
}
