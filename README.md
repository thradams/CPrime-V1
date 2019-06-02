
## Description

C' (cprime) is a C compiler that generates C code.  The generated code is intended to be readably and formatation is kept together with comments and macros.

It is a new CFront following a new path.


See it online:
http://www.thradams.com/web/cprime.html

## C language extensions tour

### Struct members with initializers

```c
struct Point
{
  int x = 1;
  int y = 2;
};
```

### Default initializer
```c
int main()
{
  struct Point pt = {}; //same as {.x = 1, .y = 2}
}
```

### Lambda Expression

This is similar of C++. The diference is that we don't capture and the result of the lambdas expression is always a pointer to function.

```c
void Run(void (*callback)(void*), void* data);
int main()
{  
  Run([](void* data) {
    printf("first");
    Run([](void* data){
      printf("second");
    }, 0);     
  }, 0);
}
```

the generated code is :
```c

void Run(void (*callback)(void*), void* data);

static void _lambda_1(void* data){
      printf("second");
    }

static void _lambda_0(void* data){
  
    printf("first");
    Run(_lambda_1, 0);     
  }

int main()
{  
  Run(_lambda_0, 0);
}

```
### Function tags

Functions can have a extra identifier that is called function tag.

```c
void FunctionName(int) : functionTag;
```
Function can be tagged in one place

```c
void FunctionName(int) : functionTag;

//this is the same function with the same tag
void FunctionName(int); 
```
### Explicit function instantiation 
The compiler knows how to implement some functions for any struct.

They are:
* init     - initialize structs with default values
* destroy  - free resources used by structs
* create   - Allocates and initialize the object on the heap (malloc)
* delete   - Destroy a object created on heap and frees the memory

Any of these functions can be implemented automaticaly for any struct.

It is called  explicit instantiation because declaration and point of instantiation is given by the programmer.

Declaration sample:
```c
//file X.h
struct X {
    int i = 3;
};

struct X * makeX() : create;
```

Instantiation sample:

The compiler will understand that makeX is instance of 'create' reading the function tag.
The instantiation point is defined with the keyword default. 

```c
//file X.c
#include "X.h"

//this is the point of instantiation
struct X * makeX() default;
```

### Auto pointer qualifier

Pointers can be qualified with the 'auto' keyword.

This tells the compiler that the pointer is the owner of the pointed object.

In pratice this is used for destroy and delete instantiation:

For instance:

```c
struct X {
    char * auto Text;
};

void DestroyX(struct X *) : destroy;
```

The destroyX instantiation will be

```c
void DestroyX(struct X *) default
{
    free((void*)->Text);
}
```

### Pointer qualifier [size]
Structures member pointers can be qualified with '[size]' .

This tells the compiler that the pointer is pointing size objects where size is also a member of the struct.

```c
struct Item {
	char * auto Text;
};

struct Items
{
	struct Item * auto * auto [Size] pData;
	int Size;	
};


void Items_Destroy(struct Items* pItems) : destroy;
```

This 'struct Item * auto * auto [Size] pData;' can be read as "pData is a onwer pointer of Size onwer pointers of struct Item".

Items_Destroy is instanciated as:

```c
void Items_Destroy(struct Items* pItems) /*@default*/
{
    if (pItems->pData)
    {
        for (int i = 0; i < pItems->Size; i++)
        {
            free((void*)pItems->pData[i]->Text);
        }
        free((void*)pItems->pData);
    }
}
```

## Automatic function tags
This is an optional feature controled by compiler flags. We can define that functions with the aproprieted signature and know suffixes like create, init, destroy and delete (case insensitive) will be automatically tagged.

For instance:

```c
void Items_Destroy(struct Items* pItems);
```
Is automatically tagged as

```c
void Items_Destroy(struct Items* pItems) : destroy;
```
## Automatic instanciation of Push
Push is a function that adds a new item inside a known data structure. 

It cannot be instanciated for any type. The current implementation allow the instanciation of push for vector and linked list only.

```c
struct Item {
    int i;
    struct Item* pNext;
};

struct Items {
    struct Item* pHead,* pTail;
};

void Items_Push(struct Items* pItems, struct Item* pItem) : push;
```
Instantiation for linked list with pHead and pTail

```c
void Items_Push(struct Items* pItems, struct Item* pItem) default
{
    if (pItems->pHead == 0)
    {
        pItems->pHead = pItem;
    }
    else
    {
        pItems->pTail->pNext = pItem;
    }
    pItems->pTail = pItem; 
}
```
```c
struct Item
{
    int i;
    struct Item* pNext;
};

struct Items
{
    struct Item** pData;
    int Size;
    int Capacity;
};

void Items_Push(struct Items* pItems, struct Item* pItem) : push default;

```

```c

void Items_Push(struct Items* pItems, struct Item* pItem) default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        struct Item** pnew = pItems->pData;
        pnew = (struct Item**)realloc(pnew, n * sizeof(struct Item*));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
    pItems->pData[pItems->Size] = pItem;
    pItems->Size++;
}


```
### Especial comments
CPrime has especial comments that are ignored.

```c
/*@
and 
*/

```
These two sequences will be interprted as spaces.

These special comments where created to allow C language extensions be created using normal C syntax.

For instance, this C code parsed by C compiler will see comments

```c
//file X.h
struct X {
    int i /*@= 3*/;
};

struct X * makeX() /*@: create*/;
```
but cprime compiler will see:

```c
//file X.h
struct X {
    int i = 3;
};

struct X * makeX() : create;
```
>
> CPrime is compiled using itself. I use VC++ compiler and IDE with this annotation method.
> Without this method I would need a IDE plugin, and this is something I dont have at this time.
>

### Runtime polymorphism

We can specify in cprime the set of types for a pointer. In C for instance, void* means a pointer to any object.
Instead of saying pointer to any object I want to especify the list of possible types.

The syntax is :

```c
struct Box {
    int id = 1;
};

struct Circle {
    int id = 2;
};

struct <Box | Circle> Shape {
    int id;
};

```
We can read as "Shape is a pointer to Box or Circle". The pointed object have some common initial struct member that is called discriminant. With this discrimenti prime can do the runtime polimorphism.

We can instanciate a function like this:

```c
void Shape_Draw(struct Shape* pShape) default;
```
resulting in:

```c
void Shape_Draw(struct Shape* pShape) default
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
```



## Using the compiler
The compiler can be used together with traditional C compilers like VC++, clang or gcc.



## Welcome

I work professionally with C++ since 2000 keeping my knowledge about C++ updated. After 2014 I noticed that my interest for the C language was gradually increasing. 

In 2012, I opened a topic in com.lang.C++.moderated about the possibility of to have “smart pointers” inside the C++ type system and later in 2015 I watched the Herb Sutter presentation cppcon “Writing Good C++14 By Default" where he talks about memory ownership checked statically.  After this point I became very motivated to implement the checked ownership analysis in the C language as part of the type system and I started to write my C parser in C. 

During the development of this parser and static analysis, I had some difficulties with the C language that have already begin addressed by C++, like to generate special member functions. I was doing constructors and destructor by hand and wondering how they could be designed and used in C. 

At some point I decided that I should address the problem to work better with C before to do the static analysis and then I renamed the project to C’ cprime.  Because I want a tool to be useful now (not something experimental) I spent some time to solve the problem of generating C code from C code including the preprocessed parts. This allowed me to use existing C compilers and IDEs.
C’ can generate destructors for structs and can have owner pointers in the type system. The motivation for static analysis still there and it is also related with code generation. More motivations like containers and polymorphism are included in the C’ as well.

 
