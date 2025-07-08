/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
#include "parser.h"
#include "backend.h"

/*For getopt_long*/
#include <getopt.h>

int main(int argc, char *argv[]){
 
  /* If there are too many flags */
  if(argc > 3 || argc < 2){
    fprintf(stderr, "Usage: %s [-c | -s | -i]  <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  /*Flag parse*/
  int opt;
  int mode = 0; /*1 = C-gen, 2 = stakc-gen, 3 = interpreter*/
  int numOfFlags = 0; /*keep track of how many vaild flags are passed*/

  static struct option longOptions[] = {
    {"c-gen", no_argument, 0, 'c' },
    {"stack-gen", no_argument, 0, 's'},
    {"interpreter", no_argument, 0, 'i'},
    {0, 0, 0, 0}
    };

    while ((opt = getopt_long (argc, argv, "csi", longOptions, NULL)) != -1){
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
      default: /*unknown flag*/
        return EXIT_FAILURE;
    }
  }

  /*Make sure only one vail flag is given*/
  if(numOfFlags > 1){
    fprintf(stderr, "Too many flags passed\nUsage: %s [-c | -s | -i]  <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }  

  /* Open the file */
  FILE *fptr;
  fptr = fopen(argv[optind], "r");
  if (!fptr) {
    perror("./mac: Failed to open File");
    
    return EXIT_FAILURE; ;
  }

  /*Make the AST*/
  AST_node *icode;
  if(!parseProgram(&icode, fptr)){
    fprintf(stderr, "Error: No valid expression found at the start of your input.\n");
    return EXIT_FAILURE;
  }
  fclose(fptr);

  /*Code gen*/
  if(mode == 1){
    /*Call the function, if there is error exit program, else the function will execute*/
    if(cCodeGen(icode) == EXIT_FAILURE){
      return EXIT_FAILURE;
    };
  }else if(mode == 2){
    if(stackMachineCodeGen(icode) == EXIT_FAILURE){
      return EXIT_FAILURE;
    };
  }else{
    if(interpreter(icode) == EXIT_FAILURE){
      return EXIT_FAILURE;
    };
  }

  return SUCCESS;
}
