
struct X
{
    int * i ;
};

void X_Init(struct X* p)  /*@default*/   
{
    p->i = 0;
}