#ifndef SOQTPLANEVIEWERP_H
#define SOQTPLANEVIEWERP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <qobject.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Qt/viewers/SoGuiPlaneViewerP.h>

class SoQtPlaneViewer;

// ************************************************************************

// This class contains private data and methods used within the
// SoQtPlaneViewer class.

class SoQtPlaneViewerP : public QObject, public SoGuiPlaneViewerP
{
  Q_OBJECT

public:
  SoQtPlaneViewerP(SoQtPlaneViewer * publ);
  ~SoQtPlaneViewerP();

  void constructor(SbBool buildnow);

  struct {
    class QPushButton * x, * y, * z;
    class QPushButton * camera;
  } buttons;

  struct {
    class QPixmap * orthogonal, * perspective;
  } pixmaps;

public slots:
  void xClicked(void);
  void yClicked(void);
  void zClicked(void);
  void cameraToggleClicked(void);
};

// ************************************************************************

#endif // ! SOQTPLANEVIEWERP_H
