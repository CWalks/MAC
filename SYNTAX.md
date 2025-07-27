# *Syntax guild for .arth files* 

This document will describe valid syntax for writing arithmetic expressions (.arth) for MAC

## Overview 
MAC stands for Mini Arithmetic Calculator/Complier and its purpose is to understand bracket
arithmetic expressions in file (I named these files .arth). There are 3 main modes for MAC 
which will be explained later.

## .arth files
.arth files supports:
- bracketed arithmetic expressions
//- variables or assignments (This will also change in the future)

### Grammar for bracketed arithmetic expressions
digit -> '[0-9]+'
operator   → '+' | '*' 
expression → digit | '(' expression operator expression ')'

### Examples
`( (4 * 59  ) + (09  * 0))`
`(9 + 242)`
`8`

#### Example of an .arth file
```
(((42 + 3) + 123) * (21+ 0012))
```
# How to use MAC

### Quick Guide
-s : stack Machine generation
-c : C generation
-i : interpreter (default)

`./mac [-c | -s | -i]  <source file> [<destination file> | -d]`

## Flags 

### Stack Machine Generation
This code generation will output code for an abstract stack machine and is used with the -s 
flag.

#### How does this abstract stack machine work?
It will push numbers onto the abstract stack.
When it does an operation (ADD or MULT) it takes the 
top two number then preforms the operation on them. That 
new number takes the spot of the first of the 2 numbers taken.

### C Generation
This takes an .arth file and compiles it to usable C code. It uses temp variables to store 
and calculate the total from the .arth file then prints out the result. This mode uses the
-c flag.

### Interpreter
This will interpret the .arth file and print out the result. This mode uses the -i flag and
is the defeat mode for MAC.

### Dry flag
There is a dry flag that will print out the results to stdout rather to a destination file.
This flag, -d, is used along side one of the three modes for mac (-s, -c, -i).
#### Example
`./mac -c -d <source file>`









