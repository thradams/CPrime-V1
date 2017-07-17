#include <stdio.h>
#include <stdlib.h>

struct Shape;


typedef struct
{
     int type /* =   1 */;
     int w;
     int h;
     struct Shape* pNext;
} Box;

void Box_Draw(Box* pBox)
{
    printf("box w = %d, h = %d\n", pBox->w, pBox->h);
}

Box* Box_Create()  /*default*/
{
    Box* p = (Box*) malloc(sizeof * p);
   if (p)
   {
      Box temp = {  1,0,0,NULL};
      *p = temp;
   }
   return p; 

}
void Box_Delete(Box* p)  /*default*/
{
   if (p)
   {
            free(p);
   }

}

typedef struct
{
    int type /* =   2 */;
    int r;
    struct Shape* pNext;
} Circle;

void Circle_Draw(Circle* pCircle)
{
    printf("circle r = %d\n", pCircle->r);
}

Circle* Circle_Create()  /*default*/
{
    Circle* p = (Circle*) malloc(sizeof * p);
   if (p)
   {
      Circle temp = {  2,0,NULL};
      *p = temp;
   }
   return p; 

}
void Circle_Delete(Circle*p)  /*default*/
{
   if (p)
   {
            free(p);
   }

}


typedef struct
{
    int type /* =   3 */;
    int w;
    int h;
    struct Shape* pNext;
} Triangle;

void Triangle_Draw(Triangle* pTriangle)
{
    printf("Triangle w = %d, h = %d\n", pTriangle->w, pTriangle->h);
}

Triangle* Triangle_Create()  /*default*/
{
    Triangle* p = (Triangle*) malloc(sizeof * p);
   if (p)
   {
      Triangle temp = {  3,0,0,NULL};
      *p = temp;
   }
   return p; 

}
void Triangle_Destroy(Triangle* p)  /*default*/
{





}
void Triangle_Delete(Triangle* p)  /*default*/
{
   if (p)
   {
      Triangle_Destroy(p);
      free(p);
   }

}


typedef struct Shape{ int type; } Shape;

void Shape_Draw(Shape* p)  /*default*/
{
}
void Shape_Delete(Shape* p)  /*default*/
{
   if (p)
   {
            free(p);
   }

}


int main()
{
    Box* pBox = Box_Create();
    pBox->w = 1;
    pBox->h = 2;

    Shape *pShape = (Shape*) pBox;

    Shape_Draw(pShape);

    Shape_Delete(pShape);
    return  1;
}