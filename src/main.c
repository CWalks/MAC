/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
#include "lex.h"
#include "error.h"
#include "parser.h"


void printTree(Expression *expr, int depth) {
  if (!expr) return;

  for (int i = 0; i < depth; i++) printf("  "); // Indent

  if (expr->type == 'D') {
    printf("Digit: %d\n", expr->value);
  } else if (expr->type == 'p') {
    printf("Operator: %c\n", expr->oper);
    printTree(expr->left, depth + 1);
    printTree(expr->right, depth + 1);
  }
}

int main(int argc, char *argv[]){
 

  ASTNode *icode;
  if(!parseProgram(&icode)){
    error("No top-level expression");
  }
 
  printTree(icode, 0);

  return 0;
}
