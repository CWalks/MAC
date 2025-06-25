/* MAC 
 * Caleb Walker
 * 11/05/2025
 * Parser
 */

#include "parser.h"
#include "lex.h"
#include "error.h"

#define SUCCESS 1
#define FAILURE 0


/**
 * @brief Creating and returning a new dynamically allocated Expression
 * @Return: a new Expression strut
 */
static Expression *newExpression(void){
  Expression* newExp = (Expression *) malloc(sizeof(Expression));
  if (newExp == NULL){
    error("Failed to create new expression; Not enough memory");
  }
  return newExp;
}

/**
 * @brief Free expression
 */
static void freeExpression(Expression *expr){free((void *)expr);}

/**
 * @brief Checks if oper is an operator ('+' or '*')
 * @Return: 1 if the oper is classifid as a operator, otherwise return 0
 */
static int parseOperator(Operator *oper, FILE *fp){
  if(Token.class == '+'){
    *oper = '+';
    getNextToken(fp);
    return SUCCESS; 
  }
  if(Token.class == '*'){
    *oper = '*';
    getNextToken(fp);
    return SUCCESS;
  }
  return FAILURE; /*Failed to get operator*/
}

/**
 * @brief Builds an AST from a given Expression
 * @param expr_P: a double pointer to a expression that will start as the root of the AST
 * @Return: 1 if successful otherwise return 0 
 *
 * @note If an error is found it will stop the program and broadcast
 * an error message
 */
static int parseExpression(Expression **expr_p, FILE *fp){

  /* Just for convenience */
  *expr_p = newExpression();
  Expression *expr = *expr_p;

  /* Try to parse a digit
   * If the current token is a digit, it's a leaf node. 
   * Sets the type, stores the value, and returns success
   */
  if(Token.class == DIGIT){
    expr->type = 'D';
    expr->value = Token.repr;
    getNextToken(fp);
    return SUCCESS;
  }
/* Try to parse a parenthesized expression
 * we expect an expression, an operator, 
 * and another expression.
 */
  if(Token.class == '('){
    expr->type = 'P';
    getNextToken(fp);
    if(!parseExpression(&expr->left, fp)){
      /*error missing expression*/
      error("Missing expression; You are missing the left expression within your brackets");
    }
    if(!parseOperator(&expr->oper, fp)){
      /*error missing operator*/
      error("Missing operator; You are missing an operator within your brackets");
    }
    if(!parseExpression(&expr->right, fp)){
      /*Error missing expression*/
      error("Missing expression; You are missing the right expression within your brackets");
    }
    if(Token.class != ')'){
      /*error missing bracket )*/
      error("Missing end bracket; remember to match your brackets! ");
    }
    getNextToken(fp);
    return SUCCESS;

  }
  /*Failed on both attemps*/
  freeExpression(expr);
  return FAILURE;
}

/**
 * @brief Parses the input and builds the abstract syntax tree (AST).
 * Acts as the starting point for the lexical analyzer. If parsing is successful, 
 * the resulting expression tree is stored in the location pointed to by icode_p.
 *
 * @param icode_P A double pointer AST_node* where the resulting AST will be stored.
 * This will be the root of the tree
 *
 * @param fp a FILE pointer that will be the file to read from
 *
 * @return int return 1 if successful otherwise 0 for failure
 * */
int parseProgram(AST_node **icode_p, FILE *fp){

  /*Check fp*/
  if (!fp) {
        error("parse: NULL file pointer\n"); 
    }

  Expression *expr;

  /*Start the lexical analyzer*/
  getNextToken(fp);
  if(parseExpression(&expr, fp)){
    /*After parsing, if there isnt an EOF at the end, the program does not end with ')'*/
    if(Token.class != EOF){
     
      switch (Token.class) {
        case '*':
          error("Expressions must be wrapped in parentheses");
          break; /*Not needed because error exits the program but this stops from compiler complaining*/
        case '+':
          error("Expressions must be wrapped in parentheses");
        case DIGIT:
          error("Space between digits");
          break;
    
        default : error("Garbage after end of program");

      }
    }
    /* Assign the AST to icode_P (by letting icode_p equal the root of the AST)*/
    *icode_p = expr;
    return SUCCESS;
  }
return FAILURE;
}

