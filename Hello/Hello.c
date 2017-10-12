#include "config.h"
//#/include <stdio.h>

//#include <stdbool.h>
//#include <stdlib.h>
//#//include <string.h>
//#//include <time.h>


#if (! _Noreturn )

#endif


#if (! _Noreturn  && ( 0 ? __STDC_VERSION__ : 0) < 201112  && !0)

#endif

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
