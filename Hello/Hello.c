#define STRUCT 
//struct

typedef  char * _auto String;

//void String_Destroy(String* s) {}

struct X;

typedef struct X X;

void X_Destroy(STRUCT X* pX)  _default
{
    /// pX ///
    //pX->a = 0;
    //pX->b = 0;
    free(pX->Name);
    /// pX ///
}

void X_Delete(STRUCT X* pX)  _default
{
    if (pX){

        X_Destroy(pX);
        free(pX);
    }

}

struct Y
{
    STRUCT X x;
    STRUCT X * pX;
    STRUCT X * _auto pAutoX;
};
typedef struct Y Y;

//void Y_Destroy(STRUCT Y* pY) _default;
void Y_Delete(STRUCT Y* pY) _default
{
    /// pY ///
    if (pY)
    {
    X_Destroy(&pY->x);
    //pY->pX = NULL;
    X_Delete(pY->pAutoX);
        free(pY);
    }
    /// pY ///
}
int main()
{
}

struct X
{
    int a;
    char b;
    String  Name;
};