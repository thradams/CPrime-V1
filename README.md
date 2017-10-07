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

Currently, C' is generating default constructor, destructor, create, delete and static initializers.

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

You can choose the place where you are going to instanciate this function.
You can use the normal declaration in header files.


## Using the compiler
Donload the zip folder that contains the compiler and samples.

## References
This section will contain external references

## Videos



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



