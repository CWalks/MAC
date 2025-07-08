/*MAC 
 * Caleb Walker
 * 28/06/2025
 * C code gen 
 */

#include "backend.h"

/**
 * @breif A helper function that will return a number
 * that can be used in a temp variable name 
 */
static int tempVarName(){
  static int var = 0;
  return var++;
}

/**
 * @breif: a private function that will process an AST and generate C code
 * pram: expr An Expression struct that will be the head of the AST 
 * return: An int repersenting the amount of temp variables used for the
 * C code. This will be used in the return statement of the generated C code
 * @note: This function will recursively go through the AST checking each node and will
 * print out the instruction of how to solve the expression
 */  
static int processForCGen(Expression *expr){
   
  /*If at a leaf node*/
  if(expr->type == 'D'){
    int var = tempVarName();
    printf("int temp%d = %d; \n", var, expr->value);
    return var;
  }
  /*If both children are digits, this must be a an operator*/
  if(expr->left->type == 'D' && expr->right->type == 'D'){
    int var = tempVarName();
    printf("int temp%d = %d %c %d; \n", var, expr->left->value, expr->oper ,expr->right->value);
    return var;
  }

  int left = processForCGen(expr->left);
  int right = processForCGen(expr->right);
  int result = tempVarName();

  char oper;
  switch(expr->oper){
    case '+': oper = '+'; break;
    case '*': oper = '*'; break;
  }

  printf("int temp%d = temp%d %c temp%d;\n",result, left, oper, right);
  return result;

}

/**
 * @breif: the public version of processForCGen that will process an AST
 * and generate C code
 * @param icode: and AST_node (Expression) that will the be head of the AST
 */
int cCodeGen(AST_node *icode){
  if(icode == NULL){
    fprintf(stderr,"./mac: Error: invaild AST node");
    return ERROR;
  }
  printf("#include<stdio.h>\n\nint main(void){\n");
  int result = processForCGen(icode);
  printf("printf(\"%%d\\n\", temp%d);\n}\n", result);

  return SUCCESS;
}


