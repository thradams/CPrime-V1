# C'

![robot](/robots.jpg)
(Picture courtesy of my niece Bethina)

## Description

C' (pronounced c prime) is language and transpiler that extends the C language with some selected concepts of C++.
The C' will not map exactly the concept or syntax of C++ but you will find similarities.

The best introduction is to try the samples online.
http://www.thradams.com/web/cprime.html

This is the compiler (that is written in C) compiled to js using emscripten.


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



## Roadmap

At some point I want to include static analysis again and check the onwership and null pointers as part of the type system. 





