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
#include <EndingState.h>
#include <HistoryState.h>
#include <ReturnState.h>
#include <StateTransition.h>
#include <HistoryStateTransition.h>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , sm(nullptr)
 , s2(nullptr)
 , s21(nullptr)
 , s22(nullptr)
 , s23(nullptr)
 , s24(nullptr)
 , s25(nullptr)
 , s26(nullptr)
 , s29(nullptr)
 , s231(nullptr)
 , s232(nullptr)
 , s233(nullptr)
 , s234(nullptr)
 , s241(nullptr)
 , s242(nullptr)
 , s243(nullptr)
 , s244(nullptr)
 , s245(nullptr)
 , s2311(nullptr)
 , s2312(nullptr)
 , s2341(nullptr)
 , s2342(nullptr)
  {
  ui->setupUi(this);
  createStateMachine();
  connectUI();
  s0Properties(nullptr);
  }


MainWindow::~MainWindow() {
  delete ui;
  delete s2342;
  delete s2341;
  delete s2312;
  delete s2311;
  delete s241;
  delete s242;
  delete s243;
  delete s244;
  delete s245;
  delete s232;
  delete s233;
  delete s234;
  delete s29;
  delete s26;
  delete s25;
  delete s24;
  delete s23;
  delete s22;
  delete s21;
  delete s2;
  }


void MainWindow::connectUI() {
  connect(ui->pb2,    &QPushButton::clicked, sm, [=]{ sm->dispatch(2); });
  connect(ui->pb21,   &QPushButton::clicked, sm, [=]{ sm->dispatch(21); });
  connect(ui->pb22,   &QPushButton::clicked, sm, [=]{ sm->dispatch(22); });
  connect(ui->pb23,   &QPushButton::clicked, sm, [=]{ sm->dispatch(23); });
  connect(ui->pb25,   &QPushButton::clicked, sm, [=]{ sm->dispatch(25); });
  connect(ui->pbLF,   &QPushButton::clicked, this, &MainWindow::toggleReturnState);
  connect(ui->pb211,  &QPushButton::clicked, sm, [=]{ sm->dispatch(211); });
  connect(ui->pb221,  &QPushButton::clicked, sm, [=]{ sm->dispatch(221); });
  connect(ui->pb241,  &QPushButton::clicked, sm, [=]{ sm->dispatch(241); });
  connect(ui->pb242,  &QPushButton::clicked, sm, [=]{ sm->dispatch(242); });
  connect(ui->pb243,  &QPushButton::clicked, sm, [=]{ sm->dispatch(243); });
  connect(ui->pb244,  &QPushButton::clicked, sm, [=]{ sm->dispatch(244); });
  connect(ui->pb245,  &QPushButton::clicked, sm, [=]{ sm->dispatch(245); });
  connect(ui->pb2311, &QPushButton::clicked, sm, [=]{ sm->dispatch(2311); });
  connect(ui->pb2312, &QPushButton::clicked, sm, [=]{ sm->dispatch(2312); });
  connect(ui->pb232,  &QPushButton::clicked, sm, [=]{ sm->dispatch(232); });
  connect(ui->pb233,  &QPushButton::clicked, sm, [=]{ sm->dispatch(233); });
  connect(ui->pb234,  &QPushButton::clicked, sm, [=]{ sm->dispatch(234); });
  connect(ui->pb2341, &QPushButton::clicked, sm, [=]{ sm->dispatch(2341); });
  connect(ui->pb2342, &QPushButton::clicked, sm, [=]{ sm->dispatch(2342); });  

  connect(s2,  &State::onEntry, this, &MainWindow::s2Properties);
  connect(s23, &State::onEntry, this, &MainWindow::s23Properties);
  }


void MainWindow::createStateMachine() {
  sm = new StateMachine();
  s2    = new State("S2",  sm);
  s21   = new State("S21", s2);
  s22   = new State("S22", s2);
  s23   = new HistoryState("S23", s2);
  s24   = new State("S24", s2);           // virtual
  s25   = new State("S25", s2);
  s26   = new State("S26", s2);
  s29   = new ReturnState("S29",  s2);
  s211  = new OrphanState("S211", s21);
  s221  = new OrphanState("S221", s22);
  s231  = new State("S231", s23);         // virtual
  s232  = new State("S232", s23);
  s233  = new State("S233", s23);
  s234  = new State("S234", s23);
  s241  = new State("S241", s24);
  s242  = new State("S242", s24);
  s243  = new State("S243", s24);
  s244  = new State("S244", s24);
  s245  = new State("S245", s24);
  s2311 = new State("S2311", s231);
  s2312 = new State("S2312", s231);
  s2341 = new OrphanState("S2341", s234);
  s2342 = new EndingState("S2342", s234);

  sm->addTransition(2,   s2);
  s2->addTransition(21,  s21);
  s2->addTransition(22,  s22);
  s2->addTransition(23,  s23);
  s2->addTransition(25,  s25);
  s2->addTransition(241, s241);
  s2->addTransition(242, s242);
  s2->addTransition(243, s243);
  s2->addTransition(244, s244);
  s2->addTransition(245, s245);

  HistoryStateTransition* hst = new HistoryStateTransition(2311, s21, s2311, s23);

  s2->addTransition(hst);
  hst = new HistoryStateTransition(2312, s21, s2312, s23);
  s2->addTransition(hst);
  hst = new HistoryStateTransition(232, s21, s232, s23);
  s2->addTransition(hst);
  hst = new HistoryStateTransition(233, s21, s233, s23);
  s2->addTransition(hst);
  hst = new HistoryStateTransition(234, s21, s234, s23);
  s2->addTransition(hst);
  hst = new HistoryStateTransition(23, s21, s23, s23, false);
  s2->addTransition(hst);

  s21->addTransition(29,  s29);
  s21->addTransition(211, s211);
  s22->addTransition(29,  s29);
  s22->addTransition(221, s221);
  s23->addTransition(2311, s2311);
  s23->addTransition(2312, s2312);
  s23->addTransition(232,  s232);
  s23->addTransition(233,  s233);
  s23->addTransition(234,  s234);

  s211->addTransition(21, s21);
  s221->addTransition(22, s22);
  s234->addTransition(2341, s2341);
  s2341->addTransition(2342, s2342);
  s2342->addTransition(234, s234);
  }


void MainWindow::s0Properties(StateTransition* trans) {
  qDebug() << "s0Properties() ...";
  ui->pb2->setEnabled(true);
  ui->pb21->setEnabled(false);
  ui->pb211->setEnabled(false);
  ui->pb22->setEnabled(false);
  ui->pb221->setEnabled(false);
  ui->pb23->setEnabled(false);
  ui->pb25->setEnabled(false);
  ui->pb241->setEnabled(false);
  ui->pb242->setEnabled(false);
  ui->pb243->setEnabled(false);
  ui->pb244->setEnabled(false);
  ui->pb245->setEnabled(false);
  ui->pb2311->setEnabled(false);
  ui->pb2312->setEnabled(false);
  ui->pb232->setEnabled(false);
  ui->pb2341->setEnabled(false);
  ui->pb2342->setEnabled(false);
  ui->pb233->setEnabled(false);
  ui->pb234->setEnabled(false);
  }


void MainWindow::s2Properties(StateTransition* trans) {
  qDebug() << "s2Properties() ...";
  ui->pb2->setEnabled(true);
  ui->pb21->setEnabled(true);
  ui->pb211->setEnabled(true);
  ui->pb22->setEnabled(true);
  ui->pb221->setEnabled(true);
  ui->pb23->setEnabled(true);
  ui->pb25->setEnabled(true);
  ui->pb241->setEnabled(true);
  ui->pb242->setEnabled(true);
  ui->pb243->setEnabled(true);
  ui->pb244->setEnabled(true);
  ui->pb245->setEnabled(true);
  ui->pb2311->setEnabled(false);
  ui->pb2312->setEnabled(false);
  ui->pb232->setEnabled(false);
  ui->pb2341->setEnabled(false);
  ui->pb2342->setEnabled(false);
  ui->pb233->setEnabled(false);
  ui->pb234->setEnabled(false);
  }


void MainWindow::s23Properties(StateTransition* trans) {
  qDebug() << "s23Properties() ...";
  ui->pb2->setEnabled(true);
  ui->pb21->setEnabled(true);
  ui->pb211->setEnabled(true);
  ui->pb22->setEnabled(true);
  ui->pb221->setEnabled(true);
  ui->pb23->setEnabled(true);
  ui->pb25->setEnabled(true);
  ui->pb241->setEnabled(true);
  ui->pb242->setEnabled(true);
  ui->pb243->setEnabled(true);
  ui->pb244->setEnabled(true);
  ui->pb245->setEnabled(true);
  ui->pb2311->setEnabled(true);
  ui->pb2312->setEnabled(true);
  ui->pb232->setEnabled(true);
  ui->pb2341->setEnabled(true);
  ui->pb2342->setEnabled(true);
  ui->pb233->setEnabled(true);
  ui->pb234->setEnabled(true);
  }


void MainWindow::toggleReturnState(bool active) {
  if (sm->currentState() == s29)
     sm->stateReturn();
  else
     sm->dispatch(29);
  }
