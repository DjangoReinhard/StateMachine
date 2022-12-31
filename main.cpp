/* 
 * **************************************************************************
 * 
 *  file:       main.cpp
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
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[]) {
  QApplication      a(argc, argv);
  QTranslator       translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();

  for (const QString &locale : uiLanguages) {
      const QString baseName = "StateMachine_" + QLocale(locale).name();

      if (translator.load(":/i18n/" + baseName)) {
         a.installTranslator(&translator);
         break;
         }
      }
  MainWindow w;

  w.show();

  return a.exec();
  }
