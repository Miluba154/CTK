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

#ifndef __ctkDICOMQueryWidget_h
#define __ctkDICOMQueryWidget_h

#include "ctkDICOMWidgetsExport.h"

// Qt includes 
#include <QWidget>
#include <QMap>
#include <QVariant>


class ctkDICOMQueryWidgetPrivate;
/// \ingroup DICOM_Widgets
class CTK_DICOM_WIDGETS_EXPORT ctkDICOMQueryWidget : public QWidget
{
Q_OBJECT;
public:

  explicit ctkDICOMQueryWidget(QWidget* parent=0);
  virtual ~ctkDICOMQueryWidget();

public Q_SLOTS:
  void query();
  void cancel();
  void onServerParametersChanged(const QMap<QString,QVariant> &);

Q_SIGNALS:

  void startedQuery();
  /// Signal to emit when cancel button pressed (after studiesRetrieved is emitted)
  void canceled();
 /// Signal to emit remaining steps of the query process
  void progress(int remainingSteps);
  
protected Q_SLOTS:
  void onQueryProgressChanged(int remainingSteps);
};

#endif
