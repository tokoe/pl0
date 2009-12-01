#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <QtCore/QStack>

class QIODevice;

class CodeWriter
{
  public:
    enum OpCode
    {
      PutValueVariableLocal = 0,
      PutValueVariableMain = 1,
      PutValueVariableGlobal = 2,
      PutAddressVariableLocal = 3,
      PutAddressVariableMain = 4,
      PutAddressVariableGlobal = 5,
      PutConst = 6,
      StoreValue = 7,
      PutValue = 8,
      GetValue = 9,
      SignedMinus = 10,
      Odd = 11,
      Add = 12,
      Sub = 13,
      Mul = 14,
      Div = 15,
      CompareEqual = 16,
      CompareNotEqual = 17,
      CompareLessThan = 18,
      CompareGreaterThan = 19,
      CompareLessThanEqual = 20,
      CompareGreaterThanEqual = 21,
      Call = 22,
      ReturnProc = 23,
      Jump = 24,
      JumpNot = 25,
      EntryProc = 26
    };

    CodeWriter( QIODevice *device );
    ~CodeWriter();

    void writeOperation( OpCode code );
    void writeOperation( OpCode code, short arg );
    void writeOperation( OpCode code, short arg1, short arg2 );
    void writeOperation( OpCode code, short arg1, short arg2, short arg3 );

    void writeOperationAtPosition( qint64 position, OpCode code );
    void writeOperationAtPosition( qint64 position, OpCode code, short arg );
    void writeOperationAtPosition( qint64 position, OpCode code, short arg1, short arg2 );
    void writeOperationAtPosition( qint64 position, OpCode code, short arg1, short arg2, short arg3 );

    void write( short arg );
    void writeAtPosition( qint64 position, short arg );

    qint64 currentPosition() const;

    void pushLabel( qint64 position );
    qint64 popLabel();

  private:
    QIODevice *mDevice;
    QStack<qint64> mLabels;
};

#endif
