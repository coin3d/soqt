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

#include <Inventor/Qt/SoQtCursor.h>

/*!
  \internal
  Set cursor graphics according to mode.
*/
void
SoQtFlyViewerP::updateCursorRepresentation(void)
{
  // FIXME: with the new So@Gui@Cursor class, this has actually become
  // a possibly generic method for all So* toolkits. Move to common
  // code. 20011125 mortene.

  if (!this->viewer->isCursorEnabled()) {
    this->viewer->setComponentCursor(SoQtCursor::getBlankCursor());
    return;
  }

  switch (this->viewermode) {
  case SoQtFlyViewerP::FLYING:
    this->viewer->setComponentCursor(SoQtCursor(SoQtCursor::DEFAULT));
    break;

  case SoQtFlyViewerP::WAITING_FOR_SEEK:
    this->viewer->setComponentCursor(SoQtCursor(SoQtCursor::CROSSHAIR));
    break;

  case SoQtFlyViewerP::WAITING_FOR_UP_PICK:
    this->viewer->setComponentCursor(SoQtCursor(SoQtCursor::UPARROW));
    break;

  default:
    // FIXME: enable again when implementation completed. 20010910 mortene.
//      assert(0);
    SOQT_STUB();
    break;
  }
} // setCursorRepresentation()
