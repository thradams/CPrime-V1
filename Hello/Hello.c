#include <stdio.h>
#include <stdlib.h>
//#include <Windows.h>

typedef char * _auto String;

struct Person
{
    String Name;
    int age /*= -1*/;
    _Bool b /*= true*/;
};

struct Person* Person_Create();
void Person_Delete(struct Person* person);
 
int main()
{
    struct Person person = _default {0};
    struct Person* pPerson = Person_Create();
    Person_Delete(pPerson);
    return 0;
}

struct Person* Person_Create() _default
{
    struct Person* p = (struct Person*)malloc(sizeof * p);
    if (p != NULL)
    {
        p->Name = NULL;
        p->age = 0;
        p->b = 0;
    }
    return p;
}
void Person_Destroy(struct Person* person) _default
{
    free(person->Name);
}

void Person_Delete(struct Person* person) _default
{
    if (person != NULL)
    {
        Person_Destroy(person);
        free(person);
    }
}