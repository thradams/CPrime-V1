#include "config.h"
#include <stdio.h>
struct Box
{
	int id;
};

struct Circle
{
	int id;
};

struct _union(Box | Circle) Shape
;

void Shape_Destroy(struct Shape* p) _default;

int main()
{
}