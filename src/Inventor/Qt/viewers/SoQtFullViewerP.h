#ifndef SOQTFULLVIEWERP_H
#define SOQTFULLVIEWERP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
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
