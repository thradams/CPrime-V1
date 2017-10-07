# C'

How can I help you write and maintain your code?

![robot](/robots.jpg)

## What is C' ?
C'(pronounced c prime) is tool to help writing C programs.

The input for C' is your C source code with some annotations. 

The annotations are done using some empty macros and your input and 
ouput are C sources.

Your includes, macros, formatting, comments 
are preserved at the ouput.


## How can C' help?
C' can **generate** and **maintain** code for you.

Currently, C' is generating constructor, destructor, create, delete and static initializers.


Sample
```c
struct X
{
  int i;
};
```
To generate a initialization function for this struct just type:

```c
void X_Init(struct X* pX) _default;
```
When you compile this code you get:
```c
void X_Init(struct X* pX) _default
{
   pX->i= 0;
}
```

C' will maintain this implementation for you because the function use the macro _default.

More features are being considered like containers, helper functions etc. 

Feel free to sugest features.



## Goals

 * Be useful today. It can help existing C code at any time together with
   your existing compiler and code.
 * Create a tool to help creation and maintenance of  C code
 * Keep the input valid C code, then we can use in existing IDEs and compilers
 * Make the C development more produtive
 * For the future, lint, format, anything that can help
 
## Using the compiler

Download the cp.zip here:
https://github.com/thradams/CPrime/releases

Open the command line and try some samples:

See samples.txt

```c
cp hello.c -o hello2.c
```

type cp

```
C' Version Oct  6 2017
https://github.com/thradams/CPrime

Syntax: cp [options] [file ...]

Examples: cp hello.c
          cp -config config.h hello.c
          cp -config config.h hello.c -o hello.c
          cp -config config.h -P hello.c
          cp -E hello.c
          cp -P hello.c
          cp -A hello.c

Options:
-config FILE                          Configuration file.
-help                                 Print this message.
-o FILE                               Sets ouput file name.
-E                                    Preprocess to console.
-P                                    Preprocess to file.
-A                                    Output AST to file.
-r                                    Reverts generation.

```

## Include directories

Use #pragma dir , see sample on config.h.

I tested the compiler only with includes of Visual Studio 2017.

I added some macros to parse the headers. This is the config file that works 
for me using Visual Studio 2017.

https://github.com/thradams/CPrime/blob/master/CPrime/vs2017.h

Maybe we can find some parser problems using gcc. I can fix the problems
and help to create the configuration file for gcc.

# Things to try:

### Static initialization

```c
typedef struct 
{
  int x, y;
} Point;

int main()
{  
  Point pt = _default {}
}

```

```c
typedef struct 
{
  int x = 1;
  int y = 2;
} Point;

int main()
{  
  Point pt = _default {}
}

```

## constructor / destructor / create / delete / _auto

The generated functions are based on name patterns X_Init, X_Create, X_Destroy, X_Delete.
Where X can be typedef or struct name.

```c

typedef char * _auto String;

struct Person
{
    String Name;
    int age /*= -1*/;
    _Bool b /*= true*/;
};

struct Person* Person_Create();
void Person_Delete(struct Person* person);
 
int main()
{
    struct Person person = _default {0};
    struct Person* pPerson = Person_Create();
    Person_Delete(pPerson);
    return 0;
}

struct Person* Person_Create() _default;

//Remove Destroy and see what happens with Delete
//Create Init and see what happens with Create
//void Person_Init(struct Person* person) _default;
//Remove _auto from String and see what happens

void Person_Destroy(struct Person* person) _default;
void Person_Delete(struct Person* person) _default;
```
Diferent name patterns can be configured in the future.

Other designs have been considered:

```c
void X_init(X* p) _init;
void X_dtor(X* p) _destroy;
or
void X_init(X* p) _cp("init");
void X_destructor(X* p) _cp("destroy");
```

Simple linked list:

```c
struct Node {
	struct Node* _auto pNext;
};

typedef struct
{
	struct Node* _auto pHead, pTail;
} List;

struct Node* Node_Create() _default;
void Node_Delete(struct Node* pNode) _default;
void List_Destroy(List* pList) _default;
```

If you want to compile the generated code in a tradicional C compiler you must
define empty macros _auto, _default.

I use the option /FI from microsoft compiler for this task.
https://msdn.microsoft.com/en-us/library/8c5ztk84.aspx


I have posted on twitter GIFs that have some samples
of code generation.

https://twitter.com/thradams

## Old Videos


https://www.youtube.com/edit?o=U&video_id=LmUebDRGE1A

Initializers

https://www.youtube.com/watch?v=lIRLijA_n2Q&t=19s

https://www.youtube.com/edit?o=U&video_id=mMHyeDZ0iA8

Build-in function instanciation destroy , create, delete

https://www.youtube.com/watch?v=yaa6uhHi2Xk

Build-in enum to string

https://www.youtube.com/watch?v=2qvCglaRNDU




