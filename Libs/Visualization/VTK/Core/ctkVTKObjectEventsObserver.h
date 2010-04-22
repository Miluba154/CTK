/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

#ifndef __ctkVTKObjectEventsObserver_h
#define __ctkVTKObjectEventsObserver_h

/// CTK includes
#include <ctkPimpl.h>

/// Qt includes
#include <QObject>
#include <QList>
#include <QString>

/// VTK includes
#include <vtkCommand.h>

#include "CTKVisualizationVTKCoreExport.h"

class ctkVTKConnection;
class vtkObject;
class ctkVTKObjectEventsObserverPrivate;

class CTK_VISUALIZATION_VTK_CORE_EXPORT ctkVTKObjectEventsObserver : public QObject
{
Q_OBJECT

public:
  typedef QObject Superclass;
  explicit ctkVTKObjectEventsObserver(QObject* parent = 0);
  virtual ~ctkVTKObjectEventsObserver(){}

  virtual void printAdditionalInfo();

  /// 
  /// Enable / Disable all ctkVTKConnections
  void setAllEnabled( bool enable );
  bool allEnabled()const;

  /// 
  /// Add a connection, an Id allowing to uniquely identify the connection is also returned
  QString addConnection(vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, const char* qt_slot, float priority = 0.0);

  ///
  /// Utility function that remove a connection on old_vtk_obj and add a connection
  /// to vtk_obj (same event, object, slot, priority)
  QString addConnection(vtkObject* old_vtk_obj, vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, const char* qt_slot, float priority = 0.0);

  ///
  /// Utility function that remove a connection on old_vtk_obj and add a connection
  /// to vtk_obj (same event, object, slot, priority)
  QString reconnection(vtkObject* vtk_obj, unsigned long vtk_event,
                       const QObject* qt_obj, const char* qt_slot, 
                       float priority = 0.0);

  /// 
  /// Remove a connection
  int removeConnection(vtkObject* vtk_obj, unsigned long vtk_event = vtkCommand::NoEvent,
                       const QObject* qt_obj = 0, const char* qt_slot = 0);

  /// 
  /// Remove all the connections
  inline int removeAllConnections();

  ///
  /// Temporarilly block all the connection
  void blockAllConnections(bool block);
  
  /// 
  /// Block/Unblock a connection.
  int blockConnection(bool block, vtkObject* vtk_obj,
                      unsigned long vtk_event, const QObject* qt_obj);
  void blockConnection(const QString& id, bool blocked);

private:
  CTK_DECLARE_PRIVATE(ctkVTKObjectEventsObserver);

};

int ctkVTKObjectEventsObserver::removeAllConnections()
{
  return this->removeConnection(0);
}

#endif