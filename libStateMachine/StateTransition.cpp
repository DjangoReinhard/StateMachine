/* 
 * **************************************************************************
 * 
 *  file:       StateTransition.cpp
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
#include "StateTransition.h"
#include "State.h"
#include <QDebug>


/**
 * @brief StateTransition::StateTransition describes a state transition
 * @param eventCode - the code registered to request this state change
 * @param source    - source state (only informational, is not validated yet)
 * @param target    - target state
 * @param parent    - Qt parent object (not used yet)
 */
StateTransition::StateTransition(int eventCode, State* source, State* target, QObject *parent)
 : QObject(parent)
 , code(eventCode)
 , source(source)
 , target(target) {
  }


StateTransition::~StateTransition() {
  }


int StateTransition::eventCode() const {
  return code;
  }


bool StateTransition::isValid() const {
  qDebug() << "\tStateTransition::isValid() returns true";
  return true;
  }


State* StateTransition::sourceState()  {
  return source;
  }


State* StateTransition::targetState() {
  return target;
  }
