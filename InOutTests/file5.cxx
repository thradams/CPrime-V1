
struct Box
{
	int id = 1;
};

Box* Box_Create() default;
void Box_Delete(Box* pBox) default;

void Box_Draw(Box* pBox)
{
	printf("Box\n");
}

struct Circle
{
	int id = 2;
};
Circle* Circle_Create() default;
void Circle_Delete(Circle* pCircle) default;

void Circle_Draw(Circle* pCircle)
{
	printf("Circle\n");
}

struct _union(Box | Circle) Shape
{
	int id;
};

void Shape_Delete(Shape* pShape) default;
void Shape_Draw(Shape* pShape) default;

