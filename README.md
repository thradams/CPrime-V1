# C'

![robot](/robots.jpg)
(Picture courtesy of my niece Bethina)

## Description

C' (pronounced c prime) is language and transpiler that extends the C language with some selected concepts of C++.
The C' will not map exactly the concept or syntax of C++ but you will find similarities.

The best introduction is to try the samples online.
http://www.thradams.com/web/cprime.html

This is the compiler (that is written in C) compiled to js using emscripten.

## Current Features 

### Especial functions
The compiler can generate something similar of C++ constructor,destructor, operator new and operator delete.

To generate these function use **default** at the end of declaration. 

The name of the functions and signature are used to undestand what you want to generate. For instance, use XXX_Create for "operator new"  XXX_Init for constructor, XXX_Destroy for destructor and XXX_Delete for operator delete. 

Input:

```c

typedef char * auto String;
struct X
{
    String Name;
    int i;
};

X * X_Create() default;
void X_Init(X * p) default;
void X_Destroy(X * p) default;
void X_Delete(X * p) default;

int main()
{
    X x = {};
    return 1;
}

```
Output:

```c

typedef char * /*@auto*/ String;
struct X
{
    String Name;
    int i;
};

struct X * X_Create() /*@default*/
{
    struct X *p = (struct X *) malloc(sizeof * p);
    if (p)
    {
        X_Init(p);
    }
    return p;
}
void X_Init(struct X * p) /*@default*/
{
    p->Name = 0;
    p->i = 0;
}
void X_Destroy(struct X * p) /*@default*/
{
    free((void*)p->Name);
}
void X_Delete(struct X * p) /*@default*/
{
    if (p)
    {
        X_Destroy(p);
        free((void*)p);
    }
}

int main()
{
    struct X x =/*@default*/ {0};
    return 1;
}

```
The **auto** type qualifier is a qualifier that can be applied in pointers. When a pointer has auto it means that the pointer
is the **owner of the pointed object**. This information is used to generate destructors.
See the declaration of String and the generated destructor X_Destroy.

The ouput "annotated C" also can be used to revert to the orignal code.
In other words "annotated C" is just another view to the same source. The compiler can be used in any C IDE with this annotated syntax.
The extended syntax can be used for a better undestanding a high level view of the code.

### Dynamic Arrays (like std::vector)
Instead of using templates syntax, we define the struct that represents the data and the algorithmls like push_back are created automatically.

```c

struct Item
{
	int i;
};


Item* Item_Create() default;
void Item_Delete(Item* p) default;

struct Items
{
	Item * auto * auto sizeof(Size) pData;
	int Size;
	int Capacity;
};


void Items_PushBack(Items* pItems, Item* pItem) default;
void Items_Destroy(Items* pItems) default;


int main(int argc, char **argv)
{
	Items items = {};

	Items_PushBack(&items, Item_Create());
	Items_PushBack(&items, Item_Create());
	Items_PushBack(&items, Item_Create());

	for (int i = 0; i < items.Size; i++)
	{
		printf("%d\n", items.pData[i]->i);
	}

	Items_Destroy(&items);
	return 0;
}

```
```c

struct Item
{
	int i;
};


struct Item* Item_Create() /*@default*/
{
    struct Item* p = (struct Item*) malloc(sizeof * p);
    if (p)
    {
        p->i = 0;
    }
    return p;
}
void Item_Delete(struct Item* p) /*@default*/
{
    if (p)
    {
        free((void*)p);
    }
}

struct Items
{
	struct Item * /*@auto*/ * /*@auto*/ /*@size(Size)@*/ pData;
	int Size;
	int Capacity;
};


void Items_PushBack(struct Items* pItems, struct Item* pItem) /*@default*/
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
void Items_Destroy(struct Items* pItems) /*@default*/
{
    for (int i = 0; i < pItems->Size; i++)
    {
        Item_Delete(pItems->pData[i]);
    }
    free((void*)pItems->pData);
}


int main(int argc, char **argv)
{
	struct Items items =/*@default*/ {0};

	Items_PushBack(&items, Item_Create());
	Items_PushBack(&items, Item_Create());
	Items_PushBack(&items, Item_Create());

	for (int i = 0; i < items.Size; i++)
	{
		printf("%d\n", items.pData[i]->i);
	}

	Items_Destroy(&items);
	return 0;
}


```
### Initialization
Struct data members can have initializers. This initializers are used to generate special functions and for the default initialization.

```c
struct Point
{
  int x = 1;
  int y = 2;
};

struct Line
{
  Point start, end;
};

int main()
{
  Point pt = {};
  Line ln = {};
}
```

```c
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

```


### Lambdas 
Lambdas without capture are implemented using C++ syntax.

## Next steps

[Learn more](learn.md) about the generated code.

[Using](usingcp.md) the compiler.


## Background & Motives

I work professionally with C++ since 2000 keeping my knowledge about C++ updated. After 2014 I noticed that my interest for the C language was gradually increasing. 

It is hard to summarize the reasons for that, but I can say that the rise of complexity and fancy libraries and styles of C++ are not adding value in the software I write.  I still like C++ and it is possible to use C++ compilers in way that meet my expectations of simplicity and maintenance. However, I think I can have a more portable, fast and easy to maintaing and teach code with C.

In 2012, I opened a topic in com.lang.C++.moderated about the possibility of to have “smart pointers” inside the C++ type system and later in 2015 I watched the Herb Sutter presentation cppcon “Writing Good C++14 By Default" where he talks about memory ownership checked statically.  After this point I became very motivated to implement the checked ownership analysis in the C language as part of the type system and I started to write my C parser in C. 

During the development of this parser and static analysis, I had some difficulties with the C language that have already begin addressed by C++, like to generate special member functions. I was doing constructors and destructor by hand and wondering how they could be designed and used in C. 

At some point I decided that I should address the problem to work better with C before to do the static analysis and then I renamed the project to C’ cprime.  Because I want a tool to be useful now (not something experimental) I spent some time to solve the problem of generating C code from C code including the preprocessed parts. This allowed me to use existing C compilers and IDEs.
C’ can generate destructors for structs and can have owner pointers in the type system. The motivation for static analysis still there and it is also related with code generation. More motivations like containers and polymorphism are included in the C’ as well.



## Roadmap

At some point I want to include static analysis again and check the onwership and null pointers as part of the type system. 





