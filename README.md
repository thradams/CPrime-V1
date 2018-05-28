# C'

Let´s do pair programming!

![robot](/robots.jpg)
(Picture courtesy of my niece Bethina)

## Description

C' (pronounced c prime) is a tool to help C programmers to write and maintain C code.
The tool edit the file in place like a refactoring tool. You can think on it as a pair programming with a robot.
Some implementation and maintenance, like destructor for data structures, are delegated for the robot and you are free to think in the program's logic instead of code something that can be automatically generated.

## How it works?

See it online
[playground](http://thradams.com/web/cprime.html)

You can delegate to the robot the implementation of some functions.

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

If the struct X is changed then the C' will update the implementation for you.

Other functions like init, delete and destroy also can be generated.

Video of basic features:

https://www.youtube.com/watch?v=cFHL6cf1n_k&feature=youtu.be

Online

http://thradams.com/cprime/hello3.html

# Next steps

[Learn more](learn.md) about the generated code.

[Using](usingcp.md) the compiler.


## Background & Motives

I work professionally with C++ since 2000 keeping my knowledge about C++ updated. After 2014 I noticed that my interest for the C language was gradually increasing. 

It is hard to summarize the reasons for that, but I can say that the rise of complexity and fancy libraries and styles of C++ are not adding value in the software I write.  I still like C++ and it is possible to use C++ compilers in way that meet my expectations of simplicity and maintenance. However, I think I can have a more portable, fast and easy to maintaing and teach code with C.

In 2012, I opened a topic in com.lang.C++.moderated about the possibility of to have “smart pointers” inside the C++ type system and later in 2015 I watched the Herb Sutter presentation cppcon “Writing Good C++14 By Default" where he talks about memory ownership checked statically.  After this point I became very motivated to implement the checked ownership analysis in the C language as part of the type system and I started to write my C parser in C. 

During the development of this parser and static analysis, I had some difficulties with the C language that have already begin addressed by C++, like to generate special member functions. I was doing constructors and destructor by hand and wondering how they could be designed and used in C. 

At some point I decided that I should address the problem to work better with C before to do the static analysis and then I renamed the project to C’ cprime.  Because I want a tool to be useful now (not something experimental) I spent some time to solve the problem of generating C code from C code including the preprocessed parts. This allowed me to use existing C compilers and IDEs.
C’ can generate destructors for structs and can have owner pointers in the type system. The motivation for static analysis still there and it is also related with code generation. More motivations like containers and polymorphism are included in the C’ as well.

## Two generatarion models

The first one is the model described here, were the source is changed "in place" like a refactoring tool. The cprime code itself is compiled using this mode. Of course at the begging the source was pure C. I  a had a very good experience adding cprime features for the code that was orinally using only C. This "in place" mode made the change very simple and secure. After some time, I enjoyed the beneficts of using cprime. When I had to modify some AST structs cprime just wrote my code; 49% of the lines AST.c are generated.
This first mode has motivated the logo and the idea of pair programming with an robot.

The second model is to generate a new file, and keep the source code smaller without the generated code.
I don´t want to use the second model before to have a complete solution for debug and edit the code. The second model also can be used to convert from C2x to C89 for instance. Many new features could be used and translated for old compilers.
If you know babel https://babeljs.io/ then you can imagine the cprime like a babel for C.


## Current Status & Goals

The C’ can be used today as command line tool to generate and maintain code. You can remove the usage of the tool at any time and use the generated code as normal C code. So the evaluation of the tool is totally uncompromised. I am already using the tool to generate itself. 
 

## Roadmap

The improvements on C’ will focus in stability of basic features. I am also planning to add lambdas in the C language to allow replace C++ in other kind of projects where lambdas are used.

At some point I want to include static analysis again and check the onwership and null pointers as part of the type system. 




## Old Videos (experimental features considered)

Polymorphism and Dynamic Array Demo

https://www.youtube.com/watch?v=vzouZGBV8YQ


https://www.youtube.com/edit?o=U&video_id=LmUebDRGE1A

Initializers

https://www.youtube.com/watch?v=lIRLijA_n2Q&t=19s

https://www.youtube.com/edit?o=U&video_id=mMHyeDZ0iA8

Build-in function instanciation destroy , create, delete

https://www.youtube.com/watch?v=yaa6uhHi2Xk

Build-in enum to string

https://www.youtube.com/watch?v=2qvCglaRNDU




