/* MAC
 * Caleb Walker
 * 13/05/2025
 * Error & exit 
 */

#include "error.h"

/**
  * prints out a given message to standard error then exits the program
  * @warning this function will exit the program
  */
void error(char *msg){
  fprintf(stderr, "ERROR: %s on line %i at charater %i\n", msg, curLine, curChar);
  exit(1);
}
