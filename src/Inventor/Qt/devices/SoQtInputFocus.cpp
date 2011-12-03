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

// FIXME: this device class has not been implemented yet. 20020625 mortene.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>
#include <Inventor/Qt/devices/SoGuiInputFocusP.h>

#include <qglobal.h>

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

class SoQtInputFocusP : public SoGuiInputFocusP {
public:
  SoQtInputFocusP(SoQtInputFocus * p) : SoGuiInputFocusP(p) { }
};

// *************************************************************************

SoQtInputFocus::SoQtInputFocus(int mask)
{
  PRIVATE(this) = new SoQtInputFocusP(this);
  PRIVATE(this)->eventmask = mask;
}

SoQtInputFocus::~SoQtInputFocus()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtInputFocus::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  SOQT_STUB();
}

void
SoQtInputFocus::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  SOQT_STUB();
}

// *************************************************************************

const SoEvent *
SoQtInputFocus::translateEvent(QEvent *)
{
  SOQT_STUB();
  return NULL;
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
