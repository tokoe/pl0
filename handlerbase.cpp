
#include "handlerbase.h"

HandlerBase::HandlerBase()
{
}

void HandlerBase::setCurrentToken( const Token &token )
{
  mCurrentToken = token;
}

Token HandlerBase::currentToken() const
{
  return mCurrentToken;
}

void HandlerBase::setErrorText( const QString &text )
{
  mErrorText = QString( "[%1:%2] %3" ).arg( mCurrentToken.row() )
                                      .arg( mCurrentToken.column() )
                                      .arg( text );
}

QString HandlerBase::errorText() const
{
  return mErrorText;
}

bool HandlerBase::executeAction( ActionType type )
{
  switch ( type ) {
    case ActionProgramState0: return actionProgramState0(); break;
    case ActionProgramState1: return actionProgramState1(); break;
    case ActionProgramState2: return actionProgramState2(); break;
    case ActionBlockState0: return actionBlockState0(); break;
    case ActionBlockState1: return actionBlockState1(); break;
    case ActionBlockState2: return actionBlockState2(); break;
    case ActionBlockState3: return actionBlockState3(); break;
    case ActionBlockState4: return actionBlockState4(); break;
    case ActionBlockState5: return actionBlockState5(); break;
    case ActionBlockState6: return actionBlockState6(); break;
    case ActionBlockState7: return actionBlockState7(); break;
    case ActionBlockState8: return actionBlockState8(); break;
    case ActionBlockState9: return actionBlockState9(); break;
    case ActionBlockState10: return actionBlockState10(); break;
    case ActionBlockState11: return actionBlockState11(); break;
    case ActionBlockState12: return actionBlockState12(); break;
    case ActionBlockState13: return actionBlockState13(); break;
    case ActionBlockState14: return actionBlockState14(); break;
    case ActionBlockState15: return actionBlockState15(); break;
    case ActionBlockState16: return actionBlockState16(); break;
    case ActionBlockState17: return actionBlockState17(); break;
    case ActionBlockState18: return actionBlockState18(); break;
    case ActionBlockState19: return actionBlockState19(); break;
    case ActionBlockState20: return actionBlockState20(); break;
    case ActionBlockState21: return actionBlockState21(); break;
    case ActionBlockState22: return actionBlockState22(); break;
    case ActionStatementState0: return actionStatementState0(); break;
    case ActionStatementState1: return actionStatementState1(); break;
    case ActionStatementState2: return actionStatementState2(); break;
    case ActionStatementState3: return actionStatementState3(); break;
    case ActionStatementState4: return actionStatementState4(); break;
    case ActionStatementState5: return actionStatementState5(); break;
    case ActionStatementState6: return actionStatementState6(); break;
    case ActionStatementState7: return actionStatementState7(); break;
    case ActionStatementState8: return actionStatementState8(); break;
    case ActionStatementState9: return actionStatementState9(); break;
    case ActionStatementState10: return actionStatementState10(); break;
    case ActionStatementState11: return actionStatementState11(); break;
    case ActionStatementState12: return actionStatementState12(); break;
    case ActionStatementState13: return actionStatementState13(); break;
    case ActionStatementState14: return actionStatementState14(); break;
    case ActionStatementState15: return actionStatementState15(); break;
    case ActionStatementState16: return actionStatementState16(); break;
    case ActionStatementState17: return actionStatementState17(); break;
    case ActionStatementState18: return actionStatementState18(); break;
    case ActionStatementState19: return actionStatementState19(); break;
    case ActionStatementState20: return actionStatementState20(); break;
    case ActionStatementState21: return actionStatementState21(); break;
    case ActionStatementState22: return actionStatementState22(); break;
    case ActionExpressionState0: return actionExpressionState0(); break;
    case ActionExpressionState1: return actionExpressionState1(); break;
    case ActionExpressionState2: return actionExpressionState2(); break;
    case ActionExpressionState3: return actionExpressionState3(); break;
    case ActionExpressionState4: return actionExpressionState4(); break;
    case ActionExpressionState5: return actionExpressionState5(); break;
    case ActionExpressionState6: return actionExpressionState6(); break;
    case ActionExpressionState7: return actionExpressionState7(); break;
    case ActionExpressionState8: return actionExpressionState8(); break;
    case ActionTermState0: return actionTermState0(); break;
    case ActionTermState1: return actionTermState1(); break;
    case ActionTermState2: return actionTermState2(); break;
    case ActionTermState3: return actionTermState3(); break;
    case ActionTermState4: return actionTermState4(); break;
    case ActionTermState5: return actionTermState5(); break;
    case ActionTermState6: return actionTermState6(); break;
    case ActionFactorState0: return actionFactorState0(); break;
    case ActionFactorState1: return actionFactorState1(); break;
    case ActionFactorState2: return actionFactorState2(); break;
    case ActionFactorState3: return actionFactorState3(); break;
    case ActionFactorState4: return actionFactorState4(); break;
    case ActionFactorState5: return actionFactorState5(); break;
    case ActionConditionState0: return actionConditionState0(); break;
    case ActionConditionState1: return actionConditionState1(); break;
    case ActionConditionState2: return actionConditionState2(); break;
    case ActionConditionState3: return actionConditionState3(); break;
    case ActionConditionState4: return actionConditionState4(); break;
    case ActionConditionState5: return actionConditionState5(); break;
    case ActionConditionState6: return actionConditionState6(); break;
    case ActionConditionState7: return actionConditionState7(); break;
    case ActionConditionState8: return actionConditionState8(); break;
    case ActionConditionState9: return actionConditionState9(); break;
    case ActionConditionState10: return actionConditionState10(); break;
    default: Q_ASSERT(false); break;
  }

  return false;
}

bool HandlerBase::actionProgramState0()
{
  return true;
}

bool HandlerBase::actionProgramState1()
{
  return true;
}

bool HandlerBase::actionProgramState2()
{
  return true;
}

bool HandlerBase::actionBlockState0()
{
  return true;
}

bool HandlerBase::actionBlockState1()
{
  return true;
}

bool HandlerBase::actionBlockState2()
{
  return true;
}

bool HandlerBase::actionBlockState3()
{
  return true;
}

bool HandlerBase::actionBlockState4()
{
  return true;
}

bool HandlerBase::actionBlockState5()
{
  return true;
}

bool HandlerBase::actionBlockState6()
{
  return true;
}

bool HandlerBase::actionBlockState7()
{
  return true;
}

bool HandlerBase::actionBlockState8()
{
  return true;
}

bool HandlerBase::actionBlockState9()
{
  return true;
}

bool HandlerBase::actionBlockState10()
{
  return true;
}

bool HandlerBase::actionBlockState11()
{
  return true;
}

bool HandlerBase::actionBlockState12()
{
  return true;
}

bool HandlerBase::actionBlockState13()
{
  return true;
}

bool HandlerBase::actionBlockState14()
{
  return true;
}

bool HandlerBase::actionBlockState15()
{
  return true;
}

bool HandlerBase::actionBlockState16()
{
  return true;
}

bool HandlerBase::actionBlockState17()
{
  return true;
}

bool HandlerBase::actionBlockState18()
{
  return true;
}

bool HandlerBase::actionBlockState19()
{
  return true;
}

bool HandlerBase::actionBlockState20()
{
  return true;
}

bool HandlerBase::actionBlockState21()
{
  return true;
}

bool HandlerBase::actionBlockState22()
{
  return true;
}

bool HandlerBase::actionStatementState0()
{
  return true;
}

bool HandlerBase::actionStatementState1()
{
  return true;
}

bool HandlerBase::actionStatementState2()
{
  return true;
}

bool HandlerBase::actionStatementState3()
{
  return true;
}

bool HandlerBase::actionStatementState4()
{
  return true;
}

bool HandlerBase::actionStatementState5()
{
  return true;
}

bool HandlerBase::actionStatementState6()
{
  return true;
}

bool HandlerBase::actionStatementState7()
{
  return true;
}

bool HandlerBase::actionStatementState8()
{
  return true;
}

bool HandlerBase::actionStatementState9()
{
  return true;
}

bool HandlerBase::actionStatementState10()
{
  return true;
}

bool HandlerBase::actionStatementState11()
{
  return true;
}

bool HandlerBase::actionStatementState12()
{
  return true;
}

bool HandlerBase::actionStatementState13()
{
  return true;
}

bool HandlerBase::actionStatementState14()
{
  return true;
}

bool HandlerBase::actionStatementState15()
{
  return true;
}

bool HandlerBase::actionStatementState16()
{
  return true;
}

bool HandlerBase::actionStatementState17()
{
  return true;
}

bool HandlerBase::actionStatementState18()
{
  return true;
}

bool HandlerBase::actionStatementState19()
{
  return true;
}

bool HandlerBase::actionStatementState20()
{
  return true;
}

bool HandlerBase::actionStatementState21()
{
  return true;
}

bool HandlerBase::actionStatementState22()
{
  return true;
}

bool HandlerBase::actionExpressionState0()
{
  return true;
}

bool HandlerBase::actionExpressionState1()
{
  return true;
}

bool HandlerBase::actionExpressionState2()
{
  return true;
}

bool HandlerBase::actionExpressionState3()
{
  return true;
}

bool HandlerBase::actionExpressionState4()
{
  return true;
}

bool HandlerBase::actionExpressionState5()
{
  return true;
}

bool HandlerBase::actionExpressionState6()
{
  return true;
}

bool HandlerBase::actionExpressionState7()
{
  return true;
}

bool HandlerBase::actionExpressionState8()
{
  return true;
}

bool HandlerBase::actionTermState0()
{
  return true;
}

bool HandlerBase::actionTermState1()
{
  return true;
}

bool HandlerBase::actionTermState2()
{
  return true;
}

bool HandlerBase::actionTermState3()
{
  return true;
}

bool HandlerBase::actionTermState4()
{
  return true;
}

bool HandlerBase::actionTermState5()
{
  return true;
}

bool HandlerBase::actionTermState6()
{
  return true;
}

bool HandlerBase::actionFactorState0()
{
  return true;
}

bool HandlerBase::actionFactorState1()
{
  return true;
}

bool HandlerBase::actionFactorState2()
{
  return true;
}

bool HandlerBase::actionFactorState3()
{
  return true;
}

bool HandlerBase::actionFactorState4()
{
  return true;
}

bool HandlerBase::actionFactorState5()
{
  return true;
}

bool HandlerBase::actionConditionState0()
{
  return true;
}

bool HandlerBase::actionConditionState1()
{
  return true;
}

bool HandlerBase::actionConditionState2()
{
  return true;
}

bool HandlerBase::actionConditionState3()
{
  return true;
}

bool HandlerBase::actionConditionState4()
{
  return true;
}

bool HandlerBase::actionConditionState5()
{
  return true;
}

bool HandlerBase::actionConditionState6()
{
  return true;
}

bool HandlerBase::actionConditionState7()
{
  return true;
}

bool HandlerBase::actionConditionState8()
{
  return true;
}

bool HandlerBase::actionConditionState9()
{
  return true;
}

bool HandlerBase::actionConditionState10()
{
  return true;
}
