#ifndef CODEWRITER_H
#define CODEWRITER_H

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
      // omit CompareNotEqual
      CompareLessThan = 18,
      CompareGreaterThan = 19,
      CompareLessEqual = 20,
      CompareGreaterThanEqual = 21,
      Call = 22,
      ReturnProc = 23,
      Jump = 24,
      JumpNot = 25,
      EntryProc = 26
    };

    CodeWriter( QIODevice *device );
    ~CodeWriter();

    void writeOperation( OpCode code, short arg );
    void writeOperation( OpCode code, short arg1, short arg2 );
    void writeOperation( OpCode code, short arg1, short arg2, short arg3 );

  private:
    QIODevice *mDevice;
};

#endif
