#include "config.h"
#include <stdio.h>
#include <stdlib.h>

enum {
  Other_ID,
  Circle_ID,
  Car_ID,
  Triangle_ID,
  Box_ID,
};

typedef struct Box {
  int i;
} Box;

struct Circle {
  int i;
};

struct Car {
  int i;
};

typedef struct {
  int i;
} Triangle;

void Car_Draw(struct Car *p) {}
void Car_Delete(struct Car *p) _default {
    if (p != NULL)
    {
        free((void*)p);
    }
}

void Box_Draw(struct Box *p) {}
void Box_Delete(struct Box *p) _default {
    if (p != NULL)
    {
        free((void*)p);
    }
}
void Circle_Draw(struct Circle *p) {}
void Circle_Delete(struct Circle *p) _default {
    if (p != NULL)
    {
        free((void*)p);
    }
}
void Triangle_Draw(Triangle *p) {}
void Triangle_Delete(Triangle *p) _default {
    if (p != NULL)
    {
        free((void*)p);
    }
}

Triangle *Triangle_Create() //_default
{
  Triangle *p = (Triangle *)malloc(sizeof *p);
  if (p != NULL) {
    p->i = Triangle_ID;
  }
  return p;
}

struct _union("Car | Circle") Other;

typedef struct  Other Other;

typedef struct _union("Box Circle Triangle Other") Shape Shape;

void Shape_Delete(struct Shape *p) _default {
    switch (*((int*)p))
    {
        case Other_ID: Other_Delete((Other*)p); break; 
        case Circle_ID: Circle_Delete((struct Circle*)p); break; 
        case Triangle_ID: Triangle_Delete((Triangle*)p); break; 
        case Box_ID: Box_Delete((Box*)p); break; 
    }
}

void Shape_Draw(struct Shape *p) _default {
    switch (*((int*)p))
    {
        case Other_ID: Other_Draw((Other*)p); break; 
        case Circle_ID: Circle_Draw((struct Circle*)p); break; 
        case Triangle_ID: Triangle_Draw((Triangle*)p); break; 
        case Box_ID: Box_Draw((Box*)p); break; 
    }
}

int main(int argc, char **argv) {
  Shape *p = (struct Shape *)Triangle_Create();
  Shape_Draw(p);
  Shape_Delete(p);
  return 0;
}
