#include <QtTest/QtTest>

#include "../identifiermanager.h"

class TestIdentifierManager : public QObject
{
  Q_OBJECT

  private Q_SLOTS:
    void testVariables();
    void testConsts();
    void testProcedures();
    void testNestedProcedures();
};


void TestIdentifierManager::testVariables()
{
  IdentifierManager manager;

  manager.setName( "a" );
  manager.pushVariableIdentifier();
  manager.setName( "b" );
  manager.pushVariableIdentifier();
  manager.setName( "c" );
  manager.pushVariableIdentifier();

  QVERIFY( manager.hasVariableIdentifier( "a" ) );
  QVERIFY( manager.hasVariableIdentifier( "b" ) );
  QVERIFY( manager.hasVariableIdentifier( "c" ) );
  QVERIFY( !manager.hasVariableIdentifier( "A" ) );
  QVERIFY( !manager.hasVariableIdentifier( "B" ) );
  QVERIFY( !manager.hasVariableIdentifier( "C" ) );
  QVERIFY( !manager.hasVariableIdentifier( "d" ) );
  QVERIFY( !manager.hasVariableIdentifier( "D" ) );

  QVERIFY( !manager.hasConstIdentifier( "a" ) );
  QVERIFY( !manager.hasProcedureIdentifier( "a" ) );
}

void TestIdentifierManager::testConsts()
{
  IdentifierManager manager;

  manager.setName( "a" );
  manager.setValue( 10 );
  manager.pushConstIdentifier();
  manager.setName( "b" );
  manager.setValue( 20 );
  manager.pushConstIdentifier();
  manager.setName( "c" );
  manager.setValue( 30 );
  manager.pushConstIdentifier();

  QVERIFY( manager.hasConstIdentifier( "a" ) );
  QVERIFY( manager.hasConstIdentifier( "b" ) );
  QVERIFY( manager.hasConstIdentifier( "c" ) );
  QVERIFY( !manager.hasConstIdentifier( "A" ) );
  QVERIFY( !manager.hasConstIdentifier( "B" ) );
  QVERIFY( !manager.hasConstIdentifier( "C" ) );
  QVERIFY( !manager.hasConstIdentifier( "d" ) );
  QVERIFY( !manager.hasConstIdentifier( "D" ) );

  QVERIFY( !manager.hasVariableIdentifier( "a" ) );
  QVERIFY( !manager.hasProcedureIdentifier( "a" ) );
}

void TestIdentifierManager::testProcedures()
{
  IdentifierManager manager;

  manager.setName( "constA" );
  manager.setValue( 10 );
  manager.pushConstIdentifier();
  manager.setName( "constB" );
  manager.setValue( 20 );
  manager.pushConstIdentifier();
  manager.setName( "varA" );
  manager.pushVariableIdentifier();

  manager.setName( "proc1" );
  manager.pushProcedure();

  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );

  manager.setName( "proc1constA" );
  manager.setValue( 10 );
  manager.pushConstIdentifier();
  
  manager.setName( "proc1varA" );
  manager.pushVariableIdentifier();

  QVERIFY( manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( manager.hasVariableIdentifier( "proc1varA" ) );
  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );

  manager.endProcedure();

  QVERIFY( !manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( !manager.hasVariableIdentifier( "proc1varA" ) );

  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );
}

void TestIdentifierManager::testNestedProcedures()
{
  IdentifierManager manager;

  manager.setName( "constA" );
  manager.setValue( 10 );
  manager.pushConstIdentifier();
  manager.setName( "constB" );
  manager.setValue( 20 );
  manager.pushConstIdentifier();
  manager.setName( "varA" );
  manager.pushVariableIdentifier();

  manager.setName( "proc1" );
  manager.pushProcedure();

  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );

  manager.setName( "proc1constA" );
  manager.setValue( 10 );
  manager.pushConstIdentifier();
  
  manager.setName( "proc1varA" );
  manager.pushVariableIdentifier();

  QVERIFY( manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( manager.hasVariableIdentifier( "proc1varA" ) );
  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );

  manager.setName( "proc2" );
  manager.pushProcedure();

  QVERIFY( manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( manager.hasVariableIdentifier( "proc1varA" ) );
  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc2" ) );

  manager.setName( "proc2constA" );
  manager.setValue( 10 );
  manager.pushConstIdentifier();
  
  manager.setName( "proc2varA" );
  manager.pushVariableIdentifier();

  QVERIFY( manager.hasConstIdentifier( "proc2constA" ) );
  QVERIFY( manager.hasVariableIdentifier( "proc2varA" ) );
  QVERIFY( manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( manager.hasVariableIdentifier( "proc1varA" ) );
  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc2" ) );

  manager.endProcedure();

  QVERIFY( !manager.hasConstIdentifier( "proc2constA" ) );
  QVERIFY( !manager.hasVariableIdentifier( "proc2varA" ) );

  QVERIFY( manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( manager.hasVariableIdentifier( "proc1varA" ) );
  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc2" ) );

  manager.endProcedure();

  QVERIFY( !manager.hasConstIdentifier( "proc1constA" ) );
  QVERIFY( !manager.hasVariableIdentifier( "proc1varA" ) );
  QVERIFY( !manager.hasProcedureIdentifier( "proc2" ) );

  QVERIFY( manager.hasConstIdentifier( "constA" ) );
  QVERIFY( manager.hasConstIdentifier( "constB" ) );
  QVERIFY( manager.hasVariableIdentifier( "varA" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );

  manager.setName( "proc3" );
  manager.pushProcedure();
  manager.endProcedure();

  QVERIFY( manager.hasProcedureIdentifier( "proc1" ) );
  QVERIFY( manager.hasProcedureIdentifier( "proc3" ) );
}

QTEST_MAIN(TestIdentifierManager)
#include "testidentifiermanager.moc"
