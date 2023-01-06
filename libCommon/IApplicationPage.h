/* 
 * **************************************************************************
 * 
 *  file:       CenterPageInterface.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    22.1.2022 by Django Reinhard
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
#ifndef CENTERPAGEINTERFACE_H
#define CENTERPAGEINTERFACE_H
#include <QtPlugin>
class QAction;


class IApplicationPage
{
public:
  virtual ~IApplicationPage() = default;

  virtual QAction* viewAction()     = 0;
  virtual QString  pageName() const = 0;
  };

QT_BEGIN_NAMESPACE
#define IApplicationPage_iid "de.schwarzrot.FalconView.IApplicationPage/0.1"
Q_DECLARE_INTERFACE(IApplicationPage, IApplicationPage_iid)
QT_END_NAMESPACE

#endif // CENTERPAGEINTERFACE_H
