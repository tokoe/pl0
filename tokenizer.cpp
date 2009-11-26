
#include "tokenizer.h"

#include <QtCore/QDebug>

typedef enum {
  InvalidInput = -2,
  SpecialInput = 0,
  DigitInput = 1,
  CharacterInput = 2,
  ColonInput = 3,
  EqualInput = 4,
  LessThanInput = 5,
  GreaterThanInput = 6,
  SpaceInput = 7,
} InputType;

typedef enum {
  Read = 1,
  Write = 2,
  WriteUpper = 4,
  Finish = 8
} ActionsType;

typedef struct {
  int function;
  int state;
} StateTableEntry;

StateTableEntry s_stateTable[6][8] = {
/*             Special                 Digit                Char                   Colon                 Equal                 LessThan            GreaterThan        Space */
/* 0 */ { { Read|Write|Finish, 0 }, { Read|Write, 2 }, { Read|WriteUpper, 1 }, { Read|Write, 3 }, { Read|Write|Finish, 0 }, { Read|Write, 4 }, { Read|Write, 5 }, { Read, 0 } },
/* 1 */ { { Finish, 0 },            { Read|Write, 1 }, { Read|WriteUpper, 1 }, { Finish, 0 },     { Finish, 0 },            { Finish, 0 },     { Finish, 0 },     { Finish, 0 } },
/* 2 */ { { Finish, 0 },            { Read|Write, 2 }, { Finish, 0 },          { Finish, 0 },     { Finish, 0 },            { Finish, 0 },     { Finish, 0 },     { Finish, 0 } },
/* 3 */ { { Finish, 0 },            { Finish, 0 },     { Finish, 0 },          { Finish, 0 },     { Read|Write|Finish, 0 }, { Finish, 0 },     { Finish, 0 },     { Finish, 0 } },
/* 4 */ { { Finish, 0 },            { Finish, 0 },     { Finish, 0 },          { Finish, 0 },     { Read|Write|Finish, 0 }, { Finish, 0 },     { Finish, 0 },     { Finish, 0 } },
/* 5 */ { { Finish, 0 },            { Finish, 0 },     { Finish, 0 },          { Finish, 0 },     { Read|Write|Finish, 0 }, { Finish, 0 },     { Finish, 0 },     { Finish, 0 } } };

int s_inputMap[] = {
/* 0x00 */ -1, -2, -2, -2, -2, -2, -2, -2, -2, -2,  7, -2, -2,  7, -2, -2,
/* 0x10 */ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
/* 0x20 */  7,  0, -2,  0, -2, -2, -2, -2,  0,  0,  0,  0,  0,  0,  0,  0,
/* 0x30 */  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  0,  5,  4,  6,  0,
/* 0x40 */ -2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
/* 0x50 */  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -2, -2, -2, -2, -2,
/* 0x60 */ -2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
/* 0x70 */  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, -2, -2, -2, -2, -2 };


Tokenizer::Tokenizer()
{
  reset();
}

bool Tokenizer::load( QIODevice *device )
{
  reset();
  mDevice = device;
  mDevice->getChar( &mCurrentChar );

  return true;
}

void Tokenizer::operationWrite( char character )
{
  mOutputBuffer.append( character );
}

void Tokenizer::operationWriteUpper( char character )
{
  mOutputBuffer.append( QChar( character ).toUpper() );
}

void Tokenizer::operationRead( char )
{
  if ( mDevice->atEnd() )
    mCurrentChar = 0;
  else
    mDevice->getChar( &mCurrentChar );

  if ( mCurrentChar == '\n' ) {
    mCurrentRow++;
    mCurrentColumn = 0;
  } else {
    mCurrentColumn++;
  }
}

void Tokenizer::operationFinish( char character )
{
  switch ( mCurrentState ) {
    case 0: // end state is 0
      mCurrentToken = Token( Token::SpecialToken, mCurrentRow, mCurrentColumn );
      switch ( character ) {
        case '.': mCurrentToken.setSymbolValue( Token::DotSymbol ); break;
        case ',': mCurrentToken.setSymbolValue( Token::CommaSymbol ); break;
        case ';': mCurrentToken.setSymbolValue( Token::SemicolonSymbol ); break;
        case '?': mCurrentToken.setSymbolValue( Token::InputSymbol ); break;
        case '!': mCurrentToken.setSymbolValue( Token::OutputSymbol ); break;
        case '+': mCurrentToken.setSymbolValue( Token::PlusSymbol ); break;
        case '-': mCurrentToken.setSymbolValue( Token::MinusSymbol ); break;
        case '*': mCurrentToken.setSymbolValue( Token::MulSymbol ); break;
        case '/': mCurrentToken.setSymbolValue( Token::DivSymbol ); break;
        case '(': mCurrentToken.setSymbolValue( Token::OpenBracketSymbol ); break;
        case ')': mCurrentToken.setSymbolValue( Token::CloseBracketSymbol ); break;
        case '=': mCurrentToken.setSymbolValue( Token::EqualsSymbol ); break;
        case '#': mCurrentToken.setSymbolValue( Token::UnequalSymbol ); break;
      }
      break;
    case 1:
      {
        static QMap<QString, Token::SymbolType> map;
        if ( map.isEmpty() ) {
          map.insert( "CONST", Token::ConstSymbol );
          map.insert( "VAR", Token::VarSymbol );
          map.insert( "PROCEDURE", Token::ProcedureSymbol );
          map.insert( "CALL", Token::CallSymbol );
          map.insert( "BEGIN", Token::BeginSymbol );
          map.insert( "END", Token::EndSymbol );
          map.insert( "IF", Token::IfSymbol );
          map.insert( "THEN", Token::ThenSymbol );
          map.insert( "WHILE", Token::WhileSymbol );
          map.insert( "DO", Token::DoSymbol );
          map.insert( "ODD", Token::OddSymbol );
        }

        if ( map.contains( mOutputBuffer ) ) {
          mCurrentToken = Token( Token::SpecialToken, mCurrentRow, mCurrentColumn );
          mCurrentToken.setSymbolValue( map.value( mOutputBuffer ) );
        } else {
          mCurrentToken = Token( Token::IdentifierToken, mCurrentRow, mCurrentColumn );
          mCurrentToken.setIdentifierValue( mOutputBuffer );
        }
      }
      break;
    case 2:
      mCurrentToken = Token( Token::NumericToken, mCurrentRow, mCurrentColumn );
      mCurrentToken.setNumericValue( mOutputBuffer.toInt() );
      break;
    case 3:
      if ( mOutputBuffer == ":=" ) {
        mCurrentToken = Token( Token::SpecialToken, mCurrentRow, mCurrentColumn );
        mCurrentToken.setSymbolValue( Token::AssignSymbol );
      }
      break;
    case 4:
      mCurrentToken = Token( Token::SpecialToken, mCurrentRow, mCurrentColumn );
      if ( mOutputBuffer == "<=" )
        mCurrentToken.setSymbolValue( Token::LessThanEqualSymbol );
      else
        mCurrentToken.setSymbolValue( Token::LessThanSymbol );
      break;
    case 5:
      mCurrentToken = Token( Token::SpecialToken, mCurrentRow, mCurrentColumn );
      if ( mOutputBuffer == ">=" )
        mCurrentToken.setSymbolValue( Token::GreaterThanEqualSymbol );
      else
        mCurrentToken.setSymbolValue( Token::GreaterThanSymbol );
      break;
    default:
      mCurrentToken = Token( Token::ErrorToken, mCurrentRow, mCurrentColumn );
      break; 
  }
}

Token Tokenizer::nextToken()
{
  if ( !mIsProcessed )
    return mCurrentToken;

  mIsProcessed = false;
  mCurrentState = 0;
  mOutputBuffer.clear();

  while ( true ) {

    char character = (mCurrentChar & 0x7f);

    const InputType characterClass = (InputType)s_inputMap[ (int)character ];
    switch ( characterClass ) {
      case -2:
        qDebug() << "Recognized invalid character '" << character << "' at row " << mCurrentRow << ", column " << mCurrentColumn;
        return Token( Token::ErrorToken, mCurrentRow, mCurrentColumn );
        break;
      case -1:
        return Token( Token::EndToken, mCurrentRow, mCurrentColumn );
        break;
      default:
        {
          const StateTableEntry entry = s_stateTable[ mCurrentState ][ characterClass ];

          // WRITE operation
          if ( entry.function & Write )
            operationWrite( character );

          // WRITE UPPER operation
          if ( entry.function & WriteUpper )
            operationWriteUpper( character );

          // READ operation
          if ( entry.function & Read )
            operationRead( character );

          // FINISH operation
          if ( entry.function & Finish ) {
            operationFinish( character );

            return mCurrentToken;
          }

          mCurrentState = entry.state;
        }
        break;
    }
  } 

  return Token( Token::EndToken, mCurrentRow, mCurrentColumn );
}

void Tokenizer::tokenProcessed()
{
  mIsProcessed = true;
}

void Tokenizer::reset()
{
  mDevice = 0;
  mIsProcessed = true;
  mCurrentState = 0;
  mOutputBuffer.clear();
  mCurrentRow = 0;
  mCurrentColumn = 0;
}
