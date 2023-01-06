/* 
 * **************************************************************************
 * 
 *  file:       ActionButton.cpp
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
#include <ActionButton.h>
#include <QIcon>
#include <QDebug>


ActionButton::ActionButton(QWidget* parent)
 : QToolButton(parent)
 , a(nullptr) {
  setStyleSheet("QToolButton { border: none; }");
  connect(this, &QAbstractButton::clicked, this, &ActionButton::onClicked);
  }


void ActionButton::onClicked(bool checked) {
  qDebug() << "ActionButton" << text() << "clicked";
  if (a) a->trigger();
  }


void ActionButton::setAction(QAction* a) {
  if (this->a) {
     disconnect(a, &QAction::changed, this, &ActionButton::actionChanged);
     }
  this->a = a;
  setIcon(a->icon());
  setToolTip(a->toolTip());
  setStatusTip(a->statusTip());
  setWhatsThis(a->whatsThis());
  setEnabled(a->isEnabled());

  connect(a, &QAction::changed, this, &ActionButton::actionChanged);
  }


void ActionButton::actionChanged() {
  setIcon(a->icon());
  setEnabled(a->isEnabled());
  setToolTip(a->toolTip());
  setStatusTip(a->statusTip());
  setWhatsThis(a->whatsThis());
  }
