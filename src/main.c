/*MAC 
 * Caleb Walker
 * 04/05/2025
 * Main 
 */
  
/*Get ride of this with printTree*/
#include "lex.h"

#include "error.h"
#include "parser.h"
#include "backend.h"

#include <getopt.h>


void printTree(Expression *expr, int depth) {
  if (!expr) return;

  for (int i = 0; i < depth; i++) printf("  "); // Indent

  if (expr->type == 'D') {
    printf("Digit: %d\n", expr->value);
  } else if (expr->type == 'p') {
    printf("Operator: %c\n", expr->oper);
    printTree(expr->left, depth + 1);
    printTree(expr->right, depth + 1);
  }
}

int main(int argc, char *argv[]){
 
  /* If there are too many flags */
  if(argc > 3){
    fprintf(stderr, "Usage: %s [-c | -s | -i]  <filename>\nFor fully list of flags read SYNTAX.md\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  /*Flag parse*/
  int opt;
  int mode = 0; /*1 = C-gen, 2 = stakc-gen, 3 = interpreter*/
  int numOfFlags = 0; /*keep track of how many vaild flags are passed*/

  static struct option longOptions[] = {
    {"C-gen", no_argument, 0, 'c' },
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
    perror("Failed to open File");
    
    return EXIT_FAILURE; ;
  }

  /*Make the AST*/
  AST_node *icode;
  if(!parseProgram(&icode, fptr)){
    fprintf(stderr, "Error: No valid expression found at the start of your input.\n");
    fclose(fptr);
    return EXIT_FAILURE;
  }
  fclose(fptr);

  /*Code gen*/
  if(mode == 1){
    printf("Code gen\n");
  }else if(mode == 2){
    stackMachineCodeGen(icode);
  }else{
    printf("interpreter\n");
  }

  return 0;
}
