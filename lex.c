/* MAC
 * Caleb Walker
 * 04/05/2025
 * Lexical analyzer
 */

#inlcude "lex.h"

/*Helper function that tells if the character a layout character(white space)? */
static int layoutChar (int ch){
  switch (ch){
    case ' ': case '\t': case '\n': return 1;
    default: return 0;
  }
}

/*The example in the book uses this as a gobal variable
 * so I will follow that for now but I can change it later*/
Token_type Token;

/* 
 * Gets the next token (non-layout character) and classifies in
 */
void getNextToken(void){
    int ch;
  
  /*get a non-layout character*/
  do{
    ch = getchar();
    if (ch < 0){
      Token.class = EOF 
      Token.repr = '#';
      return;
    }
  }while(layoutChar(ch))

  /*Now classify it*/
  if('0' <= ch && ch <= '9'){
    Token.class = DIGIT;
  }else{Token.class = ch;}

  Token.repr = ch;

}
