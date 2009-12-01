
#ifndef CODEGENERATIONHANDLER_H
#define CODEGENERATIONHANDLER_H

#include "handlerbase.h"

class CodeWriter;
class IdentifierManager;

class CodeGenerationHandler : public HandlerBase
{
  public:
    CodeGenerationHandler( IdentifierManager *manager, CodeWriter *writer );

  protected:
    // END_OF_PROGRAM
    virtual bool actionProgramState1();

    // END_OF_PROCEDURE
    virtual bool actionBlockState18();
    // BEGIN_OF_STATEMENTS
    virtual bool actionBlockState20();

    // IDENTIFIER
    virtual bool actionStatementState0();
    // EXPRESSION
    virtual bool actionStatementState2();
    // CONDITION
    virtual bool actionStatementState4();
    // STATEMENT
    virtual bool actionStatementState6();
    // WHILE
    virtual bool actionStatementState7();
    // CONDITION
    virtual bool actionStatementState8();
    // STATEMENT
    virtual bool actionStatementState10();
    // CALL IDENTIFIER
    virtual bool actionStatementState16();
    // INPUT IDENTIFIER
    virtual bool actionStatementState18();
    // OUTPUT EXPRESSION
    virtual bool actionStatementState20();

    // MINUS
    virtual bool actionExpressionState0();
    // NON_MINUS
    virtual bool actionExpressionState1();
    // FIRST TERM
    virtual bool actionExpressionState2();
    // ADD TERM
    virtual bool actionExpressionState6();
    // SUB TERM
    virtual bool actionExpressionState7();

    // MUL FACTOR
    virtual bool actionTermState3();
    // DIV FACTOR
    virtual bool actionTermState5();

    // PUSH NUMERIC
    virtual bool actionFactorState0();
    // PUSH IDENTIFIER
    virtual bool actionFactorState4();

    // ODD EXPRESSION
    virtual bool actionConditionState1();
    // COMP IDENTIFIER
    virtual bool actionConditionState3();
    // COMP EXPRESSION
    virtual bool actionConditionState4();
    // COMP IDENTIFIER
    virtual bool actionConditionState5();
    // COMP IDENTIFIER
    virtual bool actionConditionState6();
    // COMP IDENTIFIER
    virtual bool actionConditionState7();
    // COMP IDENTIFIER
    virtual bool actionConditionState8();
    // COMP IDENTIFIER
    virtual bool actionConditionState9();

  private:
    IdentifierManager *mManager;
    CodeWriter *mWriter;
    bool mTermIsNegative;
    Token::SymbolType mComparisonSymbol;
};

#endif
