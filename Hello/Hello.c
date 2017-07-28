#include <stdlib.h>
#include "Line.h"


int main()
{
    Lines lines;
    Lines_Init(&lines);
    Lines_Add(&lines, Line_Create());
    Lines_Destroy(&lines);
}