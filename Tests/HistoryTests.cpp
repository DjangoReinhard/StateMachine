/* 
 * **************************************************************************
 * 
 *  file:       HistoryTests.cpp
 *  project:    AppStateMachine
 *  subproject: unit test for history checks
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
#include <HistoryState.h>
#include <HistoryStateTransition.h>


class HistoryTests : public QObject
{
  Q_OBJECT
public:
  HistoryTests();
  ~HistoryTests();

private slots:
  void init();
  void cleanup();

  void positive_Test_should_PASS();
  void negative_Test_should_PASS();

private:
  StateMachine* sm;
  };


HistoryTests::HistoryTests() {
  }


HistoryTests::~HistoryTests() {
  }


void HistoryTests::init() {
  sm = new StateMachine();
  State* s1  = new State("S1", sm);
  State* s2  = new State("S2", sm);
  State* s21 = new State("S21", s2);
  State* s22 = new State("S22", s2);
  State* s23 = new HistoryState("S23", s2);
  State* s24 = new State("S24", s2);

  sm->setInitialState(s1);
  s1->addTransition(21, s21);
  s1->addTransition(22, s22);
  s1->addTransition(23, s23);
  s2->addTransition(1,  s1);
  HistoryStateTransition* hst = new HistoryStateTransition(24, s1, s24, s23);

  s1->addTransition(hst);
  }


void HistoryTests::cleanup() {
  delete sm;
  }


void HistoryTests::positive_Test_should_PASS() {
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(21));
  QCOMPARE(sm->currentState(), "S21");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(22));
  QCOMPARE(sm->currentState(), "S22");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(23));
  QCOMPARE(sm->currentState(), "S23");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(24));
  QCOMPARE(sm->currentState(), "S24");
  }


void HistoryTests::negative_Test_should_PASS() {
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(24));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(21));
  QCOMPARE(sm->currentState(), "S21");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(9));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(23));
  QCOMPARE(sm->currentState(), "S23");
  sm->dispatch(StateRequestEvent(1));
  QCOMPARE(sm->currentState(), "S1");
  sm->dispatch(StateRequestEvent(24));
  QCOMPARE(sm->currentState(), "S24");
  }


QTEST_APPLESS_MAIN(HistoryTests)
#include "HistoryTests.moc"
