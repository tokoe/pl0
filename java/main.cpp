#include "javaclass.h"

#include <QtCore/QFile>

int main()
{
  QFile file( "PL0.class" );
  file.open( QIODevice::WriteOnly );

  JavaClass jc;
  jc.write( &file );

  return 0;
}
