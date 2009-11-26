
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
  mTermIsNegative = true;
  return true;
}

// NON_MINUS
bool CodeGenerationHandler::actionExpressionState1()
{
  mTermIsNegative = false;
  return true;
}

// FIRST TERM
bool CodeGenerationHandler::actionExpressionState2()
{
  if ( mTermIsNegative )
    mWriter->writeOperation( CodeWriter::SignedMinus );

  return true;
}

// ADD TERM
bool CodeGenerationHandler::actionExpressionState6()
{
  mWriter->writeOperation( CodeWriter::Add );
  return true;
}

// SUB TERM
bool CodeGenerationHandler::actionExpressionState7()
{
  mWriter->writeOperation( CodeWriter::Sub );
  return true;
}

// MUL FACTOR
bool CodeGenerationHandler::actionTermState2()
{
  mWriter->writeOperation( CodeWriter::Mul );
  return true;
}

// DIV FACTOR
bool CodeGenerationHandler::actionTermState4()
{
  mWriter->writeOperation( CodeWriter::Div );
  return true;
}

// PUSH NUMERIC
bool CodeGenerationHandler::actionFactorState0()
{
  mWriter->writeOperation( CodeWriter::PutConst, mManager->constIndex( currentToken().numericValue() ) );
  return true;
}

// PUSH IDENTIFIER
bool CodeGenerationHandler::actionFactorState4()
{
  const QString name = currentToken().identifierValue();

  if ( mManager->hasConstIdentifier( name ) ) {
    mWriter->writeOperation( CodeWriter::PutConst, mManager->constIndex( name ) );
  } else {
    IdentifierManager::VariableType type;
    int variableAddress;
    int procedureIndex;
    mManager->getVariableAddress( name, type, variableAddress, procedureIndex );
    switch ( type ) {
      case IdentifierManager::Local:
        mWriter->writeOperation( CodeWriter::PutAddressVariableLocal, variableAddress );
        break;
      case IdentifierManager::Main:
        mWriter->writeOperation( CodeWriter::PutAddressVariableMain, variableAddress );
        break;
      case IdentifierManager::Global:
        mWriter->writeOperation( CodeWriter::PutAddressVariableGlobal, variableAddress, procedureIndex );
        break;
    }
  }
  return true;
}

// ODD EXPRESSION
bool CodeGenerationHandler::actionConditionState1()
{
  mWriter->writeOperation( CodeWriter::Odd );
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState3()
{
  mComparisonSymbol = Token::EqualsSymbol;
  return true;
}

// COMP EXPRESSION
bool CodeGenerationHandler::actionConditionState4()
{
  switch( mComparisonSymbol ) {
    case Token::EqualsSymbol: mWriter->writeOperation( CodeWriter::CompareEqual ); break;
    case Token::UnequalSymbol: mWriter->writeOperation( CodeWriter::CompareNotEqual ); break;
    case Token::LessThanSymbol: mWriter->writeOperation( CodeWriter::CompareLessThan ); break;
    case Token::GreaterThanSymbol: mWriter->writeOperation( CodeWriter::CompareGreaterThan ); break;
    case Token::LessThanEqualSymbol: mWriter->writeOperation( CodeWriter::CompareLessThanEqual ); break;
    case Token::GreaterThanEqualSymbol: mWriter->writeOperation( CodeWriter::CompareGreaterThanEqual ); break;
  }

  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState5()
{
  mComparisonSymbol = Token::UnequalSymbol;
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState6()
{
  mComparisonSymbol = Token::LessThanSymbol;
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState7()
{
  mComparisonSymbol = Token::LessThanEqualSymbol;
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState8()
{
  mComparisonSymbol = Token::GreaterThanSymbol;
  return true;
}

// COMP IDENTIFIER
bool CodeGenerationHandler::actionConditionState9()
{
  mComparisonSymbol = Token::GreaterThanEqualSymbol;
  return true;
}

