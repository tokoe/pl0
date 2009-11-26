
#ifndef HANDLERBASE_H
#define HANDLERBASE_H

#include "token.h"

class HandlerBase
{
  public:
    enum ActionType
    {
      ActionProgramState0,
      ActionProgramState1,
      ActionProgramState2,
     
      ActionBlockState0,
      ActionBlockState1,
      ActionBlockState2,
      ActionBlockState3,
      ActionBlockState4,
      ActionBlockState5,
      ActionBlockState6,
      ActionBlockState7,
      ActionBlockState8,
      ActionBlockState9,
      ActionBlockState10,
      ActionBlockState11,
      ActionBlockState12,
      ActionBlockState13,
      ActionBlockState14,
      ActionBlockState15,
      ActionBlockState16,
      ActionBlockState17,
      ActionBlockState18,
      ActionBlockState19,
      ActionBlockState20,
      ActionBlockState21,
      ActionBlockState22,

      ActionStatementState0,
      ActionStatementState1,
      ActionStatementState2,
      ActionStatementState3,
      ActionStatementState4,
      ActionStatementState5,
      ActionStatementState6,
      ActionStatementState7,
      ActionStatementState8,
      ActionStatementState9,
      ActionStatementState10,
      ActionStatementState11,
      ActionStatementState12,
      ActionStatementState13,
      ActionStatementState14,
      ActionStatementState15,
      ActionStatementState16,
      ActionStatementState17,
      ActionStatementState18,
      ActionStatementState19,
      ActionStatementState20,
      ActionStatementState21,
      ActionStatementState22,

      ActionExpressionState0,
      ActionExpressionState1,
      ActionExpressionState2,
      ActionExpressionState3,
      ActionExpressionState4,
      ActionExpressionState5,
      ActionExpressionState6,
      ActionExpressionState7,
      ActionExpressionState8,

      ActionTermState0,
      ActionTermState1,
      ActionTermState2,
      ActionTermState3,
      ActionTermState4,
      ActionTermState5,
      ActionTermState6,

      ActionFactorState0,
      ActionFactorState1,
      ActionFactorState2,
      ActionFactorState3,
      ActionFactorState4,
      ActionFactorState5,

      ActionConditionState0,
      ActionConditionState1,
      ActionConditionState2,
      ActionConditionState3,
      ActionConditionState4,
      ActionConditionState5,
      ActionConditionState6,
      ActionConditionState7,
      ActionConditionState8,
      ActionConditionState9,
      ActionConditionState10,
    };

    HandlerBase();

    void setCurrentToken( const Token &token );
    Token currentToken() const;

    QString errorText() const;

    bool executeAction( ActionType type );

  protected:
    void setErrorText( const QString &text );

    virtual bool actionProgramState0();
    virtual bool actionProgramState1();
    virtual bool actionProgramState2();

    virtual bool actionBlockState0();
    virtual bool actionBlockState1();
    virtual bool actionBlockState2();
    virtual bool actionBlockState3();
    virtual bool actionBlockState4();
    virtual bool actionBlockState5();
    virtual bool actionBlockState6();
    virtual bool actionBlockState7();
    virtual bool actionBlockState8();
    virtual bool actionBlockState9();
    virtual bool actionBlockState10();
    virtual bool actionBlockState11();
    virtual bool actionBlockState12();
    virtual bool actionBlockState13();
    virtual bool actionBlockState14();
    virtual bool actionBlockState15();
    virtual bool actionBlockState16();
    virtual bool actionBlockState17();
    virtual bool actionBlockState18();
    virtual bool actionBlockState19();
    virtual bool actionBlockState20();
    virtual bool actionBlockState21();
    virtual bool actionBlockState22();

    virtual bool actionStatementState0();
    virtual bool actionStatementState1();
    virtual bool actionStatementState2();
    virtual bool actionStatementState3();
    virtual bool actionStatementState4();
    virtual bool actionStatementState5();
    virtual bool actionStatementState6();
    virtual bool actionStatementState7();
    virtual bool actionStatementState8();
    virtual bool actionStatementState9();
    virtual bool actionStatementState10();
    virtual bool actionStatementState11();
    virtual bool actionStatementState12();
    virtual bool actionStatementState13();
    virtual bool actionStatementState14();
    virtual bool actionStatementState15();
    virtual bool actionStatementState16();
    virtual bool actionStatementState17();
    virtual bool actionStatementState18();
    virtual bool actionStatementState19();
    virtual bool actionStatementState20();
    virtual bool actionStatementState21();
    virtual bool actionStatementState22();

    virtual bool actionExpressionState0();
    virtual bool actionExpressionState1();
    virtual bool actionExpressionState2();
    virtual bool actionExpressionState3();
    virtual bool actionExpressionState4();
    virtual bool actionExpressionState5();
    virtual bool actionExpressionState6();
    virtual bool actionExpressionState7();
    virtual bool actionExpressionState8();

    virtual bool actionTermState0();
    virtual bool actionTermState1();
    virtual bool actionTermState2();
    virtual bool actionTermState3();
    virtual bool actionTermState4();
    virtual bool actionTermState5();
    virtual bool actionTermState6();

    virtual bool actionFactorState0();
    virtual bool actionFactorState1();
    virtual bool actionFactorState2();
    virtual bool actionFactorState3();
    virtual bool actionFactorState4();
    virtual bool actionFactorState5();

    virtual bool actionConditionState0();
    virtual bool actionConditionState1();
    virtual bool actionConditionState2();
    virtual bool actionConditionState3();
    virtual bool actionConditionState4();
    virtual bool actionConditionState5();
    virtual bool actionConditionState6();
    virtual bool actionConditionState7();
    virtual bool actionConditionState8();
    virtual bool actionConditionState9();
    virtual bool actionConditionState10();

  private:
    Token mCurrentToken;    
    QString mErrorText;
};

#endif
