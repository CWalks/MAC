/* MAC
 * Caleb Walker
 * 13/05/2025
 * Error & exit 
 */

#include "error.h"

/**
  * @breif: prints out a given message to standard error then exits the program
  * @param msg: A string that discribes the error
  * @warning this function will exit the program
  */
void parseError(char *msg){
  fprintf(stderr,"Parse error: %s.\n", msg);
  exit(1);
}
