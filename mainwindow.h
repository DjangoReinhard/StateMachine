/* 
 * **************************************************************************
 * 
 *  file:       mainwindow.h
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainControl;
class PluginHandler;
class ToolBar;


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
 ~MainWindow();

public slots:
  void refreshCounter();

protected:
  void connectUI();
  void createToolbars();

private:
  Ui::MainWindow* ui;  
  MainControl*    ctrl;
  ToolBar*        mainTB;  
  };
#endif // MAINWINDOW_H
