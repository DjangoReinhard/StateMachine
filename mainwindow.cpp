/*
 * **************************************************************************
 * 
 *  file:       mainwindow.cpp
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
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <StateMachine.h>
#include <MultiStateAction.h>
#include <ToolBar.h>
#include <AppUserEvents.h>
#include <MainControl.h>
#include <PluginHandler.h>
#include <ValueModel.h>
#include <ValueManager.h>
#include <QToolBar>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , ctrl(nullptr)
 , mainTB(nullptr) {
  ui->setupUi(this);
  setContextMenuPolicy(Qt::NoContextMenu);
  ctrl = new MainControl(this);
  connectUI();
  createToolbars();
  ctrl->start(/* true */);
  }


MainWindow::~MainWindow() {
  delete ui;
  }


void MainWindow::connectUI() {
  connect(ui->pb2,    &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(MachineEnabled); });
  connect(ui->pb21,   &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(EditJob); });
  connect(ui->pb22,   &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(EditFile); });
  connect(ui->pb23,   &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(HomeAllAxis); });
  connect(ui->pb25,   &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(ShowMessages); });
  connect(ui->pb211,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(JobChanged); });
  connect(ui->pb221,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(FileChanged); });
  connect(ui->pb241,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(MachineSetup); });
  connect(ui->pb242,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(ApplicationSetup); });
  connect(ui->pb243,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(ToolTable); });
  connect(ui->pb244,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(Fixtures); });
  connect(ui->pb245,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(ToolManager); });
  connect(ui->pb2311, &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(ManualJog); });
  connect(ui->pb2312, &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(WheelJog); });
  connect(ui->pb232,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(ManualCommands); });
  connect(ui->pb233,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(MeasureTouch); });
  connect(ui->pb234,  &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(JobProcessing); });
  connect(ui->pb2341, &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(JobRunning); });
  connect(ui->pb2342, &QPushButton::clicked, ctrl->stateMachine(), [=]{ ctrl->stateMachine()->dispatch(JobFinished); });

//  connect(ValueManager().getModel("counter"), &ValueModel::valueChanged, this, &MainWindow::refreshCounter);
  }


void MainWindow::createToolbars() {
  mainTB = new ToolBar(tr("Main"));
  ctrl->setToolBar(mainTB);
  this->addDockWidget(Qt::BottomDockWidgetArea, mainTB);
  }


void MainWindow::refreshCounter() {
  int c = ValueManager().getValue("counter").toInt();

  ui->g24->setTitle(QString("S24 - %1").arg(c));
  }
