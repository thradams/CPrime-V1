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
    struct Person person = _default {/*.Name=*/0/*NULL*/, /*.age=*/0, /*.b=*/0};
    struct Person* pPerson = Person_Create();
    Person_Delete(pPerson);
    return 0;
}

struct Person* Person_Create() _default
{
    struct Person *p = malloc(sizeof * p);
    if (p)
    {
        p->Name = 0/*NULL*/;
        p->age = 0;
        p->b = 0;
    }
    return p;
    

}
void Person_Delete(struct Person* person) _default
{
    if (person)
    {
        free(person->Name);
        //person->age = 0;
        //person->b = 0;
        free(person);
    }
    

}