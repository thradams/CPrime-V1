#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct X {
  int i;  
};

void X_Init(struct X* pX) _default
{
    pX->i = 0;

}

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}
