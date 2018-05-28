
struct Point
{
  int x _defval( 1);
  int y _defval( 2);
};

int main()
{
  struct Point pt =/*@default*/ {/*.x=*/ 1, /*.y=*/ 2};
}