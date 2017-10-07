# C'

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



## Old Videos


https://www.youtube.com/edit?o=U&video_id=LmUebDRGE1A

Initializers

https://www.youtube.com/watch?v=lIRLijA_n2Q&t=19s

https://www.youtube.com/edit?o=U&video_id=mMHyeDZ0iA8

Build-in function instanciation destroy , create, delete

https://www.youtube.com/watch?v=yaa6uhHi2Xk

Build-in enum to string

https://www.youtube.com/watch?v=2qvCglaRNDU

### Function and Parametric API documentation
This section will contain the API reference to access the AST and build your own patterns.



