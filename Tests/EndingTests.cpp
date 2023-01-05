/* 
 * **************************************************************************
 * 
 *  file:       EndingTests.cpp
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
#include <EndingState.h>


class EndingTests : public QObject
{
  Q_OBJECT
public:
  EndingTests();
  ~EndingTests();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void positive_Test_should_PASS();

private:
  StateMachine* sm;
  };


EndingTests::EndingTests() {
  }


EndingTests::~EndingTests() {
  }


void EndingTests::initTestCase() {
  sm = new StateMachine();
  State* s1   = new State(1, "S1", sm);
  State* s2   = new State(2, "S2", sm);
  State* s11  = new State(11, "S11", s1);
  State* s21  = new State(21, "S21", s2);
  State* s211 = new State(211, "S211", s21);
  State* s212 = new EndingState(212, "S212", s21);

  sm->setInitialState(s11);
  s1->addTransition(21, s21);
  s21->addTransition(211, s211);
  s211->addTransition(212, s212);
  }


void EndingTests::cleanupTestCase() {
  }


void EndingTests::positive_Test_should_PASS() {
  QCOMPARE(sm->currentState()->name(), "S11");
  sm->dispatch(StateRequestEvent(21));
  QCOMPARE(sm->currentState()->name(), "S21");
  sm->dispatch(StateRequestEvent(211));
  QCOMPARE(sm->currentState()->name(), "S211");
  sm->dispatch(StateRequestEvent(212));
  QCOMPARE(sm->currentState()->name(), "S21");
  }



QTEST_APPLESS_MAIN(EndingTests)
#include "EndingTests.moc"
