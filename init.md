Init samples

```c

enum E
{
  A, B
};

struct Y
{
  int i;
};
struct X
{ 
   int i;
   int *p;
   struct X *pNext;
   struct Y y;
};

void X_Init(struct X* pX) _default
{
   pX->i = 0;
   pX->p = NULL;
   pX->pNext = NULL;
   pX->y.i = 0;
}

typedef struct X Y;

void Y_Init(Y* pX) _default
{
   pX->i = 0;
   pX->p = NULL;
   pX->pNext = NULL;
}


```


