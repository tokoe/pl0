#ifndef TOKEN_H
#define TOKEN_H

#include <QtCore/QString>

class Token
{
  public:
    enum TokenType
    {
      NumericToken,
      IdentifierToken,
      SpecialToken,
      EndToken,
      ErrorToken
    };

    enum SymbolType
    {
      DotSymbol,
      CommaSymbol,
      SemicolonSymbol,
      InputSymbol,
      OutputSymbol,
      PlusSymbol,
      MinusSymbol,
      MulSymbol,
      DivSymbol,
      OpenBracketSymbol,
      CloseBracketSymbol,
      ConstSymbol,
      VarSymbol,
      ProcedureSymbol,
      CallSymbol,
      BeginSymbol,
      EndSymbol,
      IfSymbol,
      ThenSymbol,
      WhileSymbol,
      DoSymbol,
      OddSymbol,
      EqualsSymbol,
      UnequalSymbol,
      AssignSymbol,
      LessThanSymbol,
      LessThanEqualSymbol,
      GreaterThanSymbol,
      GreaterThanEqualSymbol
    };

    Token( TokenType type = EndToken, int row = 0, int column = 0 );

    TokenType type() const;

    int row() const;
    int column() const;

    void setIdentifierValue( const QString &value );
    QString identifierValue() const;

    void setNumericValue( int value );
    int numericValue() const;

    void setSymbolValue( SymbolType value );
    SymbolType symbolValue() const;

    static QString typeName( TokenType type );
    static QString symbolName( SymbolType symbol );

  private:
    TokenType mType;

    QString mIdentifierValue;
    int mNumericValue;
    SymbolType mSymbolValue;

    /* position of occurence */
    unsigned int mRow;
    unsigned int mColumn;
};

QDebug operator<<( QDebug, const Token& );

#endif
