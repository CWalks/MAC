/* MAC
 * Caleb Walker
 * 04/05/2025
 */

#ifndef __lex_h__
#define __lex_h__

#include <stdio.h>


/*Define constants*/
/*Values 0-255 are reserved for ASCII characters*/
#define EOF 256
#define DIGIT 257

typedef struct{
  int class;
  char repr;
}Token_type;

extern Token_type Token;
extern void getNextToken(void);

#endif /*__lex_h__*/
