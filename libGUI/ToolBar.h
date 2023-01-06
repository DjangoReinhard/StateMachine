/* 
 * **************************************************************************
 * 
 *  file:       ToolBar.h
 *  project:    AppStateMachine
 *  subproject: main application
 *  purpose:    sample for hierarchic state machine with history support
 *  created:    5.1.2023 by Django Reinhard
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
#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QDockWidget>
class QAction;
class ActionButton;


class ToolBar : public QDockWidget
{
  Q_OBJECT
public:
  explicit ToolBar(const QString& name, QWidget *parent = nullptr);
  virtual ~ToolBar();

  void setAction(int i, QAction* a);
  void setupToolBar();

private:
  QList<ActionButton*> buttons;
  QWidget* tw;
  };
#endif // TOOLBAR_H
