/* MAC 
 * Caleb Walker
 * 12/05/2025
 * Error header file 
 */

#ifndef __error_h__
#define __error_h__

#include <stdlib.h>

/*Needed for curChar & curLine*/
#include "lex.h"  

/* Prints out a given error message then exits the program */
extern void error(char *msg);

#endif /*!__error_h__*/
