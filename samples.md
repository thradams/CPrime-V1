##  Sample 1
Input
```c

#include <stdbool.h>

enum E
{
    A, B, C
};

struct X {
  int  i;
  char ch;
  enum E e;
  bool b;
  double d;
  float f;
  long l;
  struct Y { int i;  } y;
};

void X_Init(struct X* pX) _default
{
    pX->i = 0;
    pX->ch = 0;
    pX->e = 0;
    pX->b = false;
    pX->d = 0;
    pX->f = 0;
    pX->l = 0;
    pX->y.i = 0;
}

void X_Destroy(struct X* pX) _default
{
}

struct X* X_Create() _default
{
    struct X *p = (struct X *) malloc(sizeof * p);
    if (p)
    {
        X_Init(p);
    }
    return p;
}

void X_Delete(struct X* pX)  _default
{
    if (pX)
    {
        X_Destroy(pX);
        free(pX);
    }
}


int main(int argc, char **argv)
{
    struct X x = _default {0};
	return 0;
}

```

##  Sample 2

Input
```c

struct X {
  int  i;  
};

void X_Init(struct X* pX) _default;

```
Output
```c

struct X {
  int  i;  
};

void X_Init(struct X* pX) _default
{
   p->i = 0;
}

```
