/* 
 * **************************************************************************
 * 
 *  file:       ChildTests.cpp
 *  project:    AppStateMachine
 *  subproject: unit test for child states
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


class ChildTests : public QObject
{
  Q_OBJECT
public:
  ChildTests();
  ~ChildTests();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void positive_Test_should_PASS();
  void negative_Test_should_PASS();

private:
  StateMachine* sm;
  };


ChildTests::ChildTests() {
  }


ChildTests::~ChildTests() {
  }


void ChildTests::initTestCase() {
  sm = new StateMachine();
  State* s1  = new State("S1", sm);
  State* s2  = new State("S2", sm);
  State* s3  = new State("S3", sm);
  State* s11 = new State("S11", s1);
  State* s21 = new State("S21", s2);
  State* s31 = new State("S31", s3);

  sm->setInitialState(s11);
  s1->addTransition(21, s21);
  s2->addTransition(31, s31);
  s3->addTransition(11, s11);
  }


void ChildTests::cleanupTestCase() {
  }


void ChildTests::positive_Test_should_PASS() {
  QCOMPARE(sm->currentState()->name(), "S11");
  sm->dispatch(StateRequestEvent(21));
  QCOMPARE(sm->currentState()->name(), "S21");
  sm->dispatch(StateRequestEvent(31));
  QCOMPARE(sm->currentState()->name(), "S31");
  sm->dispatch(StateRequestEvent(11));
  QCOMPARE(sm->currentState()->name(), "S11");
  }


void ChildTests::negative_Test_should_PASS() {
  QCOMPARE(sm->currentState()->name(), "S11");
  sm->dispatch(StateRequestEvent(31));
  QCOMPARE(sm->currentState()->name(), "S11");
  sm->dispatch(StateRequestEvent(11));
  QCOMPARE(sm->currentState()->name(), "S11");
  sm->dispatch(StateRequestEvent(0));
  QCOMPARE(sm->currentState()->name(), "S11");
  sm->dispatch(StateRequestEvent(9));
  QCOMPARE(sm->currentState()->name(), "S11");
  }


QTEST_APPLESS_MAIN(ChildTests)
#include "ChildTests.moc"
