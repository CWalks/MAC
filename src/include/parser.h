/* MAC 
 * Caleb Walker
 * 11/05/2025
 * Parser header file 
 */

#ifndef __parser_h__
#define __parser_h__

#include <stdlib.h>

typedef int Operator;

/*For readablity, read bottom up*/
typedef struct _expression{
  struct _expression *left, *right; /*Left and right child in the AST*/
  int value; /*if D, What is the digit*/
  Operator oper; /*if P, operation does it hold?*/
  char type; /*To tell if it is a digit or parenthesized expression ('D' or 'P')*/
} Expression;

typedef Expression AST_node;
extern int parseProgram(AST_node **);

#endif /*__parser_h__*/
