/* MAC 
 * Caleb Walker
 * 07/07/2025
 * Interpreter
 */

#include "backend.h"

/**
 * @breif: private function that will process and interpret an static
 * @param: expr, an Expression struct that will be the head of the AST 
 * return: an Int repersenting the total of the AST
 */
static int processAndInterpret(Expression *expr){
  
  /*leaf node*/
  if(expr->type == 'D'){
    return expr->value;
  }

  /*Process left then right*/
  int left = processAndInterpret(expr->left);
  int right = processAndInterpret(expr->right);

  /*expr has to be an operator*/
  switch(expr->oper){
      case '+': return(left + right); break;
      case '*': return(left * right); break;
    }

}

/**
 * @breif: the public version of processAndInterpret that will interpret an AST
 * @param icode: an AST_node (EXpression struct) that will be the head of the AST
 * @note: this function will print out the result of the AST 
 */
int interpreter(AST_node *icode, FILE *fptr){
  if(icode == NULL){
    fprintf(stderr,"./mac: Error: invaild AST node");
    return ERROR;
  }
  int result = processAndInterpret(icode);
  fprintf(fptr, "%d\n",result);
  return SUCCESS;
}
