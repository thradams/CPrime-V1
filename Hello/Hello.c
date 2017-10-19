#include "config.h"
#define _size

struct X {
  int _size i;  
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
