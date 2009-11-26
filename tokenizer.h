#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

#include <QtCore/QIODevice>

class Tokenizer
{
  public:
    Tokenizer();

    bool load( QIODevice *device );

    Token nextToken();

    void tokenProcessed();

  private:
    void reset();
    void operationWrite( char );
    void operationWriteUpper( char );
    void operationRead( char );
    void operationFinish( char );

    QIODevice *mDevice;
    char mCurrentChar;
    Token mCurrentToken;
    bool mIsProcessed;

    int mCurrentRow;
    int mCurrentColumn;

    int mCurrentState;
    QString mOutputBuffer;
};

#endif
