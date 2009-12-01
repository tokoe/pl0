
#include "parser.h"

#include "codegenerationhandler.h"
#include "codewriter.h"
#include "handlerbase.h"
#include "identifierhandler.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QStringList>

typedef enum
{
  NilTransition,
  SymbolTransition,
  GraphTransition,
  MorphemTransition,
  EndTransition
} TransitionType;


struct Transition {
  TransitionType type;

  union {
    unsigned long X;
    Token::SymbolType symbol;
    int graphId;
    Token::TokenType morphemType;
  } description;

  int nextTransition;
  int alternativeTransition; 
  HandlerBase::ActionType actionType;
};

static void graphToDot( Transition *transition, const QString &graphName, const QString &fileName )
{
  const QStringList graphNames = QStringList() << "[program]" << "[block]"
                                               << "[statement]" << "[expression]"
                                               << "[term]" << "[factor]" << "[condition]";
  QByteArray data;
  QTextStream s( &data );

  s << "digraph " << graphName << " {\n";
  s << "  mindist = 2.0\n";

  QMap<int, int> alternativeMap;
  int pos = 0;
  Transition t = transition[ pos ];
  while ( t.type != EndTransition ) {
    if ( t.alternativeTransition != -1 ) {
      if ( alternativeMap.contains( pos ) )
        alternativeMap.insert( t.alternativeTransition, alternativeMap.value( pos ) );
      else
        alternativeMap.insert( t.alternativeTransition, pos );
    }
    pos++;
    t = transition[ pos ];
  }

  pos = 0;
  t = transition[ pos ];
  while ( t.type != EndTransition ) {
    QString startState;
    if ( alternativeMap.contains( pos ) )
      startState = QString( "s%1" ).arg( alternativeMap.value( pos ) );
    else
      startState = QString( "s%1" ).arg( pos );

    const QString endState = QString( "s%1" ).arg( t.nextTransition );

    QString label;
    switch ( t.type ) {
      case NilTransition: label = "&#949;"; break;
      case SymbolTransition: label = Token::symbolName( t.description.symbol ); break;
      case GraphTransition: label = graphNames.at( t.description.graphId ); break;
      case MorphemTransition: label = Token::typeName( t.description.morphemType ); break;
      default: label = QString(); break;
    }

    s << "  " << startState << " -> " << endState << " [label=\"" << label << " (" << pos << ")\"]\n";

    pos++;
    t = transition[ pos ];
  }

  s << "}\n";

  s.flush();

  QFile file( QString( "%1.dot" ).arg( fileName ) );
  file.open( QIODevice::WriteOnly );
  file.write( data );
  file.close();

  system( QString( "dot %1.dot -Tpng > graphs/%1.png" ).arg( fileName ).toLatin1() );

  QFile::remove( QString( "%1.dot" ).arg( fileName ) );
}

Transition s_Program[] = {
 /* 0*/ { GraphTransition,  {(unsigned long)1},                1, -1, HandlerBase::ActionProgramState0 },
 /* 1*/ { SymbolTransition, {(unsigned long)Token::DotSymbol}, 2, -1, HandlerBase::ActionProgramState1 },
 /* 2*/ { EndTransition,    {(unsigned long)0},                0, -1, HandlerBase::ActionProgramState2 }
};

Transition s_Block[] = {
 /* 0*/ { SymbolTransition,  {(unsigned long)Token::ConstSymbol},      1,  7, HandlerBase::ActionBlockState0 },
 /* 1*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken},  2, -1, HandlerBase::ActionBlockState1 },
 /* 2*/ { SymbolTransition,  {(unsigned long)Token::EqualsSymbol},     3, -1, HandlerBase::ActionBlockState2 },
 /* 3*/ { MorphemTransition, {(unsigned long)Token::NumericToken},     4, -1, HandlerBase::ActionBlockState3 },
 /* 4*/ { SymbolTransition,  {(unsigned long)Token::SemicolonSymbol},  6,  5, HandlerBase::ActionBlockState4 },
 /* 5*/ { SymbolTransition,  {(unsigned long)Token::CommaSymbol},      1, -1, HandlerBase::ActionBlockState5 },
 /* 6*/ { NilTransition,     {(unsigned long)0},                       8, -1, HandlerBase::ActionBlockState6 },
 /* 7*/ { NilTransition,     {(unsigned long)0},                       8, -1, HandlerBase::ActionBlockState7 },
 /* 8*/ { SymbolTransition,  {(unsigned long)Token::VarSymbol},        9, 13, HandlerBase::ActionBlockState8 },
 /* 9*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken}, 10, -1, HandlerBase::ActionBlockState9 },
 /*10*/ { SymbolTransition,  {(unsigned long)Token::CommaSymbol},      9, 11, HandlerBase::ActionBlockState10 },
 /*11*/ { SymbolTransition,  {(unsigned long)Token::SemicolonSymbol}, 12, -1, HandlerBase::ActionBlockState11 },
 /*12*/ { NilTransition,     {(unsigned long)0},                      14, -1, HandlerBase::ActionBlockState12 },
 /*13*/ { NilTransition,     {(unsigned long)0},                      14, -1, HandlerBase::ActionBlockState13 },
 /*14*/ { SymbolTransition,  {(unsigned long)Token::ProcedureSymbol}, 15, 20, HandlerBase::ActionBlockState14 },
 /*15*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken}, 16, -1, HandlerBase::ActionBlockState15 },
 /*16*/ { SymbolTransition,  {(unsigned long)Token::SemicolonSymbol}, 17, -1, HandlerBase::ActionBlockState16 },
 /*17*/ { GraphTransition,   {(unsigned long)1},                      18, -1, HandlerBase::ActionBlockState17 },
 /*18*/ { SymbolTransition,  {(unsigned long)Token::SemicolonSymbol}, 19, -1, HandlerBase::ActionBlockState18 },
 /*19*/ { NilTransition,     {(unsigned long)0},                      14, -1, HandlerBase::ActionBlockState19 },
 /*20*/ { NilTransition,     {(unsigned long)0},                      21, -1, HandlerBase::ActionBlockState20 },
 /*21*/ { GraphTransition,   {(unsigned long)2},                      22, -1, HandlerBase::ActionBlockState21 },
 /*22*/ { EndTransition,     {(unsigned long)0},                       0, -1, HandlerBase::ActionBlockState22 }
};

Transition s_Statement[] = {
 /* 0*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken},  1,  3, HandlerBase::ActionStatementState0 },
 /* 1*/ { SymbolTransition,  {(unsigned long)Token::AssignSymbol},     2, -1, HandlerBase::ActionStatementState1 },
 /* 2*/ { GraphTransition,   {(unsigned long)3},                      22, -1, HandlerBase::ActionStatementState2 },
 /* 3*/ { SymbolTransition,  {(unsigned long)Token::IfSymbol},         4,  7, HandlerBase::ActionStatementState3 },
 /* 4*/ { GraphTransition,   {(unsigned long)6},                       5, -1, HandlerBase::ActionStatementState4 },
 /* 5*/ { SymbolTransition,  {(unsigned long)Token::ThenSymbol},       6, -1, HandlerBase::ActionStatementState5 },
 /* 6*/ { GraphTransition,   {(unsigned long)2},                      22, -1, HandlerBase::ActionStatementState6 },
 /* 7*/ { SymbolTransition,  {(unsigned long)Token::WhileSymbol},      8, 11, HandlerBase::ActionStatementState7 },
 /* 8*/ { GraphTransition,   {(unsigned long)6},                       9, -1, HandlerBase::ActionStatementState8 },
 /* 9*/ { SymbolTransition,  {(unsigned long)Token::DoSymbol},        10, -1, HandlerBase::ActionStatementState9 },
 /*10*/ { GraphTransition,   {(unsigned long)2},                      22, -1, HandlerBase::ActionStatementState10 },
 /*11*/ { SymbolTransition,  {(unsigned long)Token::BeginSymbol},     12, 15, HandlerBase::ActionStatementState11 },
 /*12*/ { GraphTransition,   {(unsigned long)2},                      14, -1, HandlerBase::ActionStatementState12 },
 /*13*/ { SymbolTransition,  {(unsigned long)Token::EndSymbol},       22, -1, HandlerBase::ActionStatementState13 },
 /*14*/ { SymbolTransition,  {(unsigned long)Token::SemicolonSymbol}, 12, 13, HandlerBase::ActionStatementState14 },
 /*15*/ { SymbolTransition,  {(unsigned long)Token::CallSymbol},      16, 17, HandlerBase::ActionStatementState15 },
 /*16*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken}, 22, -1, HandlerBase::ActionStatementState16 },
 /*17*/ { SymbolTransition,  {(unsigned long)Token::InputSymbol},     18, 19, HandlerBase::ActionStatementState17 },
 /*18*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken}, 22, -1, HandlerBase::ActionStatementState18 },
 /*19*/ { SymbolTransition,  {(unsigned long)Token::OutputSymbol},    20, 21, HandlerBase::ActionStatementState19 },
 /*20*/ { GraphTransition,   {(unsigned long)3},                      22, -1, HandlerBase::ActionStatementState20 },
 /*21*/ { NilTransition,     {(unsigned long)0},                      22, -1, HandlerBase::ActionStatementState21 },
 /*22*/ { EndTransition,     {(unsigned long)0},                       0, -1, HandlerBase::ActionStatementState22 }
};

Transition s_Expression[] = {
 /* 0*/ { SymbolTransition,  {(unsigned long)Token::MinusSymbol},      2,  1, HandlerBase::ActionExpressionState0 },
 /* 1*/ { NilTransition,     {(unsigned long)0},                       2, -1, HandlerBase::ActionExpressionState1 },
 /* 2*/ { GraphTransition,   {(unsigned long)4},                       3, -1, HandlerBase::ActionExpressionState2 },
 /* 3*/ { NilTransition,     {(unsigned long)0},                       4, -1, HandlerBase::ActionExpressionState3 },
 /* 4*/ { SymbolTransition,  {(unsigned long)Token::PlusSymbol},       6,  5, HandlerBase::ActionExpressionState4 },
 /* 5*/ { SymbolTransition,  {(unsigned long)Token::MinusSymbol},      7,  8, HandlerBase::ActionExpressionState5 },
 /* 6*/ { GraphTransition,   {(unsigned long)4},                       3, -1, HandlerBase::ActionExpressionState6 },
 /* 7*/ { GraphTransition,   {(unsigned long)4},                       3, -1, HandlerBase::ActionExpressionState7 },
 /* 8*/ { EndTransition,     {(unsigned long)0},                       0, -1, HandlerBase::ActionExpressionState8 }
};

Transition s_Term[] = {
 /* 0*/ { GraphTransition,   {(unsigned long)5},                       1, -1, HandlerBase::ActionTermState0 },
 /* 1*/ { NilTransition,     {(unsigned long)0},                       2, -1, HandlerBase::ActionTermState1 },
 /* 2*/ { SymbolTransition,  {(unsigned long)Token::MulSymbol},        3,  4, HandlerBase::ActionTermState2 },
 /* 3*/ { GraphTransition,   {(unsigned long)5},                       1, -1, HandlerBase::ActionTermState3 },
 /* 4*/ { SymbolTransition,  {(unsigned long)Token::DivSymbol},        5,  6, HandlerBase::ActionTermState4 },
 /* 5*/ { GraphTransition,   {(unsigned long)5},                       1, -1, HandlerBase::ActionTermState5 },
 /* 6*/ { EndTransition,     {(unsigned long)0},                       0, -1, HandlerBase::ActionTermState6 }
};

Transition s_Factor[] = {
 /* 0*/ { MorphemTransition, {(unsigned long)Token::NumericToken},       5,  1, HandlerBase::ActionFactorState0 },
 /* 1*/ { SymbolTransition,  {(unsigned long)Token::OpenBracketSymbol},  2,  4, HandlerBase::ActionFactorState1 },
 /* 2*/ { GraphTransition,   {(unsigned long)3},                         3, -1, HandlerBase::ActionFactorState2 },
 /* 3*/ { SymbolTransition,  {(unsigned long)Token::CloseBracketSymbol}, 5, -1, HandlerBase::ActionFactorState3 },
 /* 4*/ { MorphemTransition, {(unsigned long)Token::IdentifierToken},    5, -1, HandlerBase::ActionFactorState4 },
 /* 5*/ { EndTransition,     {(unsigned long)0},                         0, -1, HandlerBase::ActionFactorState5 }
};

Transition s_Condition[] = {
 /* 0*/ { SymbolTransition,  {(unsigned long)Token::OddSymbol},              1,  2, HandlerBase::ActionConditionState0 },
 /* 1*/ { GraphTransition,   {(unsigned long)3},                            10, -1, HandlerBase::ActionConditionState1 },
 /* 2*/ { GraphTransition,   {(unsigned long)3},                             3, -1, HandlerBase::ActionConditionState2 },
 /* 3*/ { SymbolTransition,  {(unsigned long)Token::EqualsSymbol},           4,  5, HandlerBase::ActionConditionState3 },
 /* 4*/ { GraphTransition,   {(unsigned long)3},                            10, -1, HandlerBase::ActionConditionState4 },
 /* 5*/ { SymbolTransition,  {(unsigned long)Token::UnequalSymbol},          4,  6, HandlerBase::ActionConditionState5 },
 /* 6*/ { SymbolTransition,  {(unsigned long)Token::LessThanSymbol},         4,  7, HandlerBase::ActionConditionState6 },
 /* 7*/ { SymbolTransition,  {(unsigned long)Token::LessThanEqualSymbol},    4,  8, HandlerBase::ActionConditionState7 },
 /* 8*/ { SymbolTransition,  {(unsigned long)Token::GreaterThanSymbol},      4,  9, HandlerBase::ActionConditionState8 },
 /* 9*/ { SymbolTransition,  {(unsigned long)Token::GreaterThanEqualSymbol}, 4, -1, HandlerBase::ActionConditionState9 },
 /*10*/ { EndTransition,     {(unsigned long)0},                             0, -1, HandlerBase::ActionConditionState10 }
};

Transition* s_graphs[] = {
  s_Program,
  s_Block,
  s_Statement,
  s_Expression,
  s_Term,
  s_Factor,
  s_Condition
};

Parser::Parser()
{
  mActionHandlers.append( new IdentifierHandler( &mIdentifierManager ) );
}

Parser::~Parser()
{
  qDeleteAll( mActionHandlers );
}

void Parser::outputGraphs()
{
  graphToDot( s_Program,    "program",    "program" );
  graphToDot( s_Block,      "block",      "block" );
  graphToDot( s_Statement,  "statement",  "statement" );
  graphToDot( s_Expression, "expression", "expression" );
  graphToDot( s_Term,       "term",       "term" );
  graphToDot( s_Factor,     "factor",     "factor" );
  graphToDot( s_Condition,  "condition",  "condition" );
}

void Parser::load( QIODevice *device )
{
  mTokenizer.load( device );
}

bool Parser::parse( QIODevice *output )
{
  mActionHandlers.append( new CodeGenerationHandler( &mIdentifierManager, new CodeWriter( output ) ) );

  return parse( s_Program ); 
}

QString Parser::errorText() const
{
  return mErrorText;
}

bool Parser::parse( Transition *transition )
{
  Token currentToken = mTokenizer.nextToken();

  int transitionState = 0;
  while ( true ) {
/*
    qDebug() << currentToken;
    if ( transition == s_Program )
      qDebug() << "graph=program";
    else if ( transition == s_Block )
      qDebug() << "graph=block";
    else if ( transition == s_Statement )
      qDebug() << "graph=statement";
    else if ( transition == s_Expression )
      qDebug() << "graph=expression";
    else if ( transition == s_Term )
      qDebug() << "graph=term";
    else if ( transition == s_Factor )
      qDebug() << "graph=factor";
    else if ( transition == s_Condition )
      qDebug() << "graph=condition";
    qDebug() << "transitionstate=" << transitionState;
*/
    if ( currentToken.type() == Token::ErrorToken )
      return false;

    if ( currentToken.type() == Token::EndToken )
      return ((transition == s_Program) && (transitionState == 2));

    bool success = false;
    if ( transition[ transitionState ].type == NilTransition ) {
      success = true;
    } else if ( transition[ transitionState ].type == SymbolTransition ) {
      if ( transition[ transitionState ].description.symbol == currentToken.symbolValue() ) {
        success = true;
        mTokenizer.tokenProcessed();
      } else {
        if ( mErrorText.isEmpty() ) {
          mErrorText = QString("[%1:%2] Expected symbol %3 got %4").arg( currentToken.row() )
                                                                   .arg( currentToken.column() )
                                                                   .arg( Token::symbolName( transition[ transitionState ].description.symbol ) )
                                                                   .arg( Token::symbolName( currentToken.symbolValue() ) );
        }
      }
    } else if ( transition[ transitionState ].type == MorphemTransition ) {
      if ( transition[ transitionState ].description.morphemType == currentToken.type() ) {
        success = true;
        mTokenizer.tokenProcessed();
      } else {
        if ( mErrorText.isEmpty() ) {
          mErrorText = QString("[%1:%2] Expected morphem %3 got %4").arg( currentToken.row() )
                                                                    .arg( currentToken.column() )
                                                                    .arg( Token::typeName( transition[ transitionState ].description.morphemType ) )
                                                                    .arg( Token::typeName( currentToken.type() ) );
        }
      }
    } else if ( transition[ transitionState ].type == GraphTransition ) {
      success = parse( s_graphs[ transition[ transitionState ].description.graphId ] );
    } else if ( transition[ transitionState ].type == EndTransition ) {
      return true;
    }

    if ( success ) {
      for ( int i = 0; (i < mActionHandlers.count()) && success; ++i ) {
        mActionHandlers.at( i )->setCurrentToken( currentToken );
        if ( !mActionHandlers.at( i )->executeAction( transition[ transitionState ].actionType ) ) {
          mErrorText = mActionHandlers.at( i )->errorText();
          success = false;
        }
      }
    }

    if ( !success ) {
      if ( transition[ transitionState ].alternativeTransition == -1 ) {
        return false;
      } else
        transitionState = transition[ transitionState ].alternativeTransition;
    } else {
      transitionState = transition[ transitionState ].nextTransition;
      currentToken = mTokenizer.nextToken();
    }
  }
}
