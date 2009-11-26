
#ifndef IDENTIFIERHANDLER_H
#define IDENTIFIERHANDLER_H

#include "handlerbase.h"

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

    // ASSIGNMENT
    virtual bool actionStatementState0();

    // CALL
    virtual bool actionStatementState16();

    // INPUT
    virtual bool actionStatementState18();

    // NUMERICAL VALUE
    virtual bool actionFactorState0();

    // VALUE
    virtual bool actionFactorState4();

  private:
    IdentifierManager *mManager;
};

#endif
