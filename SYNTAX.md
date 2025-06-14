# *Syntax guild for MAC* 

This document will describe valid syntax for writing arithmetic expressions for MAC

## Overview
MAC will understand bracket arithmetic expressions

as of now you can pipe text for MAC to read
'echo "((4 * 5) + (9 * 1))" | ./mac'

This will change in the future and MAC will be able to read files but as of now
this is how it is done.

I am still in the building phase so MAC output will be a representation of an AST 

This language supports:
- Single-digit integer values (`0` to `9`) (this will change)
- Binary arithmetic operations: addition, multiplication (subtraction and division will be added)
- Fully parenthesized expressions
- No variables or assignments (This will also change in the future)

## Token

#### Digits 
A digit will be made up of number from '0' to '9'
exmaple: 5, 52, 042

#### Operators
A operator will be either '+' or '*'

## Grammar
expression → DIGIT | '(' expression operator expression ')'

operator   → '+' | '*' 

Whitespace ignored 

## Stack Machine Generation
This code generation will output code for an abstract stack machine.

### How does the stack machine work?
It will push numbers onto the abstract stack.
When it does an operation (ADD or MULT) it takes the 
top two number then preforms the operation on them. That 
new number takes the spot of the first of the 2 numbers taken.

Right now this is just abstract but maybe as a future project someone can
make a VM that would actually run this ;)




