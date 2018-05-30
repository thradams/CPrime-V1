
struct Box
{
	int id /*@ = 1@*/;
};

struct Box* Box_Create() /*@default*/
{
    struct Box* p = (struct Box*) malloc(sizeof * p);
    if (p)
    {
        p->id =  1;
    }
    return p;
}
void Box_Delete(struct Box* pBox) /*@default*/
{
    if (pBox)
    {
        free((void*)pBox);
    }
}

void Box_Draw(struct Box* pBox)
{
	printf("Box\n");
}

struct Circle
{
	int id /*@ = 2@*/;
};
struct Circle* Circle_Create() /*@default*/
{
    struct Circle* p = (struct Circle*) malloc(sizeof * p);
    if (p)
    {
        p->id =  2;
    }
    return p;
}
void Circle_Delete(struct Circle* pCircle) /*@default*/
{
    if (pCircle)
    {
        free((void*)pCircle);
    }
}

void Circle_Draw(struct Circle* pCircle)
{
	printf("Circle\n");
}

struct /*@ _union(Box | Circle)@*/ Shape
{
	int id;
};

void Shape_Delete(struct Shape* pShape) /*@default*/
{
    if (pShape)
    {
            switch (pShape->id)
            {
                case  2:
                    Circle_Delete((struct Circle*)pShape);
                break;
                case  1:
                    Box_Delete((struct Box*)pShape);
                break;
                default:
                break;
            }
    }
}
void Shape_Draw(struct Shape* pShape) /*@default*/
{
    switch (pShape->id)
    {
        case  2:
            Circle_Draw((struct Circle*)pShape);
        break;
        case  1:
            Box_Draw((struct Box*)pShape);
        break;
        default:
        break;
    }
}

