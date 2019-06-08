enum E
{
    A,
    B
};

struct X
{
    enum E e;
};

void X(struct X * p) /*@: init*/ /*@default*/
{
    p->e = A;
}
int main()
{

}