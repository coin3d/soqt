/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
