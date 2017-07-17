#include <stdio.h>
#include <stdlib.h>

struct Shape;


typedef struct
{
     int type = 1;
     int w;
     int h;
 
} Box;

void Box_Draw(Box* pBox)
{
    printf("box w = %d, h = %d\n", pBox->w, pBox->h);
}

Box* Box_Create() default;
void Box_Delete(Box* p) default;

typedef struct
{
    int type = 2;
    int r;
   
} Circle;

void Circle_Draw(Circle* pCircle)
{
    printf("circle r = %d\n", pCircle->r);
}

Circle* Circle_Create() default;
void Circle_Delete(Circle*p) default;


typedef struct
{
    int type = 3;
    int w;
    int h;
  
} Triangle;

void Triangle_Draw(Triangle* pTriangle)
{
    printf("Triangle w = %d, h = %d\n", pTriangle->w, pTriangle->h);
}

Triangle* Triangle_Create() default;
void Triangle_Destroy(Triangle* p) default;
void Triangle_Delete(Triangle* p) default;


typedef struct Shape Union(Box, Circle, Triangle) Shape;

void Shape_Draw(Shape* p) default;
void Shape_Delete(Shape* p) default;


int main()
{
    Box* pBox = Box_Create();
    pBox->w = 1;
    pBox->h = 2;

    Shape *pShape = (Shape*) pBox;

    Shape_Draw(pShape);

    Shape_Delete(pShape);
    return 1;
}
