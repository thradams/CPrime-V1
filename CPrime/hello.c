

#include <stdio.h>
#include <stdlib.h>

//struct Shape;

typedef struct
{
    int type = 1;
    void* pNext;
    int w;
    int h;
}  Box;

Box* Box_Create() default;
void Box_Destroy(Box* p) default;

void Box_Draw(Box* p)
{
    printf("box\n");
}
typedef struct
{
    int type = 2;
    void* pNext;
    int r;
}  Circle;

Circle* Circle_Create() default;
void Circle_Destroy(Circle* p) default;

void Circle_Draw(Circle* p) 
{
    printf("circle\n");
}

typedef struct Union(Box, Circle) Shape;

void Shape_Delete(Shape* p) default;
void Shape_Draw(Shape* p) default;

typedef struct Array(Shape* auto) Shapes;
void Shapes_Add(Shapes* p, Shape* pItem) default;
void Shapes_Destroy(Shapes* p) default;

typedef struct
{
  Shape * auto p;
} Z;

void Z_Destroy(Z* p) default;

int main()
{
    Shapes shapes = {};

    shape = (Shapes) {};

    Shapes_Add(&shapes, (Shape*) Box_Create());
    
    Shapes_Add(&shapes, (Shape*)Circle_Create());

    for (int i = 0; i < shapes.Size; i++)
    {
        Shape_Draw(shapes.pData[i]);

    }

    Shapes_Destroy(&shapes);
}