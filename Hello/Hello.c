#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef enum E {A, B} E;
typedef int X;
typedef struct Y
{
    X x;
};
int main()
{
    E e;
    e = A;
}