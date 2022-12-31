/* 
 * **************************************************************************
 * 
 *  file:       StateMachine.h
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
#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.h"
#include <QSet>


/**
 * The StateMachine class is the event-handler for state change requests.
 * StateMachine is itself a State to serve as fallback for state change handling.
 */
class StateMachine : public State
{
public:
  StateMachine();
  virtual ~StateMachine();

  void dispatch(const StateRequestEvent& e);
  void setInitialState(State* state);

  virtual bool haveSeen(State* state) const override;
  virtual void setSeen(State* state);

  virtual QString currentState() const;

private:
  State*       current;
  QSet<State*> history;
  };
#endif
