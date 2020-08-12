#include <stdio.h>

/*
 Este projeto é usado para fazer testes no cprime
 e ao mesmo tempo testar a compilacao normal.
*/

struct X
{
    char* /*@auto*/ name2;
};

void X_Destroy(struct X* p) /*@default*/
{
    free((void*)p->name2);
}

int main()
{
    int p;
}