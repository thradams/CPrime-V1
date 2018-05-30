struct Point
{
	int x /*@ = 1@*/;
	int y /*@ = 2@*/;

};


struct Line
{
	struct Point start, end;
};

int main()
{
	struct Point pt =/*@default*/ {/*.x=*/ 1, /*.y=*/ 2};
	struct Line ln =/*@default*/ {{/*.x=*/ 1, /*.y=*/ 2}, {/*.x=*/ 1, /*.y=*/ 2}};
}

