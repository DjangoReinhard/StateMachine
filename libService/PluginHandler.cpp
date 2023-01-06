/* 
 * **************************************************************************
 * 
 *  file:       PluginHandler.cpp
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
#include <PluginHandler.h>
#include <IApplicationPage.h>
#include <QPluginLoader>
#include <QFileInfo>
#include <QDebug>


PluginHandler::PluginHandler(const QFileInfo& pluginPath)
 : pluginDir(pluginPath.absoluteFilePath())  {
  qDebug() << "plugin dir is:" << pluginDir.absolutePath();
  }


int PluginHandler::loadPlugins(QList<IApplicationPage*>& plugins) {
  const auto entryList = pluginDir.entryList(QDir::Files);

  for (const QString& fileName : entryList) {
      QString path = pluginDir.absoluteFilePath(fileName);

      if (fileName.startsWith("lib")
       && fileName.endsWith(".so")) {
         qDebug() << "found shared lib:" << path;
         QPluginLoader loader(path);
         QObject*      plugin = loader.instance();
         QString       name   = fileName.mid(3, fileName.size() - 6);

         if (plugin) {
            auto iPlugin = qobject_cast<IApplicationPage*>(plugin);

            qDebug() << name << "loaded successfully";
            if (iPlugin) {
               qDebug() << "\tOK, plugin is of expected type!";

               plugins.append(iPlugin);
               }
            else {
               qDebug() << "\tOUPS - plugin is NOT of expected type!";
               }
            }
         else qDebug() << name << "loading failed with: " << loader.errorString();
         }
      }
  return plugins.size();
  }


