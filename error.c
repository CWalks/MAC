/* MAC
 * Caleb Walker
 * 13/05/2025
 * Error & exit 
 */

#include "error.h"

void error(char *msg){
  fprintf(stderr, "%s on line %i at charater %i\n", msg, curLine, curChar);
  exit(1);
}
