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

static const char rcsid[] =
  "$Id$";

/*!
  \class SoQtInputFocus SoQtInputFocus.h Inventor/Qt/devices/SoQtInputFocus.h
  \brief The SoQtInputFocus class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>


/*!
  Constructor.
*/
SoQtInputFocus::SoQtInputFocus(soqtEventMask mask)
{
  this->mask = mask;
}

/*!
  Destructor.
*/
SoQtInputFocus::~SoQtInputFocus()
{
}

/*!
  FIXME: write function documentation
*/
void
SoQtInputFocus::enable(QWidget * /*w*/, SoQtEventHandler /*f*/, void * /*data*/)
{
  SOQT_STUB();
}

/*!
  FIXME: write function documentation
*/
void
SoQtInputFocus::disable(QWidget * /*w*/, SoQtEventHandler /*f*/, void * /*data*/)
{
  SOQT_STUB();
}

/*!
  FIXME: write function documentation
*/
const SoEvent *
SoQtInputFocus::translateEvent(QEvent * /*event*/)
{
  SOQT_STUB();
  return NULL;
}

// *************************************************************************

static const char * getSoQtInputFocusRCSId(void) { return rcsid; }

