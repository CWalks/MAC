/* MAC
 * Caleb Walker
 * 13/05/2025
 * Error & exit 
 */

#include "error.h"
/*Needed for curChar & curLine*/
#include "lex.h"  

/**
  * @breif: prints out a given message to standard error then exits the program
  * @param msg: A string that discribes the error
  * @warning this function will exit the program
  */
void error(char *msg){
  fprintf(stderr, "ERROR: %s.\nFound on line %i at charater %i\n", msg, curLine, curChar);
  exit(1);
}
