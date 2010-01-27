
#include "javaclass.h"

#include <QtCore/QFile>

ConstPoolEntry::ConstPoolEntry( Tag tag )
  : mTag( tag )
{
}

ConstPoolEntry::~ConstPoolEntry()
{
}

ConstPoolEntry::Tag ConstPoolEntry::tag() const
{
  return mTag;
}

FieldInfo::FieldInfo( char accessFlags, quint16 nameIndex, quint16 descriptorIndex )
  : mAccessFlags( accessFlags ), mNameIndex( nameIndex ), mDescriptorIndex( descriptorIndex )
{
}

FieldInfo::~FieldInfo()
{
  qDeleteAll( mAttributes );
}

void FieldInfo::write( QIODevice *device )
{
  // write access flags
  device->putChar( 0x00 );
  device->putChar( mAccessFlags );

  // write name index
  JavaClass::writeShort( device, mNameIndex );

  // write descriptor index
  JavaClass::writeShort( device, mDescriptorIndex );

  // write number of attributes
  JavaClass::writeShort( device, mAttributes.count() );

  // write attributes
  for ( int i = 0; i < mAttributes.count(); ++i ) {
    mAttributes.at( i )->write( device );
  }
}

MethodInfo::MethodInfo( quint16 accessFlags, quint16 nameIndex, quint16 descriptorIndex )
  : mAccessFlags( accessFlags ), mNameIndex( nameIndex ), mDescriptorIndex( descriptorIndex )
{
}

MethodInfo::~MethodInfo()
{
  qDeleteAll( mAttributes );
}

void MethodInfo::write( QIODevice *device )
{
  // write access flags
  JavaClass::writeShort( device, mAccessFlags );

  // write name index
  JavaClass::writeShort( device, mNameIndex );

  // write descriptor index
  JavaClass::writeShort( device, mDescriptorIndex );

  // write number of attributes
  JavaClass::writeShort( device, mAttributes.count() );

  // write attributes
  for ( int i = 0; i < mAttributes.count(); ++i ) {
    mAttributes.at( i )->write( device );
  }
}

ClassConstPoolEntry::ClassConstPoolEntry( quint16 nameIndex )
  : ConstPoolEntry( Class ), mNameIndex( nameIndex )
{
}

void ClassConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write name index
  JavaClass::writeShort( device, mNameIndex );
}

FieldReferenceConstPoolEntry::FieldReferenceConstPoolEntry( quint16 classIndex, quint16 nameTypeIndex )
  : ConstPoolEntry( FieldReference ), mClassIndex( classIndex ), mNameTypeIndex( nameTypeIndex )
{
}

void FieldReferenceConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write class index
  JavaClass::writeShort( device, mClassIndex );

  // write name and type index
  JavaClass::writeShort( device, mNameTypeIndex );
}


MethodReferenceConstPoolEntry::MethodReferenceConstPoolEntry( quint16 classIndex, quint16 nameTypeIndex )
  : ConstPoolEntry( MethodReference ), mClassIndex( classIndex ), mNameTypeIndex( nameTypeIndex )
{
}

void MethodReferenceConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write class index
  JavaClass::writeShort( device, mClassIndex );

  // write name and type index
  JavaClass::writeShort( device, mNameTypeIndex );
}

InterfaceMethodReferenceConstPoolEntry::InterfaceMethodReferenceConstPoolEntry( quint16 classIndex, quint16 nameTypeIndex )
  : ConstPoolEntry( InterfaceMethodReference ), mClassIndex( classIndex ), mNameTypeIndex( nameTypeIndex )
{
}

void InterfaceMethodReferenceConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write class index
  JavaClass::writeShort( device, mClassIndex );

  // write name and type index
  JavaClass::writeShort( device, mNameTypeIndex );
}

StringConstPoolEntry::StringConstPoolEntry( quint16 stringIndex )
  : ConstPoolEntry( String ), mStringIndex( stringIndex )
{
}

void StringConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write string index
  JavaClass::writeShort( device, mStringIndex );
}

IntegerConstPoolEntry::IntegerConstPoolEntry( quint32 value )
  : ConstPoolEntry( Integer ), mValue( value )
{
}

void IntegerConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write value
  JavaClass::writeInt( device, mValue );
}

NameAndTypeConstPoolEntry::NameAndTypeConstPoolEntry( quint16 nameIndex, quint16 descriptorIndex )
  : ConstPoolEntry( NameAndType ), mNameIndex( nameIndex ), mDescriptorIndex( descriptorIndex )
{
}

void NameAndTypeConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  // write name index
  JavaClass::writeShort( device, mNameIndex );

  // write descriptor index
  JavaClass::writeShort( device, mDescriptorIndex );
}

Utf8ConstPoolEntry::Utf8ConstPoolEntry( const QString &value )
  : ConstPoolEntry( Utf8 ), mValue( value )
{
}

void Utf8ConstPoolEntry::write( QIODevice *device )
{
  // write tag
  device->putChar( (char)tag() );

  const QByteArray data = mValue.toUtf8();

  // write length
  JavaClass::writeShort( device, data.length() );

  // write bytes
  device->write( data );
}

ConstValueAttribute::ConstValueAttribute( quint16 nameIndex, quint16 valueIndex )
  : mNameIndex( nameIndex ), mValueIndex( valueIndex )
{
}

void ConstValueAttribute::write( QIODevice *device )
{
  // write attribute name index
  JavaClass::writeShort( device, mNameIndex );

  // write attribute length
  JavaClass::writeInt( device, 2 );

  // write attribute value index
  JavaClass::writeShort( device, mValueIndex );
}

CodeAttribute::CodeAttribute( quint16 nameIndex, quint16 maxStack, quint16 maxLocals, const QByteArray &code )
  : mNameIndex( nameIndex ), mMaxStack( maxStack ), mMaxLocals( maxLocals ), mCode( code )
{
}

void CodeAttribute::write( QIODevice *device )
{
  // write attribute name index
  JavaClass::writeShort( device, mNameIndex );

  // write attribute length
  const quint32 length =   2 // max_stack
                         + 2 // max_locals
                         + 4 // code_length
                         + mCode.length() // code data length
                         + 2 // exception table length
                         + 2; // attributes count

  JavaClass::writeInt( device, length );

  // write max stack
  JavaClass::writeShort( device, mMaxStack );

  // write max locals
  JavaClass::writeShort( device, mMaxLocals );

  // write code length
  JavaClass::writeInt( device, mCode.length() );

  // write code
  device->write( mCode );

  // write exception table length
  JavaClass::writeShort( device, 0x0000 );

  // write attributes count
  JavaClass::writeShort( device, 0x0000 );
}


JavaClass::JavaClass()
{
}

JavaClass::~JavaClass()
{
  qDeleteAll( mFields );
  qDeleteAll( mMethods );
  qDeleteAll( mAttributes );
}

quint16 JavaClass::addConst( ConstPoolEntry *entry )
{
  const quint16 index = mConstPool.count() + 1;
  mConstPool.append( entry );

  return index;
}

void JavaClass::writeShort( QIODevice *device, quint16 value )
{
  device->putChar( (unsigned char)(value >> 8) );
  device->putChar( (unsigned char)(value & 0xff) );
}

void JavaClass::writeInt( QIODevice *device, quint32 value )
{
  device->putChar( (unsigned char)(value >> 24) );
  device->putChar( (unsigned char)((value & 0x00ff) >> 16) );
  device->putChar( (unsigned char)((value & 0x0000ff) >> 8) );
  device->putChar( (unsigned char)(value & 0x000000ff) );
}

void JavaClass::write( QIODevice *device )
{
  // initialize encapsulation class

  const quint16 thisClassNameIndex = addConst( new Utf8ConstPoolEntry( "PL0" ) );
  const quint16 superClassNameIndex = addConst( new Utf8ConstPoolEntry( "java/lang/Object" ) );
  const quint16 thisClassIndex = addConst( new ClassConstPoolEntry( thisClassNameIndex ) );
  const quint16 superClassIndex = addConst( new ClassConstPoolEntry( superClassNameIndex ) );

  const quint16 initNameIndex = addConst( new Utf8ConstPoolEntry( "<init>" ) );
  const quint16 initDescriptorIndex = addConst( new Utf8ConstPoolEntry( "()V" ) );

  const quint16 codeAttributeNameIndex = addConst( new Utf8ConstPoolEntry( "Code" ) );
  const quint16 mainNameIndex = addConst( new Utf8ConstPoolEntry( "main" ) );
  const quint16 mainArgDescription = addConst( new Utf8ConstPoolEntry( "([Ljava/lang/String;)V" ) );

  // write magic code
  device->putChar( 0xCA );
  device->putChar( 0xFE );
  device->putChar( 0xBA );
  device->putChar( 0xBE );

  // write major number
  device->putChar( 0x00 );
  device->putChar( 0x00 );

  // write minor number
  device->putChar( 0x00 );
  device->putChar( 0x32 );

  // write const pool
  JavaClass::writeShort( device, mConstPool.count() + 1 );

  for ( int i = 0; i < mConstPool.count(); ++i )
    mConstPool.at( i )->write( device );

  // write access flags
  device->putChar( 0x00 );
  device->putChar( 0x21 ); // super | public

  // write this class index
  JavaClass::writeShort( device, thisClassIndex );

  // write super class index
  JavaClass::writeShort( device, superClassIndex );

  // write interface count (always 0 for us)
  JavaClass::writeShort( device, 0x0000 );

  // write interface array (can be omitted since always 0)

  // write fields count
  JavaClass::writeShort( device, mFields.count() );

  // write field array
  for ( int i = 0; i < mFields.count(); ++i ) {
    mFields.at( i )->write( device );
  }

  // write methods count
  JavaClass::writeShort( device, mMethods.count() );

  // write method array
  for ( int i = 0; i < mMethods.count(); ++i ) {
    mMethods.at( i )->write( device );
  }

  // write attributes count
  JavaClass::writeShort( device, mAttributes.count() );

  // write attributes array
  for ( int i = 0; i < mAttributes.count(); ++i ) {
    mAttributes.at( i )->write( device );
  }
}
