/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#include <qmetaobject.h>
#include <Inventor/Qt/moc_SoQtMaterialSliderSet.icc>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtMaterialSliderSet.h>

/*!
  \class SoQtMaterialSliderSet SoQtMaterialSliderSet.h Inventor/Qt/SoQtMaterialSliderSet.h
  \brief The SoQtMaterialSliderSet class blablabla TODO

  TODO: doc
*/

SOQT_OBJECT_SOURCE(SoQtMaterialSliderSet);

/*!
  TODO: doc
 */
SoQtMaterialSliderSet::SoQtMaterialSliderSet(QWidget * parent,
                                             const char * name,
                                             SbBool buildInsideParent,
                                             SoNode * editnode)
  : inherited(parent, name, buildInsideParent, editnode)
{
}

/*!
  TODO: doc
 */
SoQtMaterialSliderSet::~SoQtMaterialSliderSet()
{
}
