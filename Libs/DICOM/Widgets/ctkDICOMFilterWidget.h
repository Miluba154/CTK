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

#ifndef __ctkDICOMFilterWidget_h
#define __ctkDICOMFilterWidget_h

// Qt includes 
#include <QWidget>

#include "ctkDICOMWidgetsExport.h"

class ctkDICOMFilterWidgetPrivate;

/// \ingroup DICOM_Widgets
class CTK_DICOM_WIDGETS_EXPORT ctkDICOMFilterWidget : public QWidget
{
    Q_OBJECT
public:
  typedef QWidget Superclass;
  explicit ctkDICOMFilterWidget(QWidget* parent=0);
  virtual ~ctkDICOMFilterWidget();
  
  /// return map of field names and values
  QMap<QString,QVariant> parameters();

protected:
  QScopedPointer<ctkDICOMFilterWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(ctkDICOMFilterWidget);
  Q_DISABLE_COPY(ctkDICOMFilterWidget);

Q_SIGNALS:
  /// This signal is emitted when any of the search parameters changed.
  void parameterChanged();

  /// This signal is emitted when the user hits return in any of the line edits
  void returnPressed();

public Q_SLOTS:
  void onReturnPressed();

protected Q_SLOTS:
  void startTimer();
};

#endif
