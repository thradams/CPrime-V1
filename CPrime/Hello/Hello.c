struct X
{
    int x;
};

void X_Init(struct X * p) : init /*@default*/
{
    p->x = 0;
}

struct Y
{
    struct X x;
};

void Y_Init(struct Y * p) /*@default*/
{
    X_Init(&p->x);
}
