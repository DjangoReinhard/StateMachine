/* 
 * **************************************************************************
 * 
 *  file:       State.h
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
#ifndef STATE_H
#define STATE_H
#include <QObject>
#include <QString>
#include <QHash>
class StateTransition;


/**
 * The StateRequestEvent class is a simple event to request new active state
 * for StateMachine.
 */
class StateRequestEvent
{
public:
  StateRequestEvent(int code) : eventCode(code) {}

  int code() const { return eventCode; }

private:
  int eventCode;
  };


/**
 * The State class serves to define states of a StateMachine. Valid
 * Statetransitions can be registered.
 */
class State : public QObject
{
  Q_OBJECT
public:
  State(const QString& name, State* parentState = nullptr, QObject* parent = nullptr);
  virtual ~State();

  void addTransition(int st, State* targetState);
  void addTransition(StateTransition* trans);

  QString name() const;

  virtual State*           executeTransition(StateTransition* trans);
  virtual StateTransition* handleEvent(const StateRequestEvent& e);
  virtual bool             haveSeen(State* state) const;

signals:
  void onEntry(StateTransition* trans);
  void onExit(StateTransition* trans);

protected:
  bool hasChildState(State* state);
  void setPredecessor(State* state);
  virtual void enterState(StateTransition* trans);
  virtual void leaveState(StateTransition* trans);
  virtual void setSeen(State* state);
  virtual void setUnSeen(State* state);
  State*  predecessor;

private:
  QString stateName;
  State*  parentState;
  QHash<int, StateTransition*> transitions;
  };
#endif



