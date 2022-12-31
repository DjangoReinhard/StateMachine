/* 
 * **************************************************************************
 * 
 *  file:       StateMachine.cpp
 *  project:    AppStateMachine
 *  subproject: statemachine library
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
#include "StateMachine.h"
#include "StateTransition.h"
#include <QDebug>
#include <stdexcept>


StateMachine::StateMachine()
 : State("StateMachine")
 , current(nullptr) {
  current = this;
  }


StateMachine::~StateMachine() {
  }


QString StateMachine::currentState() const {
  return current->name();
  }


void StateMachine::setInitialState(State* s) {
  current = s;
  }


bool StateMachine::haveSeen(State *state) const {
  bool rv = history.contains(state);

  qDebug() << "\tstate" << state->name() << "has" << (rv ? "" : "NOT") << "been seen";
  return rv;
  }


void StateMachine::setSeen(State *state) {
  qDebug() << "\tremember state" << state->name() << "as seen!";
  history.insert(state);
  }


void StateMachine::dispatch(const StateRequestEvent& e) {
  if (!current) throw std::logic_error("missing state!");

  qDebug() << "event #" << e.code() << "received at state \"" << current->name() << "\"";

  StateTransition* next = current->handleEvent(e);

  if (next && next->eventCode() == e.code()) {
     const QString& n0 = next->targetState()->name();
     const QString& n1 = current->name();
     bool check = next->isValid();

     if (n0 != n1 && check) current = current->executeTransition(next);
     }
  predecessor = nullptr; // as StateMachine is a State as well, ensure, that we
                         // never have a predecessor!

  qDebug() << "after event-processing, state is now \"" << current->name() << "\"";
  }