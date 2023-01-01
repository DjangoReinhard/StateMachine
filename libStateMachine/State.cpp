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
  QList<State*>* states = new QList<State*>();
  State* dst = trans->targetState();
  State* tmp = this;

  // find all ancestor states that will be left too
  while (tmp && !(tmp == dst || tmp->hasChildState(dst))) {
        states->append(tmp);
        tmp = tmp->parentState;
        }
  // vomit signals for all left states
  for (int i=0; i < states->size(); ++i) {
      qDebug() << "\tleave state " << states->at(i)->name();
      states->at(i)->leaveState(trans);
      }
  states->clear();

  /*
   * real transition processing ...
   */
  HistoryState* hs = dynamic_cast<HistoryState*>(trans->targetState());

  if (hs) setSeen(hs);
  // remember state for those children, that wants to come back
  trans->targetState()->setPredecessor(this);


  //TODO: what ever needs to be done for transition/animation/...


  /*
   * find all states between targetState and common ancestor
   */
  State* ancestor = tmp;

  tmp = dst;
  while (tmp != ancestor) {
        states->append(tmp);
        tmp = tmp->parentState;
        }
  for (int i=states->size() - 1; i >= 0; --i) {
      qDebug() << "\tenter state " << states->at(i)->name();
      // vomits enter signal of each new state
      states->at(i)->enterState(trans);
      }
  delete states;

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


/**
 * @brief State::hasChildState - determines, whether given state is a child state
 *                               of this state
 * @param   state - state to check
 * @return  true if state is descendant of ourself
 */
bool State::hasChildState(State *state) {
  if (!state) return false;
  State* tmp = state;

  while ((tmp = tmp->parentState)) {
        if (tmp == this) return true;
        }
  return false;
  }


QString State::name() const {
  return stateName;
  }


bool State::haveSeen(State *state) const {
  //route function call to StateMachine
  if (parentState) return parentState->haveSeen(state);
  return false;
  }


void State::setPredecessor(State *state) {
  predecessor = state;
  }


void State::setSeen(State* state) {
  //route function call to StateMachine
  if (parentState) parentState->setSeen(state);
  }


void State::setUnSeen(State* state) {
  //route function call to StateMachine
  if (parentState) parentState->setUnSeen(state);
  }

void State::enterState(StateTransition* trans) {
  emit onEntry(trans);
  }


void State::leaveState(StateTransition* trans) {
  emit onExit(trans);
  }
