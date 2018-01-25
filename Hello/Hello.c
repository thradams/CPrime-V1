#include "config.h"


struct Box
{
  int i _defval(1);
};

struct Circle
{
  int i _defval(2);
};

struct _union(Box | Circle)  Shape
{
  int id;
} Shape ;
 
#pragma region cprime Shape
inline struct Circle* Shape_As_Circle(struct Shape* p) { return p->id == 2 ? (struct Circle*) p : 0;}
inline struct Shape* Circle_As_Shape(struct Circle* p) { return (struct Shape*) p; }
inline struct Box* Shape_As_Box(struct Shape* p) { return p->id == 1 ? (struct Box*) p : 0;}
inline struct Shape* Box_As_Shape(struct Box* p) { return (struct Shape*) p; }
#pragma endregion cprime





























