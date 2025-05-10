/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
#include "lex.h"

int main(int argc, char *argv[]){
 
  do {
  getNextToken();
  printf("%c \n%i \n", Token.repr, Token.class);
  }while(Token.class != 256);

  return 0;
}
