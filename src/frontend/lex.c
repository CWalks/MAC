/* MAC
 * Caleb Walker
 * 04/05/2025
 * Lexical analyzer
 */

#include "lex.h"
#include "error.h"

/* Global variables that will help with error handling */
int curLine = 1;
int curColumn = 0;

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
      curLine++; /* Incerment curLine & reset curColumn */
      curColumn = 0;
      return 1;
    case ' ':
    case '\t': return 1; /* ch is whitespace */
    default: return 0;
  }
}

/**
 * @breif Helper function that tells if a character (ch) is a digit
 * @param ch; a character repersented as an int
 * @return: 1 if ch is a digit otherwise 0
 */
static int isDigit (int ch){
  if(ch == '.'){parseError("unsupported float");}
  return ('0' <= ch && ch <= '9');
}

/**
 * @breif Gets the next token (non-layout character) and classifies it
 * 
 * @param fp a FILE pointer that will be the file to read from
 *
 * @note No peramiter or returns but this functions calls getchar()
 * and expects the input to be something for it to analyze 
 */
void getNextToken(FILE *fp){

  /*Check fp*/
  if (!fp) {
        parseError("lex: NULL file pointer\n");
    }
    int ch;
  
  /*Get next non-layout character*/
  do{
    ch = fgetc(fp);
    curColumn++;
    if (ch < 0){
      Token.class = EOF; 
      Token.repr = '#';
      return;
    }
  }while(layoutChar(ch));
  
  /*Now cla:ssify it*/
  if(isDigit(ch)){
    int value = 0;
    while(isDigit(ch)){
      value = (value * 10) + (ch - '0'); /*This builds the number allowing multi digit numbers*/
      ch = fgetc(fp);
      curColumn++;
    }
    ungetc(ch, fp);  /*put the non-digit back for future processing*/
    curColumn--;
    Token.class = DIGIT;
    Token.repr = value;
  

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
int getCurColumn(void){
  return curColumn;
}
