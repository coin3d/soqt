/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

//  $Id$

#ifndef SOQT_LIGHTSLIDERSET_H
#define SOQT_LIGHTSLIDERSET_H

#include <Inventor/Qt/SoQtSliderSet.h>

// *************************************************************************

class SOQT_DLL_EXPORT SoQtLightSliderSet : public SoQtSliderSet {
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
