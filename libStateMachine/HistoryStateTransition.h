/* 
 * **************************************************************************
 * 
 *  file:       HistoryStateTransition.h
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
#ifndef HISTORYSTATETRANSITION_H
#define HISTORYSTATETRANSITION_H
#include "StateTransition.h"
class State;


/**
 * The HistoryStateTransition class creates state transitions that check history
 * for given state.
 */
class HistoryStateTransition : public StateTransition
{
public:
  HistoryStateTransition(int eventCode, State* source, State* target, State* checkState, bool shouldMatch = true, QObject* parent = nullptr);
  virtual ~HistoryStateTransition();

  virtual bool isValid() const override;

protected:
  State* checkState();

private:
  bool   shouldMatch;
  State* check;
  };
#endif // HISTORYSTATETRANSITION_H
