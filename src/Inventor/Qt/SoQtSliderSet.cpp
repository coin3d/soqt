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

#include <qmetaobject.h>
#include <moc_SoQtSliderSet.icc>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtSliderSet.h>

/*!
  \class SoQtSliderSet SoQtSliderSet.h Inventor/Qt/SoQtSliderSet.h
  \brief The SoQtSliderSet class blablabla TODO

  TODO: doc
*/

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtSliderSet);

/*!
  TODO: doc
*/

SoQtSliderSet::SoQtSliderSet(QWidget * parent,
                             const char * name,
                             SbBool buildInsideParent,
                             SoNode * editnode)
: inherited(parent, name, buildInsideParent, editnode)
{
}

/*!
  TODO: doc
*/

SoQtSliderSet::~SoQtSliderSet()
{
}

