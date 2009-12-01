
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
  mWriter->writeOperation( CodeWriter::ReturnProc );

  const qint64 currentPosition = mWriter->currentPosition();
  const qint64 procedureBeginPosition = mWriter->popLabel();
  const qint64 codeSize = currentPosition - procedureBeginPosition;

  mWriter->writeOperationAtPosition( procedureBeginPosition, CodeWriter::EntryProc, codeSize );

  mWriter->writeAtPosition( 0, mManager->procedureCount() );

  const QList<int> constIdentifierValues = mManager->constIdentifierValues();
  for ( int i = 0; i < constIdentifierValues.count(); ++i ) {
    mWriter->write( constIdentifierValues.at( i ) );
    //FIXME: writing int?!?
    mWriter->write( 0 );
  }

  return true;
}

// END_OF_PROCEDURE
bool CodeGenerationHandler::actionBlockState18()
{
  mWriter->writeOperation( CodeWriter::ReturnProc );

  const qint64 currentPosition = mWriter->currentPosition();
  const qint64 procedureBeginPosition = mWriter->popLabel();
  const qint64 codeSize = currentPosition - procedureBeginPosition;

  mWriter->writeOperationAtPosition( procedureBeginPosition, CodeWriter::EntryProc, codeSize );

  return true;
}

// BEGIN_OF_STATEMENTS
bool CodeGenerationHandler::actionBlockState20()
{
  mWriter->pushLabel( mWriter->currentPosition() );
  mWriter->writeOperation( CodeWriter::EntryProc, 0, mManager->currentProcedureIndex(), mManager->currentProcedureVariableSize() );

  return true;
}

// IDENTIFIER
bool CodeGenerationHandler::actionStatementState0()
{
  const QString name = currentToken().identifierValue();

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

  return true;
}

// EXPRESSION
bool CodeGenerationHandler::actionStatementState2()
{
  mWriter->writeOperation( CodeWriter::StoreValue );
  return true;
}

// CONDITION
bool CodeGenerationHandler::actionStatementState4()
{
  mWriter->pushLabel( mWriter->currentPosition() );
  mWriter->writeOperation( CodeWriter::JumpNot, 0 );

  return true;
}

// STATEMENT
bool CodeGenerationHandler::actionStatementState6()
{
  const qint64 currentPosition = mWriter->currentPosition();
  const qint64 jumpNotPosition = mWriter->popLabel();
  const qint64 jumpOffset = currentPosition - jumpNotPosition - 3;

  mWriter->writeOperationAtPosition( jumpNotPosition, CodeWriter::JumpNot, jumpOffset );

  return true;
}

// WHILE
bool CodeGenerationHandler::actionStatementState7()
{
  // push while label
  mWriter->pushLabel( mWriter->currentPosition() );

  return true;
}

// CONDITION
bool CodeGenerationHandler::actionStatementState8()
{
  // push jump not label
  mWriter->pushLabel( mWriter->currentPosition() );
  mWriter->writeOperation( CodeWriter::JumpNot, 0 );

  return true;
}

// STATEMENT
bool CodeGenerationHandler::actionStatementState10()
{
  qint64 currentPosition = mWriter->currentPosition();
  const qint64 jumpNotPosition = mWriter->popLabel();
  const qint64 jumpOffset = currentPosition - jumpNotPosition;

  mWriter->writeOperationAtPosition( jumpNotPosition, CodeWriter::JumpNot, jumpOffset );
 
  currentPosition = mWriter->currentPosition();
  const qint64 whileLabelPosition = mWriter->popLabel();
  const qint64 jumpBackOffset = -(currentPosition - whileLabelPosition + 3);

  mWriter->writeOperation( CodeWriter::Jump, jumpBackOffset );

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
  const QString name = currentToken().identifierValue();

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

  mWriter->writeOperation( CodeWriter::GetValue );
  return true;
}

// OUTPUT EXPRESSION
bool CodeGenerationHandler::actionStatementState20()
{
  mWriter->writeOperation( CodeWriter::PutValue );
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
bool CodeGenerationHandler::actionTermState3()
{
  mWriter->writeOperation( CodeWriter::Mul );
  return true;
}

// DIV FACTOR
bool CodeGenerationHandler::actionTermState5()
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
        mWriter->writeOperation( CodeWriter::PutValueVariableLocal, variableAddress );
        break;
      case IdentifierManager::Main:
        mWriter->writeOperation( CodeWriter::PutValueVariableMain, variableAddress );
        break;
      case IdentifierManager::Global:
        mWriter->writeOperation( CodeWriter::PutValueVariableGlobal, variableAddress, procedureIndex );
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
    default: break;
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

