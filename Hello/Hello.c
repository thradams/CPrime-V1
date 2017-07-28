#include <stdlib.h>

/*
   1 - More details about Create/Delete/Init - ok
   2 - New design - ok
   3 - auto pointer - ok
*/
//thanks

typedef char * String;
void String_Destroy(String * s) { free(*s);  }

typedef struct
{
    String Name;
    int Age _defval(  3);
    
} Person;

//void Person_Destroy(Person* pPerson);
Person* Person_Create();
void Person_Delete(Person* pPerson);


typedef struct  Array(Person*_auto) {Person**pData; int Size, Capacity;}  MyArray;

MyArray* MyArray_Create();
void MyArray_Delete(MyArray* pMyArray);
void MyArray_Destroy(MyArray* pMyArray);
void MyArray_Add(MyArray* pMyArray, Person* pItem);

int main()
{
    //on concept is build on the top of other.
    MyArray* myArray = MyArray_Create();
    MyArray_Add(myArray, Person_Create());
    
    //auto complete works everthing looks like C
    for (int i = 0; i < myArray->Size; i++)
    {
        
    }
    MyArray_Delete(myArray);
}


MyArray* MyArray_Create() _default
{
    MyArray *p = (MyArray*) malloc(sizeof * p);
    if (p != NULL) {
    p->pData = NULL;
    p->Size = 0;
    p->Capacity = 0;
    }
    return p;

}
void MyArray_Delete(MyArray* pMyArray) _default
{
    if (pMyArray != NULL) {
        MyArray_Destroy(pMyArray);
        free(pMyArray);
    }

}

void MyArray_Destroy(MyArray* pMyArray) _default
{
    for (int i = 0 ; i < pMyArray->Size; i++)
    {
        Person_Delete(pMyArray->pData[i]);
    }
    free(pMyArray->pData);
}
void MyArray_Add(MyArray* pMyArray, Person* pItem) _default
{
    if (pMyArray->Size + 1 > pMyArray->Capacity)
     {
        int new_nelements = pMyArray->Capacity + pMyArray->Capacity / 2;

        if (new_nelements < 1)
        {
            new_nelements = 1;
        }
        void** pnew = (void**) pMyArray->pData;
        pnew = (void**)realloc(pnew, new_nelements * sizeof(void*));
        if (pnew)
        {
            pMyArray->pData = (Person**)pnew;
            pMyArray->Capacity = new_nelements;
        }
    }
    pMyArray->pData[pMyArray->Size] = pItem;
    pMyArray->Size++;
}


//the concept of create is build on the top of init
//if init is not found then its is "inline"

void Person_Init(Person* pPerson) _default
{
    pPerson->Name = NULL;
    pPerson->Age =   3;
}

Person* Person_Create() _default
{
    Person *p = (Person*) malloc(sizeof * p);
    if (p != NULL) {
        Person_Init(p);
    }
    return p;
}

//delete is built on the top of "destroy"

void Person_Delete(Person* pPerson) _default
{
    if (pPerson != NULL) {
        String_Destroy(&pPerson->Name);
        free(pPerson);
    }
}