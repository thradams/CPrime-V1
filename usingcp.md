

## Using the compiler

Download binaries here: **JUST 123K**

https://github.com/thradams/CPrime/releases

It is just a folder with the compiler and configuration file.

The configuration file is used to inform the include directories
also the define some macros.


### Command line help Help
```
C' Version Oct  6 2017
https://github.com/thradams/CPrime

Syntax: cprime [options] [file ...]

Examples: cprime hello.c
          cprime -config config.h hello.c
          cprime -config config.h hello.c -o hello.c
          cprime -config config.h -P hello.c
          cprime -E hello.c
          cprime -P hello.c
          cprime -A hello.c

Options:
-config FILE                          Configuration file.
-help                                 Print this message.
-o FILE                               Sets ouput file name.
-E                                    Preprocess to console.
-P                                    Preprocess to file.
-A                                    Output AST to file.
-r                                    Reverts generation.

```

