/* 
 * **************************************************************************
 * 
 *  file:       HistoryStateTransition.cpp
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
#include "HistoryStateTransition.h"
#include "State.h"
#include <QDebug>


/**
 * @brief HistoryStateTransition::HistoryStateTransition - create transition for
 *                        state changes that depend on history entry of checkState
 * @param eventCode   - code to request this status change
 * @param source      - source state
 * @param target      - target state
 * @param checkState  - state to check history for
 * @param shouldMatch - determines, whether checkState should be found in history
 * @param parent      - Qt parent (not used yet)
 */
HistoryStateTransition::HistoryStateTransition(int eventCode, State *source, State *target, State *checkState, bool shouldMatch, QObject *parent)
 : StateTransition(eventCode, source, target, parent)
 , check(checkState)
 , shouldMatch(shouldMatch) {
  }


HistoryStateTransition::~HistoryStateTransition() {
  }


bool HistoryStateTransition::isValid() const {
  State* source = const_cast<HistoryStateTransition*>(this)->sourceState();

  bool match = source->haveSeen(check);

  qDebug() << "\tHST::isValid() state" << check->name() << "has" << (match ? "" : "NOT") << "been seen!";

  return shouldMatch ? match : !match;
  }
