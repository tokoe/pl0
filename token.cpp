
#include "token.h"

#include <QtCore/QDebug>

Token::Token( TokenType type, int row, int column )
  : mType( type ), mRow( row ), mColumn( column )
{
}

Token::TokenType Token::type() const
{
  return mType;
}

int Token::row() const
{
  return mRow;
}

int Token::column() const
{
  return mColumn;
}

void Token::setIdentifierValue( const QString &value )
{
  mIdentifierValue = value;
}

QString Token::identifierValue() const
{
  return mIdentifierValue;
}

void Token::setNumericValue( int value )
{
  mNumericValue = value;
}

int Token::numericValue() const
{
  return mNumericValue;
}

void Token::setSymbolValue( SymbolType value )
{
  mSymbolValue = value;
}

Token::SymbolType Token::symbolValue() const
{
  return mSymbolValue;
}

QString Token::typeName( TokenType type )
{
  switch ( type ) {
    case Token::EndToken:
      return "EndToken";
      break;
    case Token::ErrorToken:
      return "ErrorToken";
      break;
    case Token::NumericToken:
      return "NumericToken";
      break;
    case Token::IdentifierToken:
      return "IdentifierToken";
      break;
    case Token::SpecialToken:
      return "SpecialToken";
      break;
    default:
      return QString();
      break;
  }
}

QString Token::symbolName( SymbolType symbol )
{
  switch ( symbol ) {
    case Token::DotSymbol: return "."; break;
    case Token::CommaSymbol: return ","; break;
    case Token::SemicolonSymbol: return ";"; break;
    case Token::InputSymbol: return "?"; break;
    case Token::OutputSymbol: return "!"; break;
    case Token::PlusSymbol: return "+"; break;
    case Token::MinusSymbol: return "-"; break;
    case Token::MulSymbol: return "*"; break;
    case Token::DivSymbol: return "/"; break;
    case Token::OpenBracketSymbol: return "("; break;
    case Token::CloseBracketSymbol: return ")"; break;
    case Token::ConstSymbol: return "CONST"; break;
    case Token::VarSymbol: return "VAR"; break;
    case Token::ProcedureSymbol: return "PROCEDURE"; break;
    case Token::CallSymbol: return "CALL"; break;
    case Token::BeginSymbol: return "BEGIN"; break;
    case Token::EndSymbol: return "END"; break;
    case Token::IfSymbol: return "IF"; break;
    case Token::ThenSymbol: return "THEN"; break;
    case Token::WhileSymbol: return "WHILE"; break;
    case Token::DoSymbol: return "DO"; break;
    case Token::OddSymbol: return "ODD"; break;
    case Token::EqualsSymbol: return "= (EQUALS)"; break;
    case Token::UnequalSymbol: return "#"; break;
    case Token::AssignSymbol: return "= (ASSIGN)"; break;
    case Token::LessThanSymbol: return "<"; break;
    case Token::LessThanEqualSymbol: return "<="; break;
    case Token::GreaterThanSymbol: return ">"; break;
    case Token::GreaterThanEqualSymbol: return ">="; break;
    default: return QString(); break;
  }
}

QDebug operator<<( QDebug debug, const Token &token )
{
  QString content;

  switch ( token.type() ) {
    case Token::EndToken:
      break;
    case Token::ErrorToken:
      break;
    case Token::NumericToken:
      content = QString::number( token.numericValue() );
      break;
    case Token::IdentifierToken:
      content = token.identifierValue();
      break;
    case Token::SpecialToken:
      content = Token::symbolName( token.symbolValue() );
      break;
  }

  if ( content.isEmpty() )
    content = '(' + content + ')';

  const QString position = '[' + QString::number( token.row() ) + ':' + QString::number( token.column() ) + ']';

  debug << "Token:" << Token::typeName( token.type() ) << " " << content << position;

  return debug;
}
