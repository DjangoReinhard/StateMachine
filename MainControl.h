/*
 * **************************************************************************
 *
 *  file:       maincontrol.h
 *  project:    AppStateMachine
 *  subproject: main application
 *  purpose:    sample for hierarchic state machine with history support
 *  created:    30.12.2022 by Django Reinhard
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
#ifndef MAINCONTROL_H
#define MAINCONTROL_H
#include <QObject>
#include <QHash>
#include <QThread>
class MultiStateAction;
class IApplicationPage;
class PluginHandler;
class State;
class StateMachine;
class ToolBar;
class QAction;


class MainControl : public QObject
{
  Q_OBJECT
public:
  explicit MainControl(QObject *parent = nullptr);
  virtual ~MainControl();

  virtual void start(bool startThread = false);
  StateMachine* stateMachine();
  QHash<int, MultiStateAction*>* actions();
  void setToolBar(ToolBar* tb);

public slots:
  void enterApplicationSetup();
  void enterATC();
  void enterEditFile();
  void enterEditJob();
  void enterEmergencySTOP();
  void enterErrorState();
  void enterFixtures();
  void enterHalInfo();
  void enterHomeAllAxis();
  void enterJobFinished();
  void enterJobPaused();
  void enterJobProcessing();
  void enterJobRunning();
  void enterMachineEnabled();
  void enterMachineSetup();
  void enterManualCommands();
  void enterManualJog();
  void enterManualMoves();
  void enterMeasureTouch();
  void enterSetup();
  void enterShowMessages();
  void enterToolManager();
  void enterToolTable();
  void enterWheelJog();

  void exitApplicationSetup();
  void exitATC();
  void exitEditFile();
  void exitEditJob();
  void exitFixtures();
  void exitHalInfo();
  void exitJobPaused();
  void exitJobProcessing();
  void exitMachineSetup();
  void exitManualCommands();
  void exitManualMoves();
  void exitMeasureTouch();
  void exitSetup();
  void exitToolManager();
  void exitToolTable();
  void exitWheelJog();

  void handleEmergencySTOP();
  void handleEditJob();
  void handleEditFile();
  void handleOpenFile();
  void handleSearch();
  void handleSave();
  void handleExit();
  void handleSetup();
  void handleApplicationSetup();
  void handleMachineSetup();
  void handleHALInfo();
  void handleFixtures();
  void handleView();
  void handleJobPaused();
  void handleJobRunning();
  void handleJobFinished();
  void handleJobProcessing();
  void handleAbsolutePosition();
  void handleATC();
  void handleActiveAxis();
  void handleContinuousJogging();
  void handleStepSize();
  void handleFloodCooling();
  void handleMistCooling();
  void handleHomeAllAxis();
  void handleManualCommands();
  void handleManualJog();
  void handleShowMessages();
  void handleSingleStep();
  void handleSpindleCCW();
  void handleSpindleCW();
  void handleSpindleStop();
  void handleToolManager();
  void handleToolTable();
  void handleMeasureTouch();
  void handleWheelJog();

  void handleEndOfCounter();

protected:
  void createActions();
  void createStateMachine();
  void connectStates();
  void updateToolbar(int actionCodes[]);

private:
  QList<IApplicationPage*> plugins;
  QHash<int, MultiStateAction*>* actionMap;
  QList<QWidget*>* tbButtons;
  QList<QAction*>* nopActions;
  ToolBar*         toolBar;
  PluginHandler*   plugHdr;
  StateMachine* sm;
  State* applicationSetup;
  State* atc;
  State* editFile;
  State* editJob;
  State* emergencySTOP;
  State* errorState;
  State* fileChanged;
  State* fixtures;
  State* halInfo;
  State* homeAllAxis;
  State* jobChanged;
  State* jobFinished;
  State* jobPaused;
  State* jobProcessing;
  State* jobRunning;
  State* jogging;
  State* machineEnabled;
  State* machineSetup;
  State* manualCommands;
  State* manualJog;
  State* manualMoves;
  State* measureTouch;
  State* openFile;
  State* powerOFF;
  State* setup;
  State* showMessages;
  State* toolManager;
  State* toolTable;
  State* wheelJog;
  };


class WorkerThread : public QThread
{
  Q_OBJECT
public:
  explicit WorkerThread(QObject* parent = nullptr);
  void run() override;

signals:
  void resultReady(const QString &s);
  };
#endif // MAINCONTROL_H
