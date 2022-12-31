/* 
 * **************************************************************************
 * 
 *  file:       State.cpp
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
#include "HistoryState.h"
#include "StateTransition.h"
#include <QDebug>


State::State(const QString& name, State* parentState, QObject* parent)
 : QObject(parent)
 , stateName(name)
 , parentState(parentState)
 , predecessor(nullptr) {
  }


State::~State() {
  }


/**
 * @brief State::addTransition - simple state transitions consist of eventCode
 *                               and target state
 * @param eventCode            - the code to request this state change
 * @param state                - target state
 */
void State::addTransition(int eventCode, State* state) {
  if (!transitions.contains(eventCode))
     transitions.insert(eventCode, new StateTransition(eventCode, this, state));
  else {
     delete transitions[eventCode];
     transitions.insert(eventCode, new StateTransition(eventCode, this, state));
     }
  }


/**
 * @brief State::addTransition - extended transitions can be created and just
 *                               passed for registration
 * @param trans                - the state transition to register
 */
void State::addTransition(StateTransition* trans) {
  if (transitions.contains(trans->eventCode()))
     delete transitions[trans->eventCode()];
  transitions.insert(trans->eventCode(), trans);
  }


/**
 * @brief State::executeTransition handles state change of StateMachine
 * @param trans - the state transition to execute
 * @return      - the new state of StateMachine
 */
State* State::executeTransition(StateTransition* trans) {
  assert(trans != nullptr);

  qDebug() << "\tleave state " << trans->sourceState()->name();
  // vomits exit signal of last state
  trans->sourceState()->leaveState(trans);

  //TODO: what ever needs to be done for transition/animation/...
  HistoryState* hs = dynamic_cast<HistoryState*>(trans->targetState());

  if (hs) setSeen(hs);

  // remember state for those children, that wants to come back
  trans->targetState()->setPredecessor(this);

  qDebug() << "\tenter state " << trans->targetState()->name();
  // vomits enter signal of new state
  trans->targetState()->enterState(trans);

  return trans->targetState();
  }


/**
 * @brief State::handleEvent - lookup for transition registered for eventcode.
 *                             if this state has no transition registered for
 *                             given eventcode, its parentstate will be asked
 *                             to handle event
 * @param e                  - event to request new state
 * @return                   - transition registered for eventcode or null if
 *                             no transition matches given eventcode
 */
StateTransition* State::handleEvent(const StateRequestEvent& e) {
  if (!transitions.contains(e.code())) {
     if (parentState) {
        StateTransition* next = parentState->handleEvent(e);

        if (next) return next;
        }
     return nullptr;
     }
  return transitions[e.code()];
  }


QString State::name() const {
  return stateName;
  }


bool State::haveSeen(State *state) const {
  if (parentState) return parentState->haveSeen(state);
  return false;
  }


void State::setSeen(State* state) {
  if (parentState) parentState->setSeen(state);
  }


void State::setPredecessor(State *state) {
  predecessor = state;
  }


void State::enterState(StateTransition* trans) {
  emit onEntry(trans);
  }


void State::leaveState(StateTransition* trans) {
  emit onExit(trans);
  }
