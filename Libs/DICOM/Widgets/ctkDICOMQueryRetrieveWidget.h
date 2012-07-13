/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMQueryRetrieveWidget_h
#define __ctkDICOMQueryRetrieveWidget_h

#include "ctkDICOMWidgetsExport.h"

// Qt includes 
#include <QWidget>

/// Class connects ctkDICOMQueryWidget(my one), ctkDICOMRetrieveWidget,
/// ctkServerNodeWidget, QTreeView with image entries, ctkDICOMFilterWidget (old ctkDICOMQueryWidget)
class ctkDICOMQueryRetrieveWidgetPrivate;

/// \ingroup DICOM_Widgets
class CTK_DICOM_WIDGETS_EXPORT ctkDICOMQueryRetrieveWidget : public QWidget
{
Q_OBJECT;
public:
  explicit ctkDICOMQueryRetrieveWidget(QWidget* parent=0);
  virtual ~ctkDICOMQueryRetrieveWidget();
  
  /// enable or disable ctk progress bars
  void useProgressDialog(bool enable);

public Q_SLOTS:
  
Q_SIGNALS:
  /// Signal emit when studies have been retrieved (user clicked on the
  /// "Retrieve" button) or when the widget is cancelled (user clicked on the
  /// "Cancel" button).

protected Q_SLOTS:
  void onRetrieveProgressChanged(int remainingSteps);


};

#endif
