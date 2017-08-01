# C' (C Prime)

C' is a pre-processor for the C language plus some extensions that ouputs C 89 code.
The language accept for C' can be created using macros in C but C' will collect more informations.

Sample
```c
typedef struct 
{
   int type _defval(1);
} Z;

int main()
{
   Z z = _default {0};
}

```
When you compile this code the following code is generated:

```c
typedef struct 
{
   int type _defval(1);
} Z;

int main()
{
   Z z = _default {1};
}

```


## How can it help?

The task of code abstraction creates patterns and these patterns repeats.
C' has some build-in patterns and let you write your compiler extension to instanciate new parametrized types and functions.

## Language reference

### Initializers

### Build-in function instanciations Destroy, Delete, Create, Swap

### Buil-in parametrized types and its function instanciations

### Union types


## C11 grammar modifications

```
struct-union-specifier:
 
```



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



