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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

/*!
  \class SoQtSliderSetBase SoQtSliderSetBase.h Inventor/Qt/SoQtSliderSetBase.h
  \brief The SoQtSliderSetBase class blablabla TODO

  TODO: doc
 */

#include <Inventor/nodes/SoNode.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtSliderSetBase.h>


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
