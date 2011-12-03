#ifndef SOQTFULLVIEWERP_H
#define SOQTFULLVIEWERP_H

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <Inventor/Qt/viewers/SoGuiFullViewerP.h>
#include <qobject.h>

class QLabel;
class QLayout;
class QSlider;
class QLineEdit;
class QPushButton;
class QWidget;
class SoQtFullViewer;
class SoQtThumbWheel;

// ************************************************************************

// This class contains private data and methods used within the
// SoQtFullViewer class.

class SoQtFullViewerP : public QObject, public SoGuiFullViewerP
{
  Q_OBJECT

public:
  SoQtFullViewerP(SoQtFullViewer * publ);
  ~SoQtFullViewerP();

public slots:
  // Thumbwheels.
  void leftWheelPressed(void);
  void leftWheelChanged(float value);
  void leftWheelReleased(void);
  void rightWheelPressed(void);
  void rightWheelChanged(float value);
  void rightWheelReleased(void);
  void bottomWheelPressed(void);
  void bottomWheelChanged(float value);
  void bottomWheelReleased(void);

  // Button row.
  void interactbuttonClicked();
  void viewbuttonClicked();
  void homebuttonClicked();
  void sethomebuttonClicked();
  void viewallbuttonClicked();
  void seekbuttonClicked();

  // Menu items.
  void selectedViewing();
  void selectedDecoration();
  void selectedHeadlight();

  // Generic slots.
  void increaseInteractiveCount();
  void decreaseInteractiveCount();

public:
  static void setThumbWheelValue(void * wheel, float val);

  void showDecorationWidgets(SbBool onOff);

  void layoutAppButtons(QWidget * form);

  // Return pointer to pushbutton in right-side decoration bar.
  QPushButton * getViewerbutton(const int idx)
  {
    return (QPushButton *)this->viewerbuttons->get(idx);
  }

  QWidget * viewerwidget, * canvas;
  QWidget * interactbutton, * viewbutton;
  SbBool decorations;
  SbString menutitle;
  SbBool menuenabled;
  QLayout * mainlayout;
  QLayout * appbuttonlayout;
  QWidget * appbuttonform;
  SbPList * appbuttonlist;
  SbPList * viewerbuttons;
};

// ************************************************************************

#endif // ! SOQTFULLVIEWERP_H
