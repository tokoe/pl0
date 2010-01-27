#ifndef JAVACLASS_H
#define JAVACLASS_H

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QStringList>

class QIODevice;

class AttributeInfo
{
  public:
    virtual ~AttributeInfo() {};
    virtual void write( QIODevice *device ) = 0;
};

class FieldInfo
{
  public:
    enum AccessFlags
    {
      Public = 0x01,
      Private = 0x02,
      Protected = 0x04,
      Static = 0x08,
      Final = 0x10,
      Volatile = 0x40,
      Transient = 0x80
    };

    FieldInfo( char accessFlags, quint16 nameIndex, quint16 descriptorIndex );
    ~FieldInfo();

    void write( QIODevice *device );

  private:
    char mAccessFlags;
    quint16 mNameIndex;
    quint16 mDescriptorIndex;
    QList<AttributeInfo*> mAttributes;
};

class MethodInfo
{
  public:
    enum AccessFlags
    {
      Public = 0x0001,
      Private = 0x0002,
      Protected = 0x0004,
      Static = 0x0008,
      Final = 0x0010,
      Synchronized = 0x0020,
      Native = 0x0100,
      Abstract = 0x0400,
      Strict = 0x0800
    };

    MethodInfo( quint16 accessFlags, quint16 nameIndex, quint16 descriptorIndex );
    ~MethodInfo();

    void write( QIODevice *device );

  private:
    char mAccessFlags;
    quint16 mNameIndex;
    quint16 mDescriptorIndex;
    QList<AttributeInfo*> mAttributes;
};

class ConstPoolEntry
{
  public:
    enum Tag
    {
      Utf8 = 1,
      Integer = 3,
      Float = 4, // unused
      Long = 5, // unused
      Double = 6, // unused
      Class = 7,
      String = 8,
      FieldReference = 9,
      MethodReference = 10,
      InterfaceMethodReference = 11,
      NameAndType = 12
    };

    ConstPoolEntry( Tag tag );
    ~ConstPoolEntry();

    virtual void write( QIODevice *device ) = 0;

    Tag tag() const;

  private:
    Tag mTag;
};

class ClassConstPoolEntry : public ConstPoolEntry
{
  public:
    ClassConstPoolEntry( quint16 nameIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mNameIndex;
};

class FieldReferenceConstPoolEntry : public ConstPoolEntry
{
  public:
    FieldReferenceConstPoolEntry( quint16 classIndex, quint16 nameTypeIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mClassIndex;
    quint16 mNameTypeIndex;
};

class MethodReferenceConstPoolEntry : public ConstPoolEntry
{
  public:
    MethodReferenceConstPoolEntry( quint16 classIndex, quint16 nameTypeIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mClassIndex;
    quint16 mNameTypeIndex;
};

class InterfaceMethodReferenceConstPoolEntry : public ConstPoolEntry
{
  public:
    InterfaceMethodReferenceConstPoolEntry( quint16 classIndex, quint16 nameTypeIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mClassIndex;
    quint16 mNameTypeIndex;
};

class StringConstPoolEntry : public ConstPoolEntry
{
  public:
    StringConstPoolEntry( quint16 stringIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mStringIndex;
};

class IntegerConstPoolEntry : public ConstPoolEntry
{
  public:
    IntegerConstPoolEntry( quint32 value );

    virtual void write( QIODevice *device );

  private:
    quint32 mValue;
};

class NameAndTypeConstPoolEntry : public ConstPoolEntry
{
  public:
    NameAndTypeConstPoolEntry( quint16 nameIndex, quint16 descriptorIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mNameIndex;
    quint16 mDescriptorIndex;
};

class Utf8ConstPoolEntry : public ConstPoolEntry
{
  public:
    Utf8ConstPoolEntry( const QString &value );

    virtual void write( QIODevice *device );

  private:
    QString mValue;
};

class ConstValueAttribute : public AttributeInfo
{
  public:
    ConstValueAttribute( quint16 nameIndex, quint16 valueIndex );

    virtual void write( QIODevice *device );

  private:
    quint16 mNameIndex;
    quint16 mValueIndex;
};

class CodeAttribute : public AttributeInfo
{
  public:
    CodeAttribute( quint16 nameIndex, quint16 maxStack, quint16 maxLocals, const QByteArray &code );

    virtual void write( QIODevice *device );

  private:
    quint16 mNameIndex;
    quint16 mMaxStack;
    quint16 mMaxLocals;
    QByteArray mCode;
};

class JavaClass
{
  public:
    JavaClass();
    ~JavaClass();

    quint16 addConst( ConstPoolEntry *entry );

    void write( QIODevice *device );

    static void writeShort( QIODevice *device, quint16 value );
    static void writeInt( QIODevice *device, quint32 value );

  private:
    QList<ConstPoolEntry*> mConstPool;
    QList<FieldInfo*> mFields;
    QList<MethodInfo*> mMethods;
    QList<AttributeInfo*> mAttributes;
};

#endif
