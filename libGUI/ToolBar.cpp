/* 
 * **************************************************************************
 * 
 *  file:       ToolBar.cpp
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
#include <ToolBar.h>
#include <ActionButton.h>
#include <QLayout>
#include <QAction>


ToolBar::ToolBar(const QString& name, QWidget *parent)
 : QDockWidget(name, parent)
 , tw(new QWidget(this)) {
  setupToolBar();
  setTitleBarWidget(tw);
  }


ToolBar::~ToolBar() {
  }


void ToolBar::setAction(int i, QAction *a) {
  assert(a != nullptr);
  buttons.at(i)->setAction(a);
  }


void ToolBar::setupToolBar() {
  QWidget* cw = new QWidget(this);
  QBoxLayout* l = new QBoxLayout(QBoxLayout::LeftToRight);
  ActionButton* a;

  l->setSpacing(0);
  for (int i=0; i < 12; ++i) {
      a = new ActionButton();

      a->setIconSize(QSize(60, 60));
      switch (i) {
        case 0: a->setShortcut(Qt::Key_F1); break;
        case 1: a->setShortcut(Qt::Key_F2); break;
        case 2: a->setShortcut(Qt::Key_F3); break;
        case 3: a->setShortcut(Qt::Key_F4); break;
        case 4: a->setShortcut(Qt::Key_F5); break;
        case 5: a->setShortcut(Qt::Key_F6); break;
        case 6: a->setShortcut(Qt::Key_F7); break;
        case 7: a->setShortcut(Qt::Key_F8); break;
        case 8: a->setShortcut(Qt::Key_F9); break;
        case 9: a->setShortcut(Qt::Key_F10); break;
        case 10: a->setShortcut(Qt::Key_F11); break;
        case 11: a->setShortcut(Qt::Key_F12); break;
        }
      l->addWidget(a);
      buttons.append(a);
      }
  cw->setLayout(l);
  setWidget(cw);
  }
