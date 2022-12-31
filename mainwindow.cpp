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
#include <HistoryState.h>
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
 , s231(nullptr)
 , s232(nullptr)
 , s241(nullptr)
 , s242(nullptr)
 , s243(nullptr)
 , s244(nullptr)
 , s245(nullptr)
 , s2311(nullptr)
 , s2312(nullptr)
 , s2313(nullptr)
 , s2314(nullptr)
 , s2321(nullptr)
  {
  ui->setupUi(this);
  createStateMachine();
  connectUI();
  s0Properties(nullptr);
  }


MainWindow::~MainWindow() {
  delete ui;
  delete s2321;
  delete s2314;
  delete s2313;
  delete s2312;
  delete s2311;
  delete s241;
  delete s242;
  delete s243;
  delete s244;
  delete s245;
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
  connect(ui->pb241,  &QPushButton::clicked, sm, [=]{ sm->dispatch(241); });
  connect(ui->pb242,  &QPushButton::clicked, sm, [=]{ sm->dispatch(242); });
  connect(ui->pb243,  &QPushButton::clicked, sm, [=]{ sm->dispatch(243); });
  connect(ui->pb244,  &QPushButton::clicked, sm, [=]{ sm->dispatch(244); });
  connect(ui->pb245,  &QPushButton::clicked, sm, [=]{ sm->dispatch(245); });
  connect(ui->pb2311, &QPushButton::clicked, sm, [=]{ sm->dispatch(2311); });
  connect(ui->pb2312, &QPushButton::clicked, sm, [=]{ sm->dispatch(2312); });
  connect(ui->pb2313, &QPushButton::clicked, sm, [=]{ sm->dispatch(2313); });
  connect(ui->pb2314, &QPushButton::clicked, sm, [=]{ sm->dispatch(2314); });
  connect(ui->pb2321, &QPushButton::clicked, sm, [=]{ sm->dispatch(2321); });

  connect(s2,  &State::onEntry, this, &MainWindow::s2Properties);
  connect(s23, &State::onEntry, this, &MainWindow::s23Properties);
  }


void MainWindow::createStateMachine() {
  sm = new StateMachine();
  s2    = new State("S2",  sm);
  s21   = new State("S21", s2);   // 1
  s22   = new State("S22", s2);   // 2
  s23   = new HistoryState("S23", s2);   // 3
  s24   = new State("S24", s2);
  s25   = new State("S25", s2);   // 5
  s26   = new State("S26", s2);   // 9 - error state?!?
  s231  = new State("S231", s23);
  s232  = new State("S232", s23);
  s241  = new State("S241", s24);  // a
  s242  = new State("S242", s24);  // b
  s243  = new State("S243", s24);  // c
  s244  = new State("S244", s24);  // d
  s245  = new State("S245", s24);  // e
  s2311 = new State("S2311", s231); // o
  s2312 = new State("S2312", s231); // p
  s2313 = new State("S2313", s231); // q
  s2314 = new State("S2314", s231); // r
  s2321 = new State("S2321", s231); // z

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

  s21->addTransition(22,  s22);
  s21->addTransition(25,  s25);
  s21->addTransition(241, s241);
  s21->addTransition(242, s242);
  s21->addTransition(243, s243);
  s21->addTransition(244, s244);
  s21->addTransition(245, s245);
  HistoryStateTransition* hst = new HistoryStateTransition(2311, s21, s2311, s23);

  s21->addTransition(hst);
  hst = new HistoryStateTransition(2312, s21, s2312, s23);
  s21->addTransition(hst);
  hst = new HistoryStateTransition(2313, s21, s2313, s23);
  s21->addTransition(hst);
  hst = new HistoryStateTransition(2314, s21, s2314, s23);
  s21->addTransition(hst);
  hst = new HistoryStateTransition(2321, s21, s2321, s23);
  s21->addTransition(hst);
  hst = new HistoryStateTransition(23, s21, s23, s23, false);
  s21->addTransition(hst);

  s22->addTransition(21,  s21);
  s22->addTransition(25,  s25);
  s22->addTransition(241, s241);
  s22->addTransition(242, s242);
  s22->addTransition(243, s243);
  s22->addTransition(244, s244);
  s22->addTransition(245, s245);
  hst = new HistoryStateTransition(2311, s22, s2311, s23);
  s22->addTransition(hst);
  hst = new HistoryStateTransition(2312, s22, s2312, s23);
  s22->addTransition(hst);
  hst = new HistoryStateTransition(2313, s22, s2313, s23);
  s22->addTransition(hst);
  hst = new HistoryStateTransition(2314, s22, s2314, s23);
  s22->addTransition(hst);
  hst = new HistoryStateTransition(2321, s22, s2321, s23);
  s22->addTransition(hst);
  hst = new HistoryStateTransition(23, s22, s23, s23, false);
  s22->addTransition(hst);

  s23->addTransition(21,   s21);
  s23->addTransition(25,   s25);
  s23->addTransition(2311, s2311);
  s23->addTransition(2312, s2312);
  s23->addTransition(2313, s2313);
  s23->addTransition(2314, s2314);
  s23->addTransition(2321, s2321);
  s23->addTransition(241,  s241);
  s23->addTransition(242,  s242);
  s23->addTransition(243,  s243);
  s23->addTransition(244,  s244);
  s23->addTransition(245,  s245);

  s24->addTransition(21,  s21);
  s24->addTransition(22,  s22);
  s24->addTransition(25,  s25);
  hst = new HistoryStateTransition(2311, s24, s2311, s23);
  s24->addTransition(hst);
  hst = new HistoryStateTransition(2312, s24, s2312, s23);
  s24->addTransition(hst);
  hst = new HistoryStateTransition(2313, s24, s2313, s23);
  s24->addTransition(hst);
  hst = new HistoryStateTransition(2314, s24, s2314, s23);
  s24->addTransition(hst);
  hst = new HistoryStateTransition(2321, s24, s2321, s23);
  s24->addTransition(hst);
  hst = new HistoryStateTransition(23, s24, s23, s23, false);
  s24->addTransition(hst);
  }


void MainWindow::s0Properties(StateTransition* trans) {
  qDebug() << "s0Properties() ...";
  ui->pb2->setEnabled(true);
  ui->pb21->setEnabled(false);
  ui->pb22->setEnabled(false);
  ui->pb23->setEnabled(false);
  ui->pb25->setEnabled(false);
  ui->pb241->setEnabled(false);
  ui->pb242->setEnabled(false);
  ui->pb243->setEnabled(false);
  ui->pb244->setEnabled(false);
  ui->pb245->setEnabled(false);
  ui->pb2311->setEnabled(false);
  ui->pb2312->setEnabled(false);
  ui->pb2313->setEnabled(false);
  ui->pb2314->setEnabled(false);
  ui->pb2321->setEnabled(false);
  }


void MainWindow::s2Properties(StateTransition* trans) {
  qDebug() << "s2Properties() ...";
  ui->pb2->setEnabled(true);
  ui->pb21->setEnabled(true);
  ui->pb22->setEnabled(true);
  ui->pb23->setEnabled(true);
  ui->pb25->setEnabled(true);
  ui->pb241->setEnabled(true);
  ui->pb242->setEnabled(true);
  ui->pb243->setEnabled(true);
  ui->pb244->setEnabled(true);
  ui->pb245->setEnabled(true);
  ui->pb2311->setEnabled(false);
  ui->pb2312->setEnabled(false);
  ui->pb2313->setEnabled(false);
  ui->pb2314->setEnabled(false);
  ui->pb2321->setEnabled(false);
  }


void MainWindow::s23Properties(StateTransition* trans) {
  qDebug() << "s23Properties() ...";
  ui->pb2->setEnabled(true);
  ui->pb21->setEnabled(true);
  ui->pb22->setEnabled(true);
  ui->pb23->setEnabled(true);
  ui->pb25->setEnabled(true);
  ui->pb241->setEnabled(true);
  ui->pb242->setEnabled(true);
  ui->pb243->setEnabled(true);
  ui->pb244->setEnabled(true);
  ui->pb245->setEnabled(true);
  ui->pb2311->setEnabled(true);
  ui->pb2312->setEnabled(true);
  ui->pb2313->setEnabled(true);
  ui->pb2314->setEnabled(true);
  ui->pb2321->setEnabled(true);
  }
