
#include <stdlib.h>

typedef struct 
{
       int * _auto i;
} X;

void X_Destroy(X* p) _default
{
    free(p->i);
}

#if 0
struct Y
{
    X * _auto pAutoX;
    X x;
};

void Y_Destroy(struct Y* p) _default
{
    X_Destroy(p->pAutoX);
    free(p->pAutoX);
    X_Destroy(&p->x);
}
#endif

int main()
{


}