/* MAC 
 * Caleb Walker
 * 10/06/2025
 * Stack Machine code gen 
 */

#include "backend.h"

/**
 * @breif: A private function that will process an AST and generate code
 * for a abstract stack Machine
 * @param expr: An Expression struct that will be the head of the AST
 * @note: This function will recursively go through the AST checking each node and will
 * print out the instruction of how to solve the expression
*/ 
static void processForSM(Expression *expr, FILE *fptr){
  switch (expr->type) {
    case 'D':
      fprintf(fptr, "PUSH %d\n",expr->value);
      break;
    case 'P':
      processForSM(expr->left, fptr);
      processForSM(expr->right, fptr);
      switch(expr->oper){
        case '+':
          fprintf(fptr, "ADD\n"); 
          break;
        case '*':
          fprintf(fptr, "MULT\n");
          break;
      }
      break;
  }
}

/**
 * @breif: the public version of processFor_SM that will process an AST
 * and generate stack code
 * @param icode: and AST_node (Expression) that will the be head of the AST
 */
int stackMachineCodeGen(AST_node *icode, FILE *fptr){
  if(icode == NULL){
    fprintf(stderr,"./mac: Error: invaild AST node");
    return ERROR;
  }
  processForSM(icode, fptr);
  return SUCCESS;
}
