/* 
 * **************************************************************************
 * 
 *  file:       AppUserEvents.h
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
#ifndef APPUSEREVENTS_H
#define APPUSEREVENTS_H
#include <QString>


enum AppUserEvents
{
  NOPAction
, ErrorSTATE
, EmergencySTOP
, PowerOFF
, MachineEnabled
, EditJob
, JobChanged
, EditFile
, FileChanged
, OpenFile
, Search
, SearchReplace
, Save
, Exit
, Setup
, ApplicationSetup
, MachineSetup
, Fixtures
, ToolTable
, ATC
, View
, HALInfo
, ToolManager
, HomeAllAxis
, JobProcessing
, ManualCommands
, ManualMoves
, ManualJog
, WheelJog
, MeasureTouch
, ShowMessages
, JobRunning
, JobPaused
, JobFinished
, Jogging
, ActiveAxis
, StepSize
, ContinuousJogging
, SingleStep
, FloodCooling
, MistCooling
, SpindleCCW
, SpindleCW
, SpindleStop
, AbsolutePosition
, RelativePosition
  };

class SIAppUserEvents
{
public:
  static QString       toString(AppUserEvents v);
  static AppUserEvents parse(const QString& s);
  };
#endif
