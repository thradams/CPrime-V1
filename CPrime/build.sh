#!/bin/bash
# A sample Bash script, by Ryan
gcc -c Ast.c
gcc -c AllTemplates.c
gcc -c CodePrint.c
gcc -c Macro.c
gcc -c MapTemplate.c
gcc -c PPToken.c
gcc -c Stream.c
gcc -c TokenArray.c
gcc -c Array.c
gcc -c AstPrint.c
gcc -c CPrime.c
gcc -c Map2.c
gcc -c Parser.c
gcc -c Scanner.c
gcc -c StringEx.c
gcc -c UnionTemplate.c
gcc -c ArrayTemplate.c
gcc -c BasicScanner.c
gcc -c ListTemplate.c
gcc -c Map.c
gcc -c Path.c
gcc -c StrBuilder.c
gcc -c SymbolMap.c
gcc -c UnitTest.c

gcc  Ast.o  AllTemplates.o  CodePrint.o  Macro.o  MapTemplate.o  PPToken.o  Stream.o   TokenArray.o   Array.o   AstPrint.o   CPrime.o   Map2.o  Parser.o Scanner.o  StringEx.o  UnionTemplate.o  ArrayTemplate.o  BasicScanner.o  ListTemplate.o Map.o  Path.o  StrBuilder.o  SymbolMap.o  UnitTest.o -o cprime