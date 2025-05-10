/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
#include "lex.h"

int main(int argc, char *argv[]){
  
  getNextToken();

  printf("%c \n", Token.repr);
  return 0;
}
