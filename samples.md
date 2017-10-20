##  Sample 1
Input
```c

#include <stdbool.h>

enum E
{
    A, b, C
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

void X_Init(struct X* pX) _default;
```
Output
```c


#include <stdbool.h>

enum E
{
    A, b, C
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
