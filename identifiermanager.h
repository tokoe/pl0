
#ifndef IDENTIFIERMANAGER_H
#define IDENTIFIERMANAGER_H

#include <QtCore/QString>

class IdentifierManager
{
  public:
    IdentifierManager();
    ~IdentifierManager();

    void setName( const QString &name );
    void setValue( int value );

    bool pushConstIdentifier();
    bool pushVariableIdentifier();
    bool pushProcedure();
    bool endProcedure();

    bool hasVariableIdentifier( const QString &name ) const;
    bool hasConstIdentifier( const QString &name ) const;
    bool hasAnonymousConstIdentifier( int value ) const;
    bool hasProcedureIdentifier( const QString &name ) const;

    bool hasLocalVariableIdentifier( const QString &name ) const;
    bool hasLocalConstIdentifier( const QString &name ) const;
    bool hasLocalProcedureIdentifier( const QString &name ) const;

    int procedureIndex( const QString &name ) const;

  private:
    class IdentifierBase;
    class ConstIdentifier;
    class VariableIdentifier;
    class ProcedureIdentifier;

    IdentifierBase* find( int type, const QString &name ) const;
    IdentifierBase* findLocal( int type, const QString &name ) const;

    ProcedureIdentifier *mMainProcedure;
    ProcedureIdentifier *mCurrentProcedure;
    int mProcedureCounter;
    int mConstIdentifierCounter;
    QString mCurrentName;
    int mCurrentValue;
};

#endif
