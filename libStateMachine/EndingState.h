/*
 * **************************************************************************
 *
 *  file:       EndingState.h
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
#ifndef ENDINGSTATE_H
#define ENDINGSTATE_H
#include <State.h>


class EndingState : public State
{
public:
  explicit EndingState(int id, State* parentState = nullptr, QObject *parent = nullptr);
  explicit EndingState(int id, const QString& name, State* parentState = nullptr, QObject *parent = nullptr);
  virtual ~EndingState();
  };
#endif // ENDINGSTATE_H
