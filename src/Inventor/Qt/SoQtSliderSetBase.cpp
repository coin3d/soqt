/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2009 by Systems in Motion.  All rights reserved.
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
#include <Inventor/Qt/moc_SoQtSliderSetBase.icc>

#include <Inventor/nodes/SoNode.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtSliderSetBase.h>

/*!
  \class SoQtSliderSetBase SoQtSliderSetBase.h Inventor/Qt/SoQtSliderSetBase.h
  \brief The SoQtSliderSetBase class blablabla TODO

  TODO: doc
*/

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtSliderSetBase);

/*!
  TODO: doc
*/

SoQtSliderSetBase::SoQtSliderSetBase(QWidget * parent,
                                     const char * name,
                                     SbBool buildInsideParent,
                                     SoNode * editnode)
: inherited(parent, name, buildInsideParent)
{
  this->node = editnode;
  if (this->node) this->node->ref();
}

/*!
  TODO: doc
*/
SoQtSliderSetBase::~SoQtSliderSetBase()
{
  if (this->node) this->node->unref();
}

/*!
  TODO: doc

  \sa getNode()
 */
void
SoQtSliderSetBase::setNode(SoNode * newNode)
{
  if (this->node) this->node->unref();
  this->node = newNode;
  if (this->node) this->node->ref();
}

/*!
  TODO: doc

  \sa setNode()
 */
SoNode *
SoQtSliderSetBase::getNode(void) const
{
  return this->node;
}
