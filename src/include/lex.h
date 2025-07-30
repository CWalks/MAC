/* MAC
 * Caleb Walker
 * 04/05/2025
 */

#ifndef __lex_h__
#define __lex_h__

#include <stdio.h>


/*Define constants*/
/*Values 0-255 are reserved for ASCII characters*/
#define DIGIT 256

typedef struct{
  int class;
  int repr;
}TokenType;

/* Hold the current token for analyzer */
extern TokenType Token;

/* Hold current line and character position for errors */
extern int curLine;
extern int curChar;

extern int getCurLine(void);
extern int getCurColumn(void);

/* Grabs the next non-layout token */
extern void getNextToken(FILE *fp);

/* */
#endif /*__lex_h__*/
