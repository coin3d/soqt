#ifndef SOQTEXAMINERVIEWERP_H
#define SOQTEXAMINERVIEWERP_H

/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <qobject.h>
#include <Inventor/SbBasic.h>
#include "SoGuiExaminerViewerP.h"

class SoQtExaminerViewer;

// ************************************************************************

// This class contains private data and methods used within the
// SoQtExaminerViewer class.

class SoQtExaminerViewerP : public QObject, public SoGuiExaminerViewerP
{
  Q_OBJECT

public:
  SoQtExaminerViewerP(SoQtExaminerViewer * publ);
  ~SoQtExaminerViewerP();

  void constructor(SbBool buildNow);

  QPixmap * orthopixmap, * perspectivepixmap;
  class QPushButton * cameratogglebutton;

public slots:
  // viewer buttons row:
  void cameratoggleClicked(void);
};

// ************************************************************************

#endif // ! SOQTEXAMINERVIEWERP_H
