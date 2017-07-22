

typedef char * auto String;


typedef struct List(String) Z;

void Z_Init(Z* pZ) default;
//void Z_Destroy(Z* pZ) default;

typedef struct {
    Z z;
} X;



