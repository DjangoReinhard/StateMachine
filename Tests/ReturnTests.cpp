/* 
 * **************************************************************************
 * 
 *  file:       OrphanTests.cpp
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
#include <OrphanState.h>
#include <ReturnState.h>


class ReturnTests : public QObject
{
  Q_OBJECT
public:
  ReturnTests();
  ~ReturnTests();

private slots:
  void init();
  void cleanup();

  void positive_Test_should_PASS();

private:
  StateMachine* sm;
  };


ReturnTests::ReturnTests() {
  }


ReturnTests::~ReturnTests() {
  }


void ReturnTests::init() {
  sm = new StateMachine();
  State* s1   = new State(1, "S1", sm);
  State* s2   = new State(2, "S2", sm);
  State* s3   = new State(3, "S3", sm);
  State* s11  = new ReturnState(11, "S11", s1);
  State* s21  = new ReturnState(21, "S21", s2);
  State* s31  = new State(31, "S31", s3);
  State* s311 = new State(311, "S311", s31);
  State* s211 = new State(211, "S211", s21);

  sm->setInitialState(s1);
  s1->addTransition(s11);
  s1->addTransition(s21);
  s1->addTransition(s31);
  s2->addTransition(s11);
  s2->addTransition(s21);
  s2->addTransition(s31);
  s2->addTransition(s211);
  s2->addTransition(s311);
  s3->addTransition(s11);
  s3->addTransition(s21);
  s3->addTransition(s31);
  s3->addTransition(s311);
  s3->addTransition(s211);
  }


void ReturnTests::cleanup() {
  }


void ReturnTests::positive_Test_should_PASS() {
  QCOMPARE(sm->currentState()->name(), "S1");
  sm->dispatch(StateRequestEvent(31));
  QCOMPARE(sm->currentState()->name(), "S31");
  sm->dispatch(StateRequestEvent(311));
  QCOMPARE(sm->currentState()->name(), "S311");
  // from 311 to 211 works, as 311 is normal state
  sm->dispatch(StateRequestEvent(211));
  QCOMPARE(sm->currentState()->name(), "S211");
  // from 211 to 311 fails, as return state is an orphaned state and thus
  // does not care for parent transition definitions
  sm->dispatch(StateRequestEvent(311));
  QCOMPARE(sm->currentState()->name(), "S211");
  // stateReturn leaves return state (s21) and s2 has transition definition to s311
  sm->stateReturn();
  QCOMPARE(sm->currentState()->name(), "S2");
  sm->dispatch(StateRequestEvent(311));
  QCOMPARE(sm->currentState()->name(), "S311");
  }


QTEST_APPLESS_MAIN(ReturnTests)
#include "ReturnTests.moc"
