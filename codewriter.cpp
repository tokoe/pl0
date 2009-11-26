
#include "codewriter.h"

#include <QtCore/QIODevice>

CodeWriter::CodeWriter( QIODevice *device )
  : mDevice( device )
{
}

CodeWriter::~CodeWriter()
{
}

void CodeWriter::writeOperation( OpCode code )
{
  mDevice->putChar( code );
}

void CodeWriter::writeOperation( OpCode code, short arg )
{
  mDevice->putChar( code );
  mDevice->putChar( (unsigned char)(arg & 0xff) );
  mDevice->putChar( (unsigned char)(arg >> 8) );
}

void CodeWriter::writeOperation( OpCode code, short arg1, short arg2 )
{
  mDevice->putChar( code );
  mDevice->putChar( (unsigned char)(arg1 & 0xff) );
  mDevice->putChar( (unsigned char)(arg1 >> 8) );
  mDevice->putChar( (unsigned char)(arg2 & 0xff) );
  mDevice->putChar( (unsigned char)(arg2 >> 8) );
}

void CodeWriter::writeOperation( OpCode code, short arg1, short arg2, short arg3 )
{
  mDevice->putChar( code );
  mDevice->putChar( (unsigned char)(arg1 & 0xff) );
  mDevice->putChar( (unsigned char)(arg1 >> 8) );
  mDevice->putChar( (unsigned char)(arg2 & 0xff) );
  mDevice->putChar( (unsigned char)(arg2 >> 8) );
  mDevice->putChar( (unsigned char)(arg3 & 0xff) );
  mDevice->putChar( (unsigned char)(arg3 >> 8) );
}

