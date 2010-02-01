
#ifndef IDENTIFIERHANDLER_H
#define IDENTIFIERHANDLER_H

#include "handlerbase.h"

#include <QtCore/QStringList>

class IdentifierManager;

class IdentifierHandler : public HandlerBase
{
  public:
    IdentifierHandler( IdentifierManager *manager );

  protected:
    // CONST declaration
    virtual bool actionBlockState1();
    virtual bool actionBlockState3();

    // VAR declaration
    virtual bool actionBlockState9();

    // PROC begin
    virtual bool actionBlockState15();
    // PROC end
    virtual bool actionBlockState18();

    // PROCEDURE OPEN BRACKET
    virtual bool actionBlockState23();
    // PROCEDURE PARAM IDENTIFIER
    virtual bool actionBlockState24();
    // PROCEDURE CLOSE BRACKET
    virtual bool actionBlockState26();

    // ASSIGNMENT
    virtual bool actionStatementState0();

    // CALL
    virtual bool actionStatementState16();

    // INPUT
    virtual bool actionStatementState18();

    // CALL WITH PARAMS EXPRESSION
    virtual bool actionStatementState24();
    // CALL WITH PARAMS CLOSING BRACKET
    virtual bool actionStatementState26();

    // NUMERICAL VALUE
    virtual bool actionFactorState0();

    // VALUE
    virtual bool actionFactorState4();

  private:
    QStringList mProcedureParameters;
    int mProcedureParameterCount;
    QString mProcedureToCall;
    int mCallProcedureParameterCount;
    IdentifierManager *mManager;
};

#endif
