/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*!
  \class SoQtSliderSetBase SoQtSliderSetBase.h Inventor/Qt/SoQtSliderSetBase.h
  \brief The SoQtSliderSetBase class blablabla TODO

  TODO: doc
 */

#include <Inventor/Qt/SoQtSliderSetBase.h>
#include <Inventor/nodes/SoNode.h>

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
