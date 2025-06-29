/* MAC 
 * Caleb Walker
 * 10/06/2025
 * backend header file 
 */ 

#ifndef __BACKEND_H__
#define __BACKEND_H__

#include <stdio.h>
#include "parser.h"

#define ERROR 1
#define SUCCESS 0

extern int stackMachineCodeGen(AST_node *);
extern int cCodeGen(AST_node *);

#endif /* __BACKEND_H__*/
