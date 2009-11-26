
#include "identifiermanager.h"

#include <QtCore/QList>

static const int VariableAddressWidth = 4;

class IdentifierManager::IdentifierBase
{
  public:
    enum Type
    {
      Const,
      Variable,
      Procedure
    };

    Type type() const
    {
      return mType;
    }

    inline void setName( const QString &name )
    {
      mName = name;
    }

    inline QString name() const
    {
      return mName;
    }

  protected:
    IdentifierBase( Type type )
      : mType( type )
    {
    }

  private:
    Type mType;
    QString mName;
};

class IdentifierManager::ConstIdentifier : public IdentifierManager::IdentifierBase
{
  public:
    ConstIdentifier()
      : IdentifierBase( Const )
    {
    }

    inline void setValue( int value )
    {
      mValue = value;
    }

    inline int value() const
    {
      return mValue;
    }

    inline void setIndex( int index )
    {
      mIndex = index;
    }

    inline int index() const
    {
      return mIndex;
    }

  private:
    int mValue;
    int mIndex;
};

class IdentifierManager::VariableIdentifier : public IdentifierManager::IdentifierBase
{
  public:
    VariableIdentifier()
      : IdentifierBase( Variable )
    {
    }

    inline void setIndex( int index )
    {
      mIndex = index;
    }

    inline int index() const
    {
      return mIndex;
    }

  private:
    int mIndex;
};

class IdentifierManager::ProcedureIdentifier : public IdentifierManager::IdentifierBase
{
  public:
    ProcedureIdentifier( int index, ProcedureIdentifier *parent )
      : IdentifierBase( Procedure ),
        mIndex( index ),
        mParentProcedure( parent ),
        mVariableAddressCounter( 0 )
    {
    }

    inline ProcedureIdentifier* parentProcedure() const
    {
      return mParentProcedure;
    }

    void addIdentifier( IdentifierBase *identifier )
    {
      if ( identifier->type() == IdentifierBase::Variable ) {
        VariableIdentifier *varIdentifier = static_cast<VariableIdentifier*>( identifier );
        varIdentifier->setIndex( mVariableAddressCounter );

        mVariableAddressCounter += VariableAddressWidth;
      }

      mChildIdentifiers.append( identifier );
    }

    inline QList<IdentifierBase*> childIdentifiers() const
    {
      return mChildIdentifiers;
    }

    void cleanup()
    {
      qDeleteAll( mChildIdentifiers );
      mChildIdentifiers.clear();
    }

    inline int index() const
    {
      return mIndex;
    }

  private:
    int mIndex;
    ProcedureIdentifier *mParentProcedure;
    int mVariableAddressCounter;
    QList<IdentifierBase*> mChildIdentifiers;
};

IdentifierManager::IdentifierManager()
  : mMainProcedure( new ProcedureIdentifier( 0, 0 ) ),
    mCurrentProcedure( mMainProcedure ),
    mProcedureCounter( 1 ),
    mConstIdentifierCounter( 0 )
{
}

IdentifierManager::~IdentifierManager()
{
  delete mMainProcedure;
}

void IdentifierManager::setName( const QString &name )
{
  mCurrentName = name;
}

void IdentifierManager::setValue( int value )
{
  mCurrentValue = value;
}

bool IdentifierManager::pushConstIdentifier()
{
  ConstIdentifier *identifier = new ConstIdentifier;
  identifier->setName( mCurrentName );
  identifier->setValue( mCurrentValue );
  identifier->setIndex( mConstIdentifierCounter );

  mConstIdentifierCounter++;

  mCurrentProcedure->addIdentifier( identifier );

  return true;
}

bool IdentifierManager::pushVariableIdentifier()
{
  VariableIdentifier *identifier = new VariableIdentifier;
  identifier->setName( mCurrentName );

  mCurrentProcedure->addIdentifier( identifier );

  return true;
}

bool IdentifierManager::pushProcedure()
{
  ProcedureIdentifier *identifier = new ProcedureIdentifier( mProcedureCounter, mCurrentProcedure );
  identifier->setName( mCurrentName );

  mCurrentProcedure->addIdentifier( identifier );

  mProcedureCounter++;
  mCurrentProcedure = identifier;

  return true;
}

bool IdentifierManager::endProcedure()
{
  ProcedureIdentifier *identifier = mCurrentProcedure;
  if ( !identifier->parentProcedure() ) {
    qDebug("IdentifierManager::endProcedure(): Try to leave main method");
    return false;
  }

  mCurrentProcedure = identifier->parentProcedure();
  identifier->cleanup();

  return true;
}

bool IdentifierManager::hasVariableIdentifier( const QString &name ) const
{
  return (find( IdentifierBase::Variable, name ) != 0);
}

bool IdentifierManager::hasConstIdentifier( const QString &name ) const
{
  return (find( IdentifierBase::Const, name ) != 0);
}

bool IdentifierManager::hasAnonymousConstIdentifier( int value ) const
{
  ProcedureIdentifier *procedure = mCurrentProcedure;
  do {

    foreach ( IdentifierBase *identifier, procedure->childIdentifiers() ) {
      if ( (identifier->type() == IdentifierBase::Const) &&
           (static_cast<ConstIdentifier*>( identifier )->value() == value) )
        return true;
    }

    procedure = procedure->parentProcedure();
  } while ( procedure );

  return false;
}

bool IdentifierManager::hasProcedureIdentifier( const QString &name ) const
{
  return (find( IdentifierBase::Procedure, name ) != 0);
}

bool IdentifierManager::hasLocalVariableIdentifier( const QString &name ) const
{
  return (findLocal( IdentifierBase::Variable, name ) != 0);
}

bool IdentifierManager::hasLocalConstIdentifier( const QString &name ) const
{
  return (findLocal( IdentifierBase::Const, name ) != 0);
}

bool IdentifierManager::hasLocalProcedureIdentifier( const QString &name ) const
{
  return (findLocal( IdentifierBase::Procedure, name ) != 0);
}

int IdentifierManager::procedureIndex( const QString &name ) const
{
  ProcedureIdentifier *procedure = static_cast<ProcedureIdentifier*>( find( IdentifierBase::Procedure, name ) );
  return procedure->index();
}

IdentifierManager::IdentifierBase* IdentifierManager::find( int type, const QString &name ) const
{
  ProcedureIdentifier *procedure = mCurrentProcedure;
  do {
    if ( type == IdentifierBase::Procedure ) {
      if ( procedure->name() == name )
        return procedure;
    }

    foreach ( IdentifierBase *identifier, procedure->childIdentifiers() ) {
      if ( (identifier->type() == type) && (identifier->name() == name) )
        return identifier;
    }

    procedure = procedure->parentProcedure();
  } while ( procedure );

  return 0;
}

IdentifierManager::IdentifierBase* IdentifierManager::findLocal( int type, const QString &name ) const
{
  foreach ( IdentifierBase *identifier, mCurrentProcedure->childIdentifiers() ) {
    if ( (identifier->type() == type) && (identifier->name() == name) )
      return identifier;
  }

  return 0;
}

