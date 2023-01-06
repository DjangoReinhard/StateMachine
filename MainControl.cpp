/*
 * **************************************************************************
 *
 *  file:       maincontrol.cpp
 *  project:    AppStateMachine
 *  subproject: main application
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
#include "MainControl.h"
#include <mainwindow.h>
#include <MultiStateAction.h>
#include <EndingState.h>
#include <HistoryState.h>
#include <OrphanState.h>
#include <ReturnState.h>
#include <StateMachine.h>
#include <PluginHandler.h>
#include <ToolBar.h>
#include <IApplicationPage.h>
#include <HistoryStateTransition.h>
#include <ValueManager.h>
#include <ValueModel.h>
#include <AppUserEvents.h>
#include <QAction>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QLayout>
#include <QWidget>
#include <QToolButton>


MainControl::MainControl(QObject *parent)
  : QObject(parent)
  , actionMap(new QHash<int, MultiStateAction*>())
  , tbButtons(nullptr)
  , nopActions(new QList<QAction*>())
  , plugHdr(nullptr)
  , sm(new StateMachine())
  , applicationSetup(nullptr)
  , atc(nullptr)
  , editFile(nullptr)
  , editJob(nullptr)
  , emergencySTOP(nullptr)
  , errorState(nullptr)
  , fileChanged(nullptr)
  , fixtures(nullptr)
  , halInfo(nullptr)
  , homeAllAxis(nullptr)
  , jobChanged(nullptr)
  , jobFinished(nullptr)
  , jobPaused(nullptr)
  , jobProcessing(nullptr)
  , jobRunning(nullptr)
  , jogging(nullptr)
  , machineEnabled(nullptr)
  , machineSetup(nullptr)
  , manualCommands(nullptr)
  , manualJog(nullptr)
  , manualMoves(nullptr)
  , measureTouch(nullptr)
  , openFile(nullptr)
  , powerOFF(nullptr)
  , setup(nullptr)
  , showMessages(nullptr)
  , toolManager(nullptr)
  , toolTable(nullptr)
  , wheelJog(nullptr) {
  plugHdr = new PluginHandler(QFileInfo(QDir(QCoreApplication::applicationDirPath()), "plugins"));
  plugHdr->loadPlugins(plugins);
  createStateMachine();
  createActions();
  connectStates();
  }


MainControl::~MainControl() {
  delete applicationSetup;
  delete atc;
  delete editFile;
  delete editJob;
  delete emergencySTOP;
  delete errorState;
  delete fileChanged;
  delete fixtures;
  delete halInfo;
  delete homeAllAxis;
  delete jobChanged;
  delete jobFinished;
  delete jobPaused;
  delete jobProcessing;
  delete jobRunning;
  delete jogging;
  delete machineEnabled;
  delete machineSetup;
  delete manualCommands;
  delete manualJog;
  delete manualMoves;
  delete measureTouch;
  delete openFile;
  delete powerOFF;
  delete setup;
  delete showMessages;
  delete toolManager;
  delete toolTable;
  delete wheelJog;
  delete actionMap;
  delete tbButtons;
  }


QHash<int, MultiStateAction*>* MainControl::actions() {
  return actionMap;
  }


void MainControl::connectStates() {
  connect(applicationSetup, &State::onEntry, this, &MainControl::enterApplicationSetup);
  connect(editFile, &State::onEntry, this, &MainControl::enterEditFile);
  connect(editJob, &State::onEntry, this, &MainControl::enterEditJob);
  connect(emergencySTOP, &State::onEntry, this, &MainControl::enterEmergencySTOP);
  connect(errorState, &State::onEntry, this, &MainControl::enterErrorState);
  connect(fixtures, &State::onEntry, this, &MainControl::enterFixtures);
  connect(halInfo, &State::onEntry, this, &MainControl::enterHalInfo);
  connect(homeAllAxis, &State::onEntry, this, &MainControl::enterHomeAllAxis);
  connect(jobFinished, &State::onEntry, this, &MainControl::enterJobFinished);
  connect(jobPaused, &State::onEntry, this, &MainControl::enterJobPaused);
  connect(jobProcessing, &State::onEntry, this, &MainControl::enterJobProcessing);
  connect(jobRunning, &State::onEntry, this, &MainControl::enterJobRunning);
  connect(manualJog, &State::onEntry, this, &MainControl::enterManualJog);
  connect(machineEnabled, &State::onEntry, this, &MainControl::enterMachineEnabled);
  connect(machineSetup, &State::onEntry, this, &MainControl::enterMachineSetup);
  connect(manualCommands, &State::onEntry, this, &MainControl::enterManualCommands);
  connect(manualMoves, &State::onEntry, this, &MainControl::enterManualMoves);
  connect(measureTouch, &State::onEntry, this, &MainControl::enterMeasureTouch);
  connect(setup, &State::onEntry, this, &MainControl::enterSetup);
  connect(atc, &State::onEntry, this, &MainControl::enterATC);
  connect(showMessages, &State::onEntry, this, &MainControl::enterShowMessages);
  connect(toolManager, &State::onEntry, this, &MainControl::enterToolManager);
  connect(toolTable, &State::onEntry, this, &MainControl::enterToolTable);
  connect(wheelJog, &State::onEntry, this, &MainControl::enterWheelJog);

  connect(applicationSetup, &State::onExit, this, &MainControl::exitApplicationSetup);
  connect(editFile, &State::onExit, this, &MainControl::exitEditFile);
  connect(editJob, &State::onExit, this, &MainControl::exitEditJob);
  connect(fixtures, &State::onExit, this, &MainControl::exitFixtures);
  connect(halInfo, &State::onExit, this, &MainControl::exitHalInfo);
  connect(jobPaused, &State::onExit, this, &MainControl::exitJobPaused);
  connect(jobProcessing, &State::onExit, this, &MainControl::exitJobProcessing);
  connect(machineSetup, &State::onExit, this, &MainControl::exitMachineSetup);
  connect(manualCommands, &State::onExit, this, &MainControl::exitManualCommands);
  connect(manualMoves, &State::onExit, this, &MainControl::exitManualMoves);
  connect(measureTouch, &State::onExit, this, &MainControl::exitMeasureTouch);
  connect(setup, &State::onExit, this, &MainControl::exitSetup);
  connect(atc, &State::onExit, this, &MainControl::exitATC);
  connect(toolManager, &State::onExit, this, &MainControl::exitToolManager);
  connect(toolTable, &State::onExit, this, &MainControl::exitToolTable);
  connect(wheelJog, &State::onExit, this, &MainControl::exitWheelJog);
  }


void MainControl::createActions() {
  actionMap->insert(NOPAction, new MultiStateAction(QIcon(":/res/SK_DisabledIcon.png"), QIcon(":/res/SK_DisabledIcon.png"), "NOP"));
  actionMap->insert(EmergencySTOP, new MultiStateAction(QIcon(":/res/SK_PowerOff.png"), QIcon(":/res/SK_PowerOn.png"), "EmergencySTOP"));
  actionMap->insert(EditJob, new MultiStateAction(QIcon(":/res/SK_Edit.png"), QIcon(":/res/SK_Edit_active.png"), "Edit-Job"));
  actionMap->insert(EditFile, new MultiStateAction(QIcon(":/res/SK_TestEdit.png"), QIcon(":/res/SK_TestEdit_active.png"), "TestEdit"));
  actionMap->insert(OpenFile, new MultiStateAction(QIcon(":/res/SK_Open.png"), QIcon(":/res/SK_Open_active.png"), "Search"));
  actionMap->insert(Search, new MultiStateAction(QIcon(":/res/SK_Search.png"), QIcon(":/res/SK_Search_active.png"), "Search"));
  actionMap->insert(Save, new MultiStateAction(QIcon(":/res/SK_Save.png"), QIcon(":/res/SK_Save_active.png"), "Save"));
  actionMap->insert(Exit, new MultiStateAction(QIcon(":/res/SK_Back.png"), QIcon(":/res/SK_Back.png"), "Exit"));
  actionMap->insert(Setup, new MultiStateAction(QIcon(":/res/SK_Settings.png"), QIcon(":/res/SK_Settings_active.png"), "Setup"));
  actionMap->insert(ApplicationSetup, new MultiStateAction(QIcon(":/res/SK_Config.png"), QIcon(":/res/SK_Config_active.png"), "ApplicationSetup"));
  actionMap->insert(Fixtures, new MultiStateAction(QIcon(":/res/SK_Offsets.png"), QIcon(":/res/SK_Offsets_active.png"), "Fixture"));
  actionMap->insert(View, new MultiStateAction(QIcon(":/res/SK_View.png"), QIcon(":/res/SK_View_active.png"), "View"));
  actionMap->insert(JobPaused, new MultiStateAction(QIcon(":/res/SK_AutoPause.png"), QIcon(":/res/SK_AutoPause_active.png"), "Auto-Pause"));
  actionMap->insert(JobRunning, new MultiStateAction(QIcon(":/res/SK_AutoStart.png"), QIcon(":/res/SK_AutoStart_active.png"), "Auto-Start"));
  actionMap->insert(JobFinished, new MultiStateAction(QIcon(":/res/SK_AutoStop.png"), QIcon(":/res/SK_AutoStop_active.png"), "Auto-Stop"));
  actionMap->insert(JobProcessing, new MultiStateAction(QIcon(":/res/SK_Auto.png"), QIcon(":/res/SK_Auto_active.png"), "Auto-Mode"));
  actionMap->insert(AbsolutePosition, new MultiStateAction(QIcon(":/res/SK_PosRelative.png"), QIcon(":/res/SK_PosAbsolute.png"), "AbsolutePosition"));
  actionMap->insert(ATC, new MultiStateAction(QIcon(":/res/SK_ATC.png"), QIcon(":/res/SK_ATC_active.png"), "ATC"));
  actionMap->insert(ActiveAxis, new MultiStateAction(QIcon(":/res/SK_DisabledIcon.png"), QIcon(":/res/SK_DisabledIcon.png"), "ActiveAxis"));
  actionMap->insert(ContinuousJogging, new MultiStateAction(QIcon(":/res/SK_DisabledIcon.png"), QIcon(":/res/SK_DisabledIcon.png"), "ContinuousJogging"));
  actionMap->insert(StepSize, new MultiStateAction(QIcon(":/res/SK_DisabledIcon.png"), QIcon(":/res/SK_DisabledIcon.png"), "StepSize"));
  actionMap->insert(FloodCooling, new MultiStateAction(QIcon(":/res/SK_Cool_Flood.png"), QIcon(":/res/SK_Cool_Flood_active.png"), "Cool-Flood"));
  actionMap->insert(MistCooling, new MultiStateAction(QIcon(":/res/SK_Cool_Mist.png"), QIcon(":/res/SK_Cool_Mist_active.png"), "Cool-Mist"));
  actionMap->insert(HomeAllAxis, new MultiStateAction(QIcon(":/res/SK_HomeAll.png"), QIcon(":/res/SK_HomeAll.png"), "HomeAll"));
  actionMap->insert(ManualCommands, new MultiStateAction(QIcon(":/res/SK_MDI.png"), QIcon(":/res/SK_MDI_active.png"), "MDI"));
  actionMap->insert(ManualJog, new MultiStateAction(QIcon(":/res/SK_Manual.png"), QIcon(":/res/SK_Manual_active.png"), "JogManual"));
  actionMap->insert(ShowMessages, new MultiStateAction(QIcon(":/res/SK_Messages.png"), QIcon(":/res/SK_Messages_active.png"), "Messages"));
  actionMap->insert(SingleStep, new MultiStateAction(QIcon(":/res/SK_SingleStep.png"), QIcon(":/res/SK_SingleStep_active.png"), "SingleStep"));
  actionMap->insert(SpindleCCW, new MultiStateAction(QIcon(":/res/SK_Spindle_CCW.png"), QIcon(":/res/SK_Spindle_CCW_active.png"), "SpindleCCW"));
  actionMap->insert(SpindleCW, new MultiStateAction(QIcon(":/res/SK_Spindle_CW.png"), QIcon(":/res/SK_Spindle_CW_active.png"), "SpindleCW"));
  actionMap->insert(SpindleStop, new MultiStateAction(QIcon(":/res/SK_Spindle_Stop.png"), QIcon(":/res/SK_Spindle_Stop_active.png"), "SpindleStop"));
  actionMap->insert(ToolManager, new MultiStateAction(QIcon(":/res/SK_ToolManager.png"), QIcon(":/res/SK_ToolManager_active.png"), "ToolManager"));
  actionMap->insert(ToolTable, new MultiStateAction(QIcon(":/res/SK_Tools.png"), QIcon(":/res/SK_Tools_active.png"), "Tools"));
  actionMap->insert(MeasureTouch, new MultiStateAction(QIcon(":/res/SK_Touch.png"), QIcon(":/res/SK_Touch_active.png"), "Touch"));
  actionMap->insert(WheelJog, new MultiStateAction(QIcon(":/res/SK_Wheel.png"), QIcon(":/res/SK_Wheel_active.png"), "Wheel"));
  actionMap->value(NOPAction)->setEnabled(false);

  for (int i=0; i < plugins.size(); ++i) {
      IApplicationPage* p = plugins.at(i);
      AppUserEvents e = SIAppUserEvents::parse(p->pageName());
      MultiStateAction* a = dynamic_cast<MultiStateAction*>(p->viewAction());

      if (a && !actionMap->contains(e)) {
         actionMap->insert(e, a);

         if (e == MachineSetup)
            connect(actionMap->value(MachineSetup), &QAction::triggered, this, &MainControl::handleMachineSetup );
         else if (e == HALInfo)
            connect(actionMap->value(HALInfo), &QAction::triggered, this, &MainControl::handleHALInfo );
         }
      }

  connect(actionMap->value(EmergencySTOP), &QAction::triggered, this, &MainControl::handleEmergencySTOP );
  connect(actionMap->value(EditJob), &QAction::triggered, this, &MainControl::handleEditJob );
  connect(actionMap->value(EditFile), &QAction::triggered, this, &MainControl::handleEditFile );
  connect(actionMap->value(OpenFile), &QAction::triggered, this, &MainControl::handleOpenFile );
  connect(actionMap->value(Search), &QAction::triggered, this, &MainControl::handleSearch );
  connect(actionMap->value(Save), &QAction::triggered, this, &MainControl::handleSave );
  connect(actionMap->value(Exit), &QAction::triggered, this, &MainControl::handleExit );
  connect(actionMap->value(Setup), &QAction::triggered, this, &MainControl::handleSetup );
  connect(actionMap->value(ApplicationSetup), &QAction::triggered, this, &MainControl::handleApplicationSetup );
  connect(actionMap->value(Fixtures), &QAction::triggered, this, &MainControl::handleFixtures );
  connect(actionMap->value(View), &QAction::triggered, this, &MainControl::handleView );
  connect(actionMap->value(JobPaused), &QAction::triggered, this, &MainControl::handleJobPaused );
  connect(actionMap->value(JobRunning), &QAction::triggered, this, &MainControl::handleJobRunning );
  connect(actionMap->value(JobFinished), &QAction::triggered, this, &MainControl::handleJobFinished );
  connect(actionMap->value(JobProcessing), &QAction::triggered, this, &MainControl::handleJobProcessing );
  connect(actionMap->value(AbsolutePosition), &QAction::triggered, this, &MainControl::handleAbsolutePosition );
  connect(actionMap->value(ATC), &QAction::triggered, this, &MainControl::handleATC );
  connect(actionMap->value(ActiveAxis), &QAction::triggered, this, &MainControl::handleActiveAxis );
  connect(actionMap->value(ContinuousJogging), &QAction::triggered, this, &MainControl::handleContinuousJogging );
  connect(actionMap->value(StepSize), &QAction::triggered, this, &MainControl::handleStepSize );
  connect(actionMap->value(FloodCooling), &QAction::triggered, this, &MainControl::handleFloodCooling );
  connect(actionMap->value(MistCooling), &QAction::triggered, this, &MainControl::handleMistCooling );
  connect(actionMap->value(HomeAllAxis), &QAction::triggered, this, &MainControl::handleHomeAllAxis );
  connect(actionMap->value(ManualCommands), &QAction::triggered, this, &MainControl::handleManualCommands );
  connect(actionMap->value(ManualJog), &QAction::triggered, this, &MainControl::handleManualJog );
  connect(actionMap->value(ShowMessages), &QAction::triggered, this, &MainControl::handleShowMessages );
  connect(actionMap->value(Fixtures), &QAction::triggered, this, &MainControl::handleFixtures );
  connect(actionMap->value(SingleStep), &QAction::triggered, this, &MainControl::handleSingleStep );
  connect(actionMap->value(SpindleCCW), &QAction::triggered, this, &MainControl::handleSpindleCCW );
  connect(actionMap->value(SpindleCW), &QAction::triggered, this, &MainControl::handleSpindleCW );
  connect(actionMap->value(SpindleStop), &QAction::triggered, this, &MainControl::handleSpindleStop );
  connect(actionMap->value(ToolManager), &QAction::triggered, this, &MainControl::handleToolManager );
  connect(actionMap->value(ToolTable), &QAction::triggered, this, &MainControl::handleToolTable );
  connect(actionMap->value(MeasureTouch), &QAction::triggered, this, &MainControl::handleMeasureTouch );
  connect(actionMap->value(WheelJog), &QAction::triggered, this, &MainControl::handleWheelJog );
  }


void MainControl::createStateMachine() {
  emergencySTOP    = new State(EmergencySTOP, "EmergencySTOP", sm);
  errorState       = new State(ErrorSTATE, "ErrorSTATE", sm);
  powerOFF         = new State(PowerOFF, "PowerOFF", sm);
  machineEnabled   = new State(MachineEnabled, "MachineEnabled",  powerOFF);
  editJob          = new ReturnState(EditJob, "EditJob", machineEnabled);
  editFile         = new ReturnState(EditFile, "EditFile", machineEnabled);
  openFile         = new ReturnState(OpenFile, "OpenFile", machineEnabled);
  homeAllAxis      = new HistoryState(HomeAllAxis, "HomeAllAxis", machineEnabled);
  setup            = new ReturnState(Setup, "Setup", machineEnabled);
  showMessages     = new ReturnState(ShowMessages, "ShowMessages", machineEnabled);
  jobChanged       = new OrphanState(JobChanged, "JobChanged", editJob);
  fileChanged      = new OrphanState(FileChanged, "FileChanged", editFile);
  manualCommands   = new State(ManualCommands, "ManualCommands", homeAllAxis);
  manualMoves      = new State(ManualMoves, "ManualMoves", homeAllAxis);
  manualJog        = new ReturnState(ManualJog, "ManualJog", manualMoves);
  wheelJog         = new ReturnState(WheelJog, "WheelJog", manualMoves);
  measureTouch     = new State(MeasureTouch, "MeasureTouch", homeAllAxis);
  jobProcessing    = new ReturnState(JobProcessing, "JobProcessing", homeAllAxis);
  atc              = new State(ATC, "ATC", setup);
  applicationSetup = new State(ApplicationSetup, "ApplicationSetup", setup);
  machineSetup     = new State(MachineSetup, "MachineSetup", setup);
  toolTable        = new State(ToolTable, "ToolTable", setup);
  fixtures         = new State(Fixtures, "Fixtures", setup);
  toolManager      = new State(ToolManager, "ToolManager", setup);
  halInfo          = new State(HALInfo, "HALInfo", setup);
  jobRunning       = new OrphanState(JobRunning, "JobRunning", jobProcessing);
  jobFinished      = new EndingState(JobFinished, "JobFinished", jobProcessing);
  jobPaused        = new State(JobPaused, "JobPaused", jobProcessing);
  jogging          = new State(Jogging, "Jogging", homeAllAxis);

  sm->addTransition(emergencySTOP);
  sm->addTransition(showMessages);
  emergencySTOP->addTransition(powerOFF);
  emergencySTOP->addTransition(machineEnabled);
  powerOFF->addTransition(machineEnabled);
  machineEnabled->addTransition(emergencySTOP);
  machineEnabled->addTransition(editJob);
  machineEnabled->addTransition(editFile);
  machineEnabled->addTransition(homeAllAxis);
  machineEnabled->addTransition(setup);

  editJob->addTransition(jobChanged);
  editJob->addTransition(openFile);
  editFile->addTransition(fileChanged);
  editFile->addTransition(openFile);
  jobChanged->addTransition(editJob);
  fileChanged->addTransition(editFile);

  homeAllAxis->addTransition(jobProcessing);
  homeAllAxis->addTransition(manualCommands);
  homeAllAxis->addTransition(manualJog);
  homeAllAxis->addTransition(wheelJog);
  homeAllAxis->addTransition(measureTouch);
  homeAllAxis->addTransition(showMessages);

  setup->addTransition(applicationSetup);
  setup->addTransition(machineSetup);
  setup->addTransition(toolTable);
  setup->addTransition(fixtures);
  setup->addTransition(toolManager);
  setup->addTransition(halInfo);
  setup->addTransition(atc);

  jobProcessing->addTransition(JobRunning, jobRunning);
  jobRunning->addTransition(JobPaused, jobPaused);
  jobRunning->addTransition(JobFinished, jobFinished);
  jobPaused->addTransition(JobRunning, jobRunning);
  jobPaused->addTransition(JobFinished, jobFinished);
  }


void MainControl::enterApplicationSetup() {
  actionMap->value(ApplicationSetup)->setActionState(Active);
  }


void MainControl::enterATC() {
  actionMap->value(ATC)->setActionState(Active);
  }


void MainControl::enterEditFile() {
  static int actionCodes[] = {
    OpenFile,
    Search,
    NOPAction,
    Save,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    Exit,
    EmergencySTOP
    };
  actionMap->value(OpenFile)->setActionState(Enabled);
  actionMap->value(Search)->setActionState(Disabled);
  actionMap->value(Save)->setActionState(Disabled);
  actionMap->value(Exit)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterEditJob() {
  static int actionCodes[] = {
    OpenFile,
    Search,
    NOPAction,
    Save,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    Exit,
    EmergencySTOP
    };
  actionMap->value(OpenFile)->setActionState(Enabled);
  actionMap->value(Search)->setActionState(Disabled);
  actionMap->value(Save)->setActionState(Disabled);
  actionMap->value(Exit)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterEmergencySTOP() {
  static int actionCodes[] = {
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    EmergencySTOP
    };
  actionMap->value(EmergencySTOP)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterErrorState() {
  static int actionCodes[] = {
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    EmergencySTOP
    };
  actionMap->value(EmergencySTOP)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterFixtures() {
  actionMap->value(Fixtures)->setActionState(Active);
  }


void MainControl::enterHalInfo() {
  actionMap->value(HALInfo)->setActionState(Active);
  }


void MainControl::enterHomeAllAxis() {
  static int actionCodes[] = {
    JobProcessing,
    EditJob,
    ManualCommands,
    EditFile,
    ManualJog,
    WheelJog,
    MeasureTouch,
    NOPAction,
    NOPAction,
    Setup,
    ShowMessages,
    EmergencySTOP
    };
  actionMap->value(JobProcessing)->setActionState(Enabled);
  actionMap->value(EditJob)->setActionState(Enabled);
  actionMap->value(ManualCommands)->setActionState(Enabled);
  actionMap->value(EditFile)->setActionState(Enabled);
  actionMap->value(ManualJog)->setActionState(Enabled);
  actionMap->value(WheelJog)->setActionState(Enabled);
  actionMap->value(MeasureTouch)->setActionState(Enabled);
  actionMap->value(Setup)->setActionState(Enabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);
  actionMap->value(MachineSetup)->setActionState(Enabled);
  actionMap->value(Fixtures)->setActionState(Enabled);

  updateToolbar(actionCodes);
  MainWindow* mw = dynamic_cast<MainWindow*>(parent());

  connect(ValueManager().getModel("counter"), &ValueModel::valueChanged, mw, &MainWindow::refreshCounter);
  }


void MainControl::enterJobFinished() {
  actionMap->value(JobRunning)->setActionState(Enabled);
  actionMap->value(JobPaused)->setActionState(Disabled);
  actionMap->value(JobFinished)->setActionState(Active);
  actionMap->value(SingleStep)->setActionState(Disabled);
  }


void MainControl::enterJobPaused() {
  actionMap->value(JobPaused)->setActionState(Active);
  actionMap->value(JobRunning)->setActionState(Enabled);
  }


void MainControl::enterJobProcessing() {
  static int actionCodes[] = {
    JobRunning,
    JobPaused,
    JobFinished,
    SingleStep,
    AbsolutePosition,
    FloodCooling,
    MistCooling,
    NOPAction,
    NOPAction,
    View,
    Exit,
    EmergencySTOP
    };
  actionMap->value(JobRunning)->setActionState(Enabled);
  actionMap->value(JobPaused)->setActionState(Disabled);
  actionMap->value(JobFinished)->setActionState(Disabled);
  actionMap->value(SingleStep)->setActionState(Disabled);
  actionMap->value(FloodCooling)->setActionState(Enabled);
  actionMap->value(MistCooling)->setActionState(Enabled);
  actionMap->value(View)->setActionState(Enabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);
  actionMap->value(Exit)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterJobRunning() {
  actionMap->value(JobRunning)->setActionState(Active);
  actionMap->value(JobPaused)->setActionState(Enabled);
  actionMap->value(JobFinished)->setActionState(Enabled);
  }


void MainControl::enterMachineEnabled() {
  static int actionCodes[] = {
    NOPAction,
    EditJob,
    NOPAction,
    EditFile,
    NOPAction,
    NOPAction,
    NOPAction,
    Setup,
    HomeAllAxis,
    NOPAction,
    ShowMessages,
    EmergencySTOP
    };
  actionMap->value(EditJob)->setActionState(Enabled);
  actionMap->value(EditFile)->setActionState(Enabled);
  actionMap->value(Setup)->setActionState(Enabled);
  actionMap->value(HomeAllAxis)->setActionState(Enabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterMachineSetup() {
  actionMap->value(MachineSetup)->setActionState(Active);
  }


void MainControl::enterManualCommands() {
  static int actionCodes[] = {
    JobProcessing,
    EditJob,
    ManualCommands,
    EditFile,
    ManualJog,
    WheelJog,
    MeasureTouch,
    NOPAction,
    NOPAction,
    Setup,
    ShowMessages,
    EmergencySTOP
    };
  actionMap->value(JobProcessing)->setActionState(Enabled);
  actionMap->value(EditJob)->setActionState(Enabled);
  actionMap->value(ManualCommands)->setActionState(Active);
  actionMap->value(EditFile)->setActionState(Enabled);
  actionMap->value(ManualJog)->setActionState(Enabled);
  actionMap->value(WheelJog)->setActionState(Enabled);
  actionMap->value(MeasureTouch)->setActionState(Enabled);
  actionMap->value(Setup)->setActionState(Enabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterManualJog() {
  actionMap->value(ContinuousJogging)->setActionState(Enabled);
  actionMap->value(ActiveAxis)->setActionState(InActive);
  actionMap->value(StepSize)->setActionState(InActive);
  }


void MainControl::enterManualMoves() {
  static int actionCodes[] = {
    ContinuousJogging,
    ActiveAxis,
    StepSize,
    NOPAction,
    AbsolutePosition,
    FloodCooling,
    MistCooling,
    SpindleCCW,
    SpindleStop,
    SpindleCW,
    Exit,
    EmergencySTOP
    };
  actionMap->value(ContinuousJogging)->setActionState(InActive);
  actionMap->value(ActiveAxis)->setActionState(InActive);
  actionMap->value(StepSize)->setActionState(InActive);
  actionMap->value(AbsolutePosition)->setActionState(Enabled);
  actionMap->value(FloodCooling)->setActionState(Enabled);
  actionMap->value(MistCooling)->setActionState(Enabled);
  actionMap->value(SpindleCCW)->setActionState(Enabled);
  actionMap->value(SpindleCW)->setActionState(Enabled);
  actionMap->value(SpindleStop)->setActionState(Enabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);
  actionMap->value(Exit)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterMeasureTouch() {
  static int actionCodes[] = {
    JobProcessing,
    EditJob,
    ManualCommands,
    EditFile,
    ManualJog,
    WheelJog,
    MeasureTouch,
    NOPAction,
    NOPAction,
    Setup,
    ShowMessages,
    EmergencySTOP
    };
  actionMap->value(JobProcessing)->setActionState(Enabled);
  actionMap->value(EditJob)->setActionState(Enabled);
  actionMap->value(ManualCommands)->setActionState(Enabled);
  actionMap->value(EditFile)->setActionState(Enabled);
  actionMap->value(ManualJog)->setActionState(Enabled);
  actionMap->value(WheelJog)->setActionState(Enabled);
  actionMap->value(MeasureTouch)->setActionState(Active);
  actionMap->value(Setup)->setActionState(Enabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterSetup() {
  static int actionCodes[] = {
    ApplicationSetup,
    MachineSetup,
    Fixtures,
    ToolTable,
    ATC,
    HALInfo,
    ToolManager,
    NOPAction,
    NOPAction,
    NOPAction,
    Exit,
    EmergencySTOP
    };
  actionMap->value(ApplicationSetup)->setActionState(Enabled);
  actionMap->value(MachineSetup)->setActionState(sm->haveSeen(homeAllAxis) ? Enabled : Disabled);
  actionMap->value(Fixtures)->setActionState(sm->haveSeen(homeAllAxis) ? Enabled : Disabled);
  actionMap->value(ToolTable)->setActionState(Enabled);
  actionMap->value(ATC)->setActionState(Enabled);
  actionMap->value(HALInfo)->setActionState(Enabled);
  actionMap->value(ToolManager)->setActionState(Enabled);

  updateToolbar(actionCodes);
  }


void MainControl::enterShowMessages() {
  static int actionCodes[] = {
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    NOPAction,
    Exit,
    EmergencySTOP
    };
  updateToolbar(actionCodes);
  }


void MainControl::enterToolManager() {
  actionMap->value(ToolManager)->setActionState(Active);
  }


void MainControl::enterToolTable() {
  actionMap->value(ToolTable)->setActionState(Active);
  }


void MainControl::enterWheelJog() {
  actionMap->value(ContinuousJogging)->setActionState(InActive);
  actionMap->value(ActiveAxis)->setActionState(Enabled);
  actionMap->value(StepSize)->setActionState(Enabled);
  }


void MainControl::exitApplicationSetup() {
  actionMap->value(ApplicationSetup)->setActionState(Enabled);
  }


void MainControl::exitATC() {
  actionMap->value(ATC)->setActionState(Enabled);
  }


void MainControl::exitEditFile() {
  actionMap->value(EditFile)->setActionState(Enabled);
  }


void MainControl::exitEditJob() {
  actionMap->value(EditJob)->setActionState(Enabled);
  }


void MainControl::exitFixtures() {
  actionMap->value(Fixtures)->setActionState(Enabled);
  }


void MainControl::exitHalInfo() {
  actionMap->value(HALInfo)->setActionState(Enabled);
  }


void MainControl::exitJobPaused() {
  actionMap->value(JobPaused)->setActionState(Enabled);
  }


void MainControl::exitJobProcessing() {
  actionMap->value(JobRunning)->setActionState(Enabled);
  actionMap->value(JobPaused)->setActionState(Disabled);
  actionMap->value(JobFinished)->setActionState(Disabled);
  actionMap->value(SingleStep)->setActionState(Disabled);
  actionMap->value(FloodCooling)->setActionState(Disabled);
  actionMap->value(MistCooling)->setActionState(Disabled);
  actionMap->value(SpindleCCW)->setActionState(Disabled);
  actionMap->value(SpindleCW)->setActionState(Disabled);
  actionMap->value(SpindleStop)->setActionState(Disabled);
  actionMap->value(ShowMessages)->setActionState(Enabled);
  actionMap->value(Exit)->setActionState(Enabled);
  }


void MainControl::exitManualMoves() {
  actionMap->value(FloodCooling)->setActionState(InActive);
  actionMap->value(MistCooling)->setActionState(InActive);
  actionMap->value(SpindleCCW)->setActionState(InActive);
  actionMap->value(SpindleCW)->setActionState(InActive);
  actionMap->value(SpindleStop)->setActionState(InActive);
  }


void MainControl::exitMachineSetup() {
  actionMap->value(MachineSetup)->setActionState(Enabled);
  }


void MainControl::exitManualCommands() {
  actionMap->value(ManualCommands)->setActionState(Enabled);
  }


void MainControl::exitMeasureTouch() {
  actionMap->value(MeasureTouch)->setActionState(Enabled);
  }


void MainControl::exitSetup() {
  actionMap->value(Setup)->setActionState(Enabled);
  }


void MainControl::exitToolManager() {
  actionMap->value(ToolManager)->setActionState(Enabled);
  }


void MainControl::exitToolTable() {
  actionMap->value(ToolTable)->setActionState(Enabled);
  }


void MainControl::exitWheelJog() {
  actionMap->value(WheelJog)->setActionState(Enabled);
  }


void MainControl::handleEmergencySTOP() {
  sm->dispatch(EmergencySTOP);
  }


void MainControl::handleEditJob() {
  sm->dispatch(EditJob);
  }


void MainControl::handleEditFile() {
  sm->dispatch(EditFile);
  }


void MainControl::handleOpenFile() {
  sm->dispatch(OpenFile);
  }


void MainControl::handleSearch() {
  sm->dispatch(Search);
  }


void MainControl::handleSave() {
  sm->dispatch(Save);
  }


void MainControl::handleExit() {
  qDebug() << "try to return from current state";
  sm->stateReturn();
  }


void MainControl::handleSetup() {
  sm->dispatch(Setup);
  }


void MainControl::handleApplicationSetup() {
  sm->dispatch(ApplicationSetup);
  }


void MainControl::handleMachineSetup() {
  sm->dispatch(MachineSetup);
  }


void MainControl::handleHALInfo() {
  sm->dispatch(HALInfo);
  }


void MainControl::handleView() {
  sm->dispatch(View);
  }


void MainControl::handleJobPaused() {
  sm->dispatch(JobPaused);
  }


void MainControl::handleJobRunning() {
  sm->dispatch(JobRunning);
  }


void MainControl::handleJobFinished() {
  sm->dispatch(JobFinished);
  }


void MainControl::handleJobProcessing() {
  sm->dispatch(JobProcessing);
  }


void MainControl::handleAbsolutePosition() {
  sm->dispatch(AbsolutePosition);
  }


void MainControl::handleATC() {
  sm->dispatch(ATC);
  }


void MainControl::handleActiveAxis() {
  sm->dispatch(ActiveAxis);
  }


void MainControl::handleContinuousJogging() {
  sm->dispatch(ContinuousJogging);
  }


void MainControl::handleStepSize() {
  sm->dispatch(StepSize);
  }


void MainControl::handleFloodCooling() {
  sm->dispatch(FloodCooling);
  }


void MainControl::handleMistCooling() {
  sm->dispatch(MistCooling);
  }


void MainControl::handleHomeAllAxis() {
  sm->dispatch(HomeAllAxis);
  }


void MainControl::handleManualCommands() {
  sm->dispatch(ManualCommands);
  }


void MainControl::handleManualJog() {
  sm->dispatch(ManualJog);
  }


void MainControl::handleShowMessages() {
  sm->dispatch(ShowMessages);
  }


void MainControl::handleFixtures() {
  sm->dispatch(Fixtures);
  }


void MainControl::handleSingleStep() {
  sm->dispatch(SingleStep);
  }


void MainControl::handleSpindleCCW() {
  sm->dispatch(SpindleCCW);
  }


void MainControl::handleSpindleCW() {
  sm->dispatch(SpindleCW);
  }


void MainControl::handleSpindleStop() {
  sm->dispatch(SpindleStop);
  }


void MainControl::handleToolManager() {
  sm->dispatch(ToolManager);
  }


void MainControl::handleToolTable() {
  sm->dispatch(ToolTable);
  }


void MainControl::handleMeasureTouch() {
  sm->dispatch(MeasureTouch);
  }


void MainControl::handleWheelJog() {
  sm->dispatch(WheelJog);
  }


StateMachine* MainControl::stateMachine() {
  return sm;
  }


void MainControl::setToolBar(ToolBar *tb) {
  this->toolBar = tb;
  }


WorkerThread::WorkerThread(QObject *parent)
 : QThread(parent) {
  }


void WorkerThread::run() {
  QString result;
  int     c = 13;

  /*
   * ... here is the expensive or blocking operation ...
   */
  while (true) {
        msleep(100);
        ValueManager().setValue("counter", ++c);
        }
  emit resultReady(result);
  }


void MainControl::handleEndOfCounter() {
  qDebug() << "Blub ...";
  }


void MainControl::start(bool startThread) {
  sm->setInitialState(emergencySTOP);

  if (startThread) {
     WorkerThread *workerThread = new WorkerThread(this);

     connect(workerThread, &WorkerThread::resultReady, this, &MainControl::handleEndOfCounter);
     connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
     workerThread->start();
     }
  }


void MainControl::updateToolbar(int actionCodes[]) {
  for (int i=0; i < 12; ++i) {
      toolBar->setAction(i, actionMap->value(actionCodes[i]));
      }
  }
