/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
/*Get ride of this with printTree*/
#include "lex.h"

#include "error.h"
#include "parser.h"
#include "backend.h"


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

  FILE *fptr;
  fptr = fopen("/home/fuzzy/projects/mac/test/test1.txt", "r");
  if (!fptr) {
    perror("Failed to open File\n");
    return 1;
  }

  
  AST_node *icode;
  if(!parseProgram(&icode, fptr)){
    error("No top-level expression");
  }
  fclose(fptr);
  stackMachineCodeGen(icode);

  return 0;
}
