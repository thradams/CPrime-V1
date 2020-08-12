#include <stdio.h>

/*
 Este projeto é usado para fazer testes no cprime
 e ao mesmo tempo testar a compilacao normal.
*/

enum E
{
 A,
 B
};

struct X
{
    char* /*@auto*/ name2;
};

void X_Destroy(struct X* p) /*@default*/
{
    free((void*)p->name2);
}

#define X_INIT {0}
int main()
{
    struct X x = X_INIT;
}