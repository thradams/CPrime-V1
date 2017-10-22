#include "config.h"
#include <stdlib.h>
#include <stdio.h>

enum
{
    Other_ID,
    Circle_ID,
    Car_ID,
    Triangle_ID,
    Box_ID,
};


typedef struct Box {
    int i;
} Box;

typedef struct Circle {
    int i;
} Circle;

typedef struct Car {
    int i;
} Car;


typedef struct {
    int i;
} Triangle;

void Car_Draw(struct Car* p)
{
}

void Box_Draw(struct Box* p) 
{
}
void Circle_Draw(struct Circle* p)
{
}
void Triangle_Draw(Triangle* p)
{
}


Triangle* Triangle_Create() //_default
{
    Triangle *p = (Triangle*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->i = Triangle_ID;
    }
    return p;
}

typedef struct _union("Car | Circle") Other Other;


 typedef struct _union("Box Circle Triangle Other") Shape Shape;

void Shape_Draw(struct Shape* p) _default
{
    switch (*((int*)p))
    {
        case Circle_ID: Circle_Draw((Circle*)p); break; 
        case Car_ID: Car_Draw((Car*)p); break; 
        case Triangle_ID: Triangle_Draw((Triangle*)p); break; 
        case Box_ID: Box_Draw((Box*)p); break; 
    }
}


struct Boxes
{
    Box* _auto _size(Size) pData;
    int Size;
    int Capacity;
};

struct Boxes
{
    Box Data _size(Size);
    Box Data[2];
    int Size;
    int Capacity;
};

struct Boxes
{
    Box* _auto _size(Size) pData;
    int Size;
    int Capacity;
};

void Boxes_Reserve(struct Boxes* p, int n) _default
{
    if (n > p->Capacity)
    {
        Box* pnew = p->pData;
        pnew = (Box*)realloc(pnew, n * sizeof(Box));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}
void Boxes_Destroy(struct Boxes* p) _default
{
    if (p->pData != NULL)
    {
        free((void*)p->pData);
    }
}

int main(int argc, char **argv)
{
    Shape* p = (struct Shape*)Triangle_Create();
    Shape_Draw(p);
    return 0;
}
