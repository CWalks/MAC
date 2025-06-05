/* MAC
 * Caleb Walker
 * 04/05/2025
 * Lexical analyzer
 */

#include "lex.h"

/* Global variables that will help with error handling */
int curLine = 1;
int curChar = 0;

/* Global variable that will hold the current token that the lexical 
 * analyzer is focusing on 
 */
TokenType Token;

/**
 * @breif Helper function that tells if the character (ch) a layout character(white space)
 * @param ch: ch is a character repersenting as an int
 * @return: 1 if ch is whitespace otherwise return 0
 * */
static int layoutChar (int ch){
  switch (ch){
    case '\n':
      curLine++; /* Incerment curLine & reset curChar */
      curChar = 0;
      return 1;
    case ' ': case '\t': return 1; /* ch is whitespace */
    default: return 0;
  }
}

/**
 * @breif Helper function that tells if a character (ch) is a digit
 * @param ch; a character repersented as an int
 * @return: 1 if ch is a digit otherwise 0
 */
static int isDigit (int ch){
  return ('0' <= ch && ch <= '9');
}

/**
 * @breif Gets the next token (non-layout character) and classifies it
 * @note No peramiter or returns but this functions calls getchar()
 * and expects the input to be something for it to analyze 
 */
void getNextToken(void){
    int ch;
  
  /*Get next non-layout character*/
  do{
    ch = getchar();
    if (ch < 0){
      Token.class = EOF; 
      Token.repr = '#';
      return;
    }
  }while(layoutChar(ch));
  
  /* Update curChar */
  curChar++;

  /*Now classify it*/
  if(isDigit(ch)){
    int value = 0;
    while(isDigit(ch)){
      value = (value * 10) + (ch - '0'); /*This builds the number allowing multi digit numbers*/
      ch = getchar();
    }
    ungetc(ch, stdin);  /*put the non-digit back for future processing*/
    Token.class = DIGIT;
    Token.repr = value;
    printf("%i\n", Token.repr);

  }else{
    Token.class = ch;
    Token.repr = ch;
  }
}

/*Returns the current line number*/
int getCurLine(void){
  return curLine;
}

/*Returns the current character number*/
int getCurChar(void){
  return curChar;
}
