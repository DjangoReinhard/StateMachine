/* 
 * **************************************************************************
 * 
 *  file:       BasicsTests.cpp
 *  project:    AppStateMachine
 *  subproject: unit test for basics
 *  purpose:    sample for hierarchic state machine with history support
 *  created:    31.12.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#include <QtTest>
#include <StateMachine.h>
#include <State.h>


class BasicsTests : public QObject
{
  Q_OBJECT
public:
  BasicsTests();
  ~BasicsTests();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void positive_Test_should_PASS();
  void negative_Test_should_PASS();

private:
  StateMachine* sm;
  };


BasicsTests::BasicsTests() {
  }


BasicsTests::~BasicsTests() {
  }


void BasicsTests::initTestCase() {
  sm = new StateMachine();
  State* s1 = new State(1, "S1", sm);
  State* s2 = new State(2, "S2", sm);
  State* s3 = new State(3, "S3", sm);

  sm->setInitialState(s1);
  s1->addTransition(2, s2);
  s2->addTransition(3, s3);
  s3->addTransition(1, s1);
  }


void BasicsTests::cleanupTestCase() {
  }


void BasicsTests::positive_Test_should_PASS() {
  QCOMPARE(sm->currentState()->name(), "S1");
  sm->dispatch(StateRequestEvent(2));
  QCOMPARE(sm->currentState()->name(), "S2");
  sm->dispatch(StateRequestEvent(3));
  QCOMPARE(sm->currentState()->name(), "S3");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState()->name(), "S1");
  }


void BasicsTests::negative_Test_should_PASS() {
  QCOMPARE(sm->currentState()->name(), "S1");
  sm->dispatch(StateRequestEvent(3));
  QCOMPARE(sm->currentState()->name(), "S1");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState()->name(), "S1");
  sm->dispatch(StateRequestEvent(0));
  QCOMPARE(sm->currentState()->name(), "S1");
  sm->dispatch(StateRequestEvent(9));
  QCOMPARE(sm->currentState()->name(), "S1");
  }


QTEST_APPLESS_MAIN(BasicsTests)
#include "BasicsTests.moc"
