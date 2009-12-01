
#include "codewriter.h"

#include <QtCore/QIODevice>

CodeWriter::CodeWriter( QIODevice *device )
  : mDevice( device )
{
  mDevice->seek( 0 );
  mDevice->putChar( 0 );
  mDevice->putChar( 0 );
  mDevice->putChar( 0 );
  mDevice->putChar( 0 );
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

void CodeWriter::writeOperationAtPosition( qint64 position, OpCode code )
{
  const qint64 currentPosition = mDevice->pos();
  mDevice->seek( position );
  writeOperation( code );
  mDevice->seek( currentPosition );
}

void CodeWriter::writeOperationAtPosition( qint64 position, OpCode code, short arg )
{
  const qint64 currentPosition = mDevice->pos();
  mDevice->seek( position );
  writeOperation( code, arg );
  mDevice->seek( currentPosition );
}

void CodeWriter::writeOperationAtPosition( qint64 position, OpCode code, short arg1, short arg2 )
{
  const qint64 currentPosition = mDevice->pos();
  mDevice->seek( position );
  writeOperation( code, arg1, arg2 );
  mDevice->seek( currentPosition );
}

void CodeWriter::writeOperationAtPosition( qint64 position, OpCode code, short arg1, short arg2, short arg3 )
{
  const qint64 currentPosition = mDevice->pos();
  mDevice->seek( position );
  writeOperation( code, arg1, arg2, arg3 );
  mDevice->seek( currentPosition );
}

void CodeWriter::write( short arg )
{
  mDevice->putChar( (unsigned char)(arg & 0xff) );
  mDevice->putChar( (unsigned char)(arg >> 8) );
}

void CodeWriter::writeAtPosition( qint64 position, short arg )
{
  const qint64 currentPosition = mDevice->pos();
  mDevice->seek( position );
  mDevice->putChar( (unsigned char)(arg & 0xff) );
  mDevice->putChar( (unsigned char)(arg >> 8) );
  mDevice->seek( currentPosition );
}

qint64 CodeWriter::currentPosition() const
{
  return mDevice->pos();
}

void CodeWriter::pushLabel( qint64 position )
{
  mLabels.push( position );
}

qint64 CodeWriter::popLabel()
{
  Q_ASSERT( !mLabels.isEmpty() );

  return mLabels.pop();
}

