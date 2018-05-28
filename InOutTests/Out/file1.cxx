
struct Point
{
  int x /*@ = 1@*/;
  int y /*@ = 2@*/;
};

int main()
{
  struct Point pt =/*@default*/ {/*.x=*/ 1, /*.y=*/ 2};
}