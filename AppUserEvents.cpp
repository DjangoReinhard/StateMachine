/* 
 * **************************************************************************
 * 
 *  file:       AppUserEvents.cpp
 *  project:    AppStateMachine
 *  subproject: main application
 *  purpose:    sample for hierarchic state machine with history support
 *  created:    6.1.2023 by Django Reinhard
 *  copyright:  (c) 2022 - 2023 Django Reinhard -  all rights reserved
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
#include <AppUserEvents.h>
#define CASE(s) case s: return #s


QString SIAppUserEvents::toString(AppUserEvents v) {
  switch (v) {
    CASE(NOPAction);
    CASE(ErrorSTATE);
    CASE(MachineSetup);
    CASE(HALInfo);
    }
  return "";
  }

#define CHECK(v) if (s == #v) return v

AppUserEvents SIAppUserEvents::parse(const QString& s) {
  CHECK(NOPAction);
  CHECK(ErrorSTATE);
  CHECK(MachineSetup);
  CHECK(HALInfo);
  return NOPAction;
  }
