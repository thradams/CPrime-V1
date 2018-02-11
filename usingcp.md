

## Using the compiler

Download binaries here: **JUST 390K**

https://github.com/thradams/CPrime/releases

For windows there is a setup.

Open the command line and try some samples:

```c
cprime hello.c -o hello2.c
```
This will compile hello.c to hello2.c

## Include directories (Configuration file)

Because C' is a full parser it requires the include dir.

See [config files](config.md) for some configuration files.

### Command line to use the config file:

```c
cprime -config config.h hello.c -o hello2.c
```

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

