
struct Point
{
	int x _defval( 1);
	int y _defval( 2);
};

struct Line
{
	struct Point start, end;
	
};

int main()
{
	struct Line line =/*@default*/{{/*.x=*/ 1, /*.y=*/ 2}, {/*.x=*/ 1, /*.y=*/ 2}};
	return 0;
}
