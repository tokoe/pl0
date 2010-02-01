
#include "identifierhandler.h"

#include "identifiermanager.h"

IdentifierHandler::IdentifierHandler( IdentifierManager *manager )
  : mManager( manager )
{
}

bool IdentifierHandler::actionBlockState1()
{
  const QString name = currentToken().identifierValue();

  if ( mManager->hasLocalVariableIdentifier( name ) ||
       mManager->hasLocalConstIdentifier( name ) ) {
    setErrorText( QString( "Redeclaration of identifier %1 in this scope" ).arg( name ) );
    return false;
  }

  mManager->setName( name );

  return true;
}

bool IdentifierHandler::actionBlockState3()
{
  mManager->setValue( currentToken().numericValue() );
  mManager->pushConstIdentifier();

  return true;
}

bool IdentifierHandler::actionBlockState9()
{
  const QString name = currentToken().identifierValue();

  if ( mManager->hasLocalVariableIdentifier( name ) ||
       mManager->hasLocalConstIdentifier( name ) ) {
    setErrorText( QString( "Redeclaration of identifier %1 in this scope" ).arg( name ) );
    return false;
  }

  mManager->setName( name );
  mManager->pushVariableIdentifier();

  return true;
}

bool IdentifierHandler::actionBlockState15()
{
  const QString name = currentToken().identifierValue();

  if ( mManager->hasLocalProcedureIdentifier( name ) ) {
    setErrorText( QString( "Redeclaration of procedure %1 in this scope" ).arg( name ) );
    return false;
  }

  mManager->setName( name );
  mManager->pushProcedure();

  return true;
}

bool IdentifierHandler::actionBlockState18()
{
  mManager->endProcedure();
  return true;
}

bool IdentifierHandler::actionBlockState23()
{
  mProcedureParameters.clear();

  return true;
}

bool IdentifierHandler::actionBlockState24()
{
  mProcedureParameters.append( currentToken().identifierValue() );

  return true;
}

bool IdentifierHandler::actionBlockState26()
{
  for ( int i = mProcedureParameters.count() - 1; i >= 0; --i ) {
    mManager->setName( mProcedureParameters.at( i ) );
    mManager->pushParameterIdentifier();
  }

  return true;
}

bool IdentifierHandler::actionStatementState0()
{
  if ( !mManager->hasVariableIdentifier( currentToken().identifierValue() ) ) {
    setErrorText( QString( "Variable %1 is undeclared in this scope" ).arg( currentToken().identifierValue() ) );
    return false;
  }

  return true;
}

bool IdentifierHandler::actionStatementState16()
{
  if ( !mManager->hasProcedureIdentifier( currentToken().identifierValue() ) ) {
    setErrorText( QString( "Procedure %1 is undeclared in this scope" ).arg( currentToken().identifierValue() ) );
    return false;
  }

  mProcedureToCall = currentToken().identifierValue();
  mCallProcedureParameterCount = 0;

  return true;
}

bool IdentifierHandler::actionStatementState18()
{
  if ( !mManager->hasVariableIdentifier( currentToken().identifierValue() ) ) {
    setErrorText( QString( "Variable %1 is undeclared in this scope" ).arg( currentToken().identifierValue() ) );
    return false;
  }

  return true;
}

bool IdentifierHandler::actionStatementState24()
{
  mCallProcedureParameterCount++;

  return true;
}

bool IdentifierHandler::actionStatementState26()
{
  const int parameterCount = mManager->procedureParameterCount( mProcedureToCall );
  if ( mCallProcedureParameterCount != parameterCount ) {
    setErrorText( QString( "Procedure %1 expected %2 parameters but got %3" ).arg( mProcedureToCall )
                                                                             .arg( parameterCount ).arg( mCallProcedureParameterCount ) );
    return false;
  }

  return true;
}

bool IdentifierHandler::actionFactorState0()
{
  // push the numeric literal as anonymous const identifier
  mManager->setName( QString() );
  mManager->setValue( currentToken().numericValue() );
  mManager->pushConstIdentifier();

  return true;
}

bool IdentifierHandler::actionFactorState4()
{
  if ( !mManager->hasVariableIdentifier( currentToken().identifierValue() ) &&
       !mManager->hasConstIdentifier( currentToken().identifierValue() ) ) {
    setErrorText( QString( "Variable/constant %1 is undeclared in this scope" ).arg( currentToken().identifierValue() ) );
    return false;
  }

  return true;
}

