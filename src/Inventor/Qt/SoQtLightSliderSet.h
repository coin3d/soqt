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

#ifndef SOQT_LIGHTSLIDERSET_H
#define SOQT_LIGHTSLIDERSET_H

#include <Inventor/Qt/SoQtSliderSet.h>

// *************************************************************************

class SOQT_DLL_API SoQtLightSliderSet : public SoQtSliderSet {
  SOQT_OBJECT_HEADER(SoQtLightSliderSet, SoQtSliderSet);
  Q_OBJECT

public:
  SoQtLightSliderSet(QWidget * parent = NULL,
                     const char * name = NULL,
                     SbBool embed = TRUE,
                     SoNode * editnode = NULL);

  ~SoQtLightSliderSet(void);

}; // class SoQtLightSliderSet

// *************************************************************************

#endif // ! SOQT_LIGHTSLIDERSET_H
