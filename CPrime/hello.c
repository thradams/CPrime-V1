typedef struct
{
    int type = 1;
    int w;
    int h;
} Box;

void Box_Init(Box* pBox) default;

Box* Box_Create() default;
void Box_Delete(Box* p) default;

typedef struct List(Box*) Boxes;

void Boxes_Add(Boxes* p, Box* pItem) default;
//void Boxes_Init(Boxes* p) default;
//void Boxes_Destroy(Boxes* p) default;

typedef struct
{
    Boxes boxes;
} Z;
void Z_Init(Z* p) default;
void Z_Destroy(Z* p) default;


