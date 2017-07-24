

#include <stdio.h>
#include <stdlib.h>

//struct Shape;

typedef struct
{
    int type /* =   1 */;
    void* pNext;
    int w;
    int h;
}  Box;

Box* Box_Create()  /*default*/
{

Box *p = (

Box*) malloc(sizeof * p);
if (p != NULL) {
p->type =   1;
p->pNext = NULL;
p->w = 0;
p->h = 0;
}
return p;

}
void Box_Destroy(Box* p)  /*default*/
{
}

void Box_Draw(Box* p)
{
    printf("box\n");
}
typedef struct
{
    int type /* =   2 */;
    void* pNext;
    int r;
}  Circle;

Circle* Circle_Create()  /*default*/
{

Circle *p = (

Circle*) malloc(sizeof * p);
if (p != NULL) {
p->type =   2;
p->pNext = NULL;
p->r = 0;
}
return p;

}
void Circle_Destroy(Circle* p)  /*default*/
{
}

void Circle_Draw(Circle* p) 
{
    printf("circle\n");
}

typedef struct  {int type;} Shape;

void Shape_Delete(Shape* p)  /*default*/
{if (p != NULL) {

    switch(p->type) {
    case 1:
        Box_Destroy((Box*) p);
    break;
    case 2:
        Circle_Destroy((Circle*) p);
    break;
    }
free(p);
}

}
void Shape_Draw(Shape* p)  /*default*/
{
    switch(p->type) {
    case 1:
        Box_Draw((Box*) p);
    break;
    case 2:
        Circle_Draw((Circle*) p);
    break;
    }

}

typedef struct  {Shape**pData; int Size, Capacity;}  Shapes;
void Shapes_Add(Shapes* p, Shape* pItem)  /*default*/
{ if (p->Size + 1 > p->Capacity)
 {
    int new_nelements = p->Capacity + p->Capacity / 2;
 
 if (new_nelements < 1)
 {
     new_nelements = 1;
 }
 void** pnew = (void**) p->pData;
 pnew = (void**)realloc(pnew, new_nelements * sizeof(void*));
 if (pnew)
 {
    p->pData = pnew;
    p->Capacity = new_nelements;
 }
 }
    p->pData[p->Size] = pItem;
    p->Size++;
 

}
void Shapes_Destroy(Shapes* p)  /*default*/
{for (int i =0 ; i < p->Size; i++)
{
  Shape *pCurrent = p->pData[i];
  Shape_Delete(pCurrent);
}

}

typedef struct
{
  Shape *auto  p;
} Z;

void Z_Destroy(Z* p)  /*default*/
{Shape_Delete(&p->p);

}

int main()
{
    Shapes shapes = {NULL, 0, 0};

    Shapes_Add(&shapes, (Shape*) Box_Create());
    
    Shapes_Add(&shapes, (Shape*)Circle_Create());

    for (int i = 0; i < shapes.Size; i++)
    {
        Shape_Draw(shapes.pData[i]);

    }

    Shapes_Destroy(&shapes);
}