/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
#include "parser.h"
#include "backend.h"

/*For getopt_long*/
#include <getopt.h>

/*For strcmp*/
#include <string.h>

int main(int argc, char *argv[]){

  /* If there are too many or not enough flags*/
  if(argc == 1){
    fprintf(stderr, "Usage: %s [-c | -s | -i]  <source file> <destination file>\n", argv[0]);
    return EXIT_FAILURE;

  }else if (argc < 4 || argc > 5){
    fprintf(stderr, "Improper use of flags\nUsage: %s [-c | -s | -i]  <source file> [<destination file> | -d]\nRead SYNTAX.md for vaild options\n", argv[0]);
    return EXIT_FAILURE;
  }

  /*Flag parse*/
  int opt;
  int mode = 0; /*1 = C-gen, 2 = stakc-gen, 3 = interpreter*/
  int numOfFlags = 0; /*keep track of how many vaild flags are passed*/
  int dry = 0; /*Will this be a dry run?*/

  static struct option longOptions[] = {
    {"c-gen", no_argument, 0, 'c' },
    {"stack-gen", no_argument, 0, 's'},
    {"interpreter", no_argument, 0, 'i'},
    {"dry", no_argument, 0, 'd'},
    {0, 0, 0, 0}
    };

    while ((opt = getopt_long (argc, argv, "csid", longOptions, NULL)) != -1){
      switch(opt){
        case 'c':
          mode = 1;
          ++numOfFlags;
          break;
        case 's':
          mode = 2;
          ++numOfFlags;
          break;
      case 'i':
          mode = 3;
          ++numOfFlags;
          break;
      case 'd':
        dry = 1;
        break;
      default: /*unknown flag*/
        return EXIT_FAILURE;
    }
  }

  /*Make sure only one vaild flag is given*/
  if(numOfFlags > 1){
    fprintf(stderr, "Too many flags passed\nUsage: %s [-c | -s | -i]  <source file> [<destination file> | -d]\nRead SYNTAX.md for vaild options\n", argv[0]);
    return EXIT_FAILURE;
  }  

  /* Open the file */
  FILE *sourcefptr;
  sourcefptr = fopen(argv[optind], "r");
  if (!sourcefptr) {
    fprintf(stderr,"./mac: Failed to open source file\n");
    return EXIT_FAILURE; ;
  }

  /*Create destination files*/
  FILE *destinationfptr;
  if (dry == 1 ){
    destinationfptr = stdout; 
  }else {
    destinationfptr = fopen(argv[++optind], "w");
    if (!sourcefptr) {
    fprintf(stderr,"./mac: Failed to open destination file\n");
    return EXIT_FAILURE;
    }
  }

  /*Make the AST*/
  AST_node *icode;
  if(!parseProgram(&icode, sourcefptr)){
    fprintf(stderr, "./mac: No valid expression found at the start of the input.\n");
    return EXIT_FAILURE;
  }
  fclose(sourcefptr);

  /*Code gen*/
  if(mode == 1){
    /*Call the function, if there is error exit program, else the function will execute*/
    if(cCodeGen(icode, destinationfptr) == EXIT_FAILURE){
      return EXIT_FAILURE;
    };
  }else if(mode == 2){
    if(stackMachineCodeGen(icode, destinationfptr) == EXIT_FAILURE){
      return EXIT_FAILURE;
    };
  }else{
    if(interpreter(icode,  destinationfptr) == EXIT_FAILURE){
      return EXIT_FAILURE;
    };
  }

  
  fclose(destinationfptr);

  return SUCCESS;
}
