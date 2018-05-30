
typedef char * auto String;
struct X
{
	String Name;
	int i;
};

X* X_Create() default;
void X_Init(X* p) default;
void X_Destroy(X* p) default;
void X_Delete(X* p) default;

int main()
{
	X x = {};
	return 1;
}
