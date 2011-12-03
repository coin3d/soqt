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

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtWalkViewer.h>
#include <Inventor/Qt/viewers/SoGuiWalkViewerP.h>

// ************************************************************************

SOQT_OBJECT_SOURCE(SoQtWalkViewer);

// ************************************************************************

#define PRIVATE(ptr) ptr->pimpl
#define PUBLIC(ptr) ptr->pub

// ************************************************************************

#ifndef DOXYGEN_SKIP_THIS

class SoQtWalkViewerP : public SoGuiWalkViewerP {
public:
  SoQtWalkViewerP(SoQtWalkViewer * o)
    : SoGuiWalkViewerP(o)
  {
  }

  void constructor(void);
};

void
SoQtWalkViewerP::constructor(void)
{
}

#endif // DOXYGEN_SKIP_THIS

// ************************************************************************

/*!
  The public constructor.
*/

SoQtWalkViewer::SoQtWalkViewer(QWidget * parent,
                               const char * name,
                               SbBool embed,
                               SoQtFullViewer::BuildFlag flag,
                               SoQtViewer::Type type)
  : inherited(parent, name, embed, flag, type, TRUE)
{
  PRIVATE(this) = new SoQtWalkViewerP(this);
  PRIVATE(this)->constructor();
}

// ************************************************************************

/*!
  A protected constructor.
*/

SoQtWalkViewer::SoQtWalkViewer(QWidget * parent,
                               const char * name,
                               SbBool embed,
                               SoQtFullViewer::BuildFlag flag,
                               SoQtViewer::Type type,
                               SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtWalkViewerP(this);
  PRIVATE(this)->constructor();
}

// ************************************************************************

/*!
  The destructor.
*/

SoQtWalkViewer::~SoQtWalkViewer()
{
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setViewing(SbBool enable)
{
}

// ************************************************************************

// Documented in superclass.
void
SoQtWalkViewer::setCamera(SoCamera * camera)
{
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCursorEnabled(SbBool enable)
{
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCameraType(SoType type)
{
}

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultWidgetName(void) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
}

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultTitle(void) const
{
  static const char defaultTitle[] = "Walk Viewer";
  return defaultTitle;
}

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultIconTitle(void) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::processEvent(QEvent * event)
{
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setSeekMode(SbBool enable)
{
}

// ************************************************************************

// Documented in superclass.
void
SoQtWalkViewer::actualRedraw(void)
{
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::rightWheelMotion(float value)
{
}

// ************************************************************************

/*!
*/

QWidget *
SoQtWalkViewer::buildLeftTrim(QWidget * parent)
{
  return NULL;
}

// ************************************************************************

#undef PRIVATE
#undef PUBLIC
