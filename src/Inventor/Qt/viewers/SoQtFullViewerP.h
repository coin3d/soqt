/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQTFULLVIEWERP_H
#define SOQTFULLVIEWERP_H

#include <SoGuiFullViewerP.h>
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
  void helpbuttonClicked();
  void homebuttonClicked();
  void sethomebuttonClicked();
  void viewallbuttonClicked();
  void seekbuttonClicked();

  // Menu items.
  void selectedViewing();
  void selectedDecoration();
  void selectedHeadlight();
  void copyviewSelected();
  void pasteviewSelected();

  // Generic slots.
  void increaseInteractiveCount();
  void decreaseInteractiveCount();

public:
  static void setThumbWheelValue(void * wheel, float val);

  void showDecorationWidgets(SbBool onOff);

  void layoutAppButtons(QWidget * form);

  void setCameraZoom(const float zoom);
  float getCameraZoom(void);

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
