
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

    inline ProcedureIdentifier* parentProcedure() const
    {
      return mParentProcedure;
    }

  protected:
    IdentifierBase( ProcedureIdentifier *parent, Type type )
      : mParentProcedure( parent ), mType( type )
    {
    }

  private:
    ProcedureIdentifier *mParentProcedure;
    Type mType;
    QString mName;
};

class IdentifierManager::ConstIdentifier : public IdentifierManager::IdentifierBase
{
  public:
    ConstIdentifier( ProcedureIdentifier *parent )
      : IdentifierBase( parent, Const )
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
    int mValue;
    int mIndex;
};

class IdentifierManager::VariableIdentifier : public IdentifierManager::IdentifierBase
{
  public:
    VariableIdentifier( ProcedureIdentifier *parent )
      : IdentifierBase( parent, Variable )
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
      : IdentifierBase( parent, Procedure ),
        mIndex( index ),
        mVariableAddressCounter( 0 )
    {
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

    inline int variableSize() const
    {
      return mVariableAddressCounter;
    }

  private:
    int mIndex;
    int mVariableAddressCounter;
    QList<IdentifierBase*> mChildIdentifiers;
};

IdentifierManager::IdentifierManager()
  : mMainProcedure( new ProcedureIdentifier( 0, 0 ) ),
    mCurrentProcedure( mMainProcedure ),
    mProcedureCounter( 1 )
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
  int index = 0;
  if ( mConstIdentifierValues.contains( mCurrentValue ) ) {
    index = mConstIdentifierValues.indexOf( mCurrentValue );
  } else {
    mConstIdentifierValues.append( mCurrentValue );
    index = mConstIdentifierValues.count() - 1;
  }

  ConstIdentifier *identifier = new ConstIdentifier( mCurrentProcedure );
  identifier->setName( mCurrentName );
  identifier->setIndex( index );

  mCurrentProcedure->addIdentifier( identifier );

  return true;
}

bool IdentifierManager::pushVariableIdentifier()
{
  VariableIdentifier *identifier = new VariableIdentifier( mCurrentProcedure );
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
  ProcedureIdentifier *identifier = static_cast<ProcedureIdentifier*>( find( IdentifierBase::Procedure, name ) );
  return identifier->index();
}

int IdentifierManager::constIndex( const QString &name ) const
{
  ConstIdentifier *identifier = static_cast<ConstIdentifier*>( find( IdentifierBase::Const, name ) );
  return identifier->index();
}

int IdentifierManager::constIndex( int value ) const
{
  return mConstIdentifierValues.indexOf( value );
}

int IdentifierManager::currentProcedureIndex() const
{
  return mCurrentProcedure->index();
}

int IdentifierManager::currentProcedureVariableSize() const
{
  return mCurrentProcedure->variableSize();
}

int IdentifierManager::procedureCount() const
{
  return mProcedureCounter;
}

QList<int> IdentifierManager::constIdentifierValues() const
{
  return mConstIdentifierValues;
}

void IdentifierManager::getVariableAddress( const QString &name, VariableType &type, int &variableAddress, int &procedureIndex ) const
{
  const VariableIdentifier *identifier = static_cast<VariableIdentifier*>( find( IdentifierBase::Variable, name ) );
  variableAddress = identifier->index();

  const ProcedureIdentifier *parentProcedure = identifier->parentProcedure();
  if ( parentProcedure == mMainProcedure ) {
    type = Main;
  } else if ( parentProcedure == mCurrentProcedure ) {
    type = Local;
  } else {
    type = Global;
    procedureIndex = parentProcedure->index();
  }
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

