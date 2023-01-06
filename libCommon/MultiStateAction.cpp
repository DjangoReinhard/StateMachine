/*
 * **************************************************************************
 *
 *  file:       MultiStateAction.cpp
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
#include <MultiStateAction.h>
#include <QDebug>


MultiStateAction::MultiStateAction(const QIcon& enabledIcon, const QIcon& activeIcon, const QString& name, QObject *parent)
 : QAction(enabledIcon, name, parent)
 , enabledIcon(enabledIcon)
 , activeIcon(activeIcon)
 , state(Active) {
  }


MultiStateAction::~MultiStateAction() {
  }


ActionState MultiStateAction::actionState() const {
  return state;
  }


void MultiStateAction::setInactiveIcon(const QIcon &icon) {
  inActiveIcon = icon;
  }


void MultiStateAction::setActionState(ActionState state) {
  switch (state) {
    case InActive:
//         qDebug() << "set action state to InActive";
         setIcon(inActiveIcon);
         setEnabled(false);
         break;
    case Disabled:
//         qDebug() << "set action state to Disabled";
         setIcon(enabledIcon);
         setEnabled(false);
         break;
    case Enabled:
//         qDebug() << "set action state to Enabled";
         setIcon(enabledIcon);
         setEnabled(true);
         break;
    case Active:
//         qDebug() << "set action state to Active";
         setIcon(activeIcon);
         setEnabled(true);
         break;
    default: return;
    }
  this->state = state;
  }

QIcon MultiStateAction::inActiveIcon;
