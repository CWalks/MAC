/* MAC 
 * Caleb Walker
 * 11/05/2025
 * Parser
 */

#include "parser.h"
#include "error.h"

/*Creating and returning a new dynamically allocated Expression*/
static Expression *newExpression(void){
  return (Expression *)malloc(sizeof(Expression));
}

/*Free the expression*/
static void freeExpression(Expression *expr){free((void *)expr);}

/*If the current token is an operator ('+' or '-')
 * retrun 1 for success
 */
static int parseOperator(Operator *oper){
  if(Token.class == '+'){
    *oper = '+';
    getNextToken();
    return 1; 
  }
  if(Token.class == '*'){
    *oper = '*';
    getNextToken();
    return 1;
  }
  return 0; /*Failed to get operatior*/
}

static int parseExpresion(Expression **expr_p){

  *expr_p = newExpression();
  Expression *expr = *expr_p;

  /*Try to parse a digit*/
  if(Token.class == DIGIT){
    expr->type = 'D';
    expr->value = Token.repr - '0';
    getNextToken();
    return 1;
  }
/*Try to parse a parenthesized expression*/
  if(Token.class == '('){
    expr->type = 'p';
    getNextToken();
    if(!parseExpresion(&expr->left)){
      /*error missing expression*/
      error("Missing expression");
    }
    if(!parseOperator(&expr->oper)){
      /*error missing operator*/
      error("Missing operator");
    }
    if(!parseExpresion(&expr->right)){
      /*Error missing expression*/
      error("Missing expression");
    }
    if(Token.class != ')'){
      /*error missing bracket )*/
      error("Missing end bracket");
    }
    getNextToken();
    return 1;

  }
  /*Failed on both attemps*/
  freeExpression(expr);
  return 0;
}

int parseProgram(ASTNode **icode_p){
  Expression *expr;

  /*Start the lexical analyzer*/
  getNextToken();
  if(parseExpresion(&expr)){
    if(Token.class != EOF){
      error("Garbage after end of program");
    }
    *icode_p = expr;
    return 1;
  }
return 0;
}

/*Add in error and test.
 * test curChar and curLine*/
