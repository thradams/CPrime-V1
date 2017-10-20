
```c
                                                    |
struct X {                                          |  struct X {
  int  i;                                           |     int  i;  
};                                                  |  };
                                                    |
void X_Init(struct X* pX) _default;                 |  void X_Init(struct X* pX) _default
                                                    |  {
                                                    |      pX->i = 0;
                                                    |  }
```


```c

struct X {
  int  i;  
};

void X_Init(struct X* pX) _default;

```

```c

struct X {
  int  i;  
};

void X_Init(struct X* pX) _default
{
   p->i = 0;
}

```
