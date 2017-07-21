

typedef char *auto  String;

void String_Destroy(String* p);
//void String_Init(String* p);

typedef struct
{
    int i;
    String Name;
     //String stringVar;
     String *auto  pAutoString;
     int *auto  pAutoInt;
} Z;

void Z_Destroy(Z* p);
//void Z_Init(Z* p);

typedef struct
{
    Z zVar;
    Z*auto  pAutoZ;
    Z* pZ;

} X;