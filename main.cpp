
#include "parser.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>

int main( int argc, char **argv )
{

  if ( argc != 3 ) {
    qDebug() << "usage: pl0 <source> <destination>";
    return 1;
  }

  QFile inputFile( argv[ 1 ] );
  if ( !inputFile.open( QIODevice::ReadOnly ) ) {
    qDebug() << "Unable to open file" << inputFile.fileName() << "for reading.";
    return 2;
  }

  QFile outputFile( argv[ 2 ] );
  if ( !outputFile.open( QIODevice::WriteOnly ) ) {
    qDebug() << "Unable to open file" << outputFile.fileName() << "for writing.";
    return 3;
  }

//#define TOKENIZER 1

#ifdef TOKENIZER
  Tokenizer tokenizer;
  tokenizer.load(&inputFile);

  Token token = tokenizer.nextToken();
  while (token.type() != Token::EndToken) {
    qDebug() << token;
    tokenizer.tokenProcessed();
    token = tokenizer.nextToken();
  }
  return 0;

#else
  Parser parser;
//  parser.outputGraphs();
  parser.load( &inputFile );

  if ( parser.parse( &outputFile ) ) {
    qDebug() << "Program valid";
    return 0;
  } else {
    qDebug() << "Program invalid:" << parser.errorText();
    return 1;
  }
#endif
}
