
#include "codegenerationhandler.h"

#include "codewriter.h"
#include "identifiermanager.h"

CodeGenerationHandler::CodeGenerationHandler( IdentifierManager *manager, CodeWriter *writer )
  : mManager( manager ), mWriter( writer )
{
}

// END_OF_PROGRAM
bool CodeGenerationHandler::actionProgramState1()
{
  return true;
}

// END_OF_PROCEDURE
bool CodeGenerationHandler::actionBlockState18()
{
  return true;
}

// BEGIN_OF_STATEMENTS
bool CodeGenerationHandler::actionBlockState20()
{
  return true;
}

// IDENTIFIER
bool CodeGenerationHandler::actionStatementState0()
{
  return true;
}

// EXPRESSION
bool CodeGenerationHandler::actionStatementState2()
{
  return true;
}

// CONDITION
bool CodeGenerationHandler::actionStatementState4()
{
  return true;
}

// STATEMENT
bool CodeGenerationHandler::actionStatementState6()
{
  return true;
}

// WHILE
bool CodeGenerationHandler::actionStatementState7()
{
  return true;
}

// CONDITION
bool CodeGenerationHandler::actionStatementState8()
{
  return true;
}

// STATEMENT
bool CodeGenerationHandler::actionStatementState10()
{
  return true;
}

// CALL IDENTIFIER
bool CodeGenerationHandler::actionStatementState16()
{
  const int procedureIndex = mManager->procedureIndex( currentToken().identifierValue() );
  mWriter->writeOperation( CodeWriter::Call, procedureIndex );

  return true;
}

// INPUT IDENTIFIER
bool CodeGenerationHandler::actionStatementState18()
{
  return true;
}

// OUTPUT IDENTIFIER
bool CodeGenerationHandler::actionStatementState20()
{
  return true;
}

// MINUS
bool CodeGenerationHandler::actionExpressionState0()
{
  return true;
}

// FIRST TERM
bool CodeGenerationHandler::actionExpressionState2()
{
  return true;
}

// ADD TERM
bool CodeGenerationHandler::actionExpressionState6()
{
  return true;
}

// SUB TERM
bool CodeGenerationHandler::actionExpressionState7()
{
  return true;
}

// MUL FACTOR
bool CodeGenerationHandler::actionTermState2()
{
  return true;
}

// DIV FACTOR
bool CodeGenerationHandler::actionTermState4()
{
  return true;
}

// PUSH NUMERIC
bool CodeGenerationHandler::actionFactorState0()
{
  return true;
}

// PUSH IDENTIFIER
bool CodeGenerationHandler::actionFactorState4()
{
  return true;
}

// ODD EXPRESSION
bool CodeGenerationHandler::actionConditionState1()
{
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState3()
{
  return true;
}

// COMP EXPRESSION
bool CodeGenerationHandler::actionConditionState4()
{
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState5()
{
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState6()
{
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState7()
{
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState8()
{
  return true;
}

