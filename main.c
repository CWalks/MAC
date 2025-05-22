/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
#include "lex.h"
#include "error.h"
#include "parser.h"

int main(int argc, char *argv[]){
 

  ASTNode *icode;
  if(!parseProgram(&icode)){
    error("No top-level expression");
  }
  printf("%c\n",icode->type);
  return 0;
}
