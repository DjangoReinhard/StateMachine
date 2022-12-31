/* 
 * **************************************************************************
 * 
 *  file:       StateTransition.h
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
#ifndef STATETRANSITION_H
#define STATETRANSITION_H
#include <QObject>
class State;


/**
 * The StateTransition class describes the transition from source state to
 * target state. Default implementation returns always true for isValid()
 * Subclasses may overwrite isValid()
 */
class StateTransition : public QObject
{
  Q_OBJECT
public:
  explicit StateTransition(int eventCode, State* source, State* target, QObject* parent = nullptr);
  virtual ~StateTransition();

  virtual bool isValid() const;

  State* sourceState();
  State* targetState();
  int    eventCode() const;

private:
  int    code;
  State* source;
  State* target;
  };
#endif // STATETRANSITION_H
