/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQT_DEVICE_H
#define SOQT_DEVICE_H

#include <Inventor/SbLinear.h>
#include <Inventor/Qt/SoQtObject.h>
#include <qevent.h>

class QWidget;

class SbPList;
class SoEvent;

// *************************************************************************

class SOQT_DLL_API SoQtDevice : public SoQtObject {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtDevice, SoQtObject);

public:
  typedef void SoQtEventHandler(QWidget *, void *, QEvent *, bool *);

  SoQtDevice(void);
  virtual ~SoQtDevice();

  virtual void enable(QWidget * w, SoQtEventHandler * handler, void * closure) = 0;
  virtual void disable(QWidget * w, SoQtEventHandler * handler, void * closure) = 0;

  virtual const SoEvent * translateEvent(QEvent * event) = 0;

  void setWindowSize(const SbVec2s size);
  SbVec2s getWindowSize(void) const;

  static void initClasses(void);

protected:
  void setEventPosition(SoEvent * event, int x, int y) const;
  static SbVec2s getLastEventPosition(void);

  void addEventHandler(QWidget *, SoQtEventHandler *, void *);
  void removeEventHandler(QWidget *, SoQtEventHandler *, void *);
  void invokeHandlers(QEvent * event);

private:
  class SoQtDeviceP * pimpl;
  friend class SoQtDeviceP;
};

// *************************************************************************

#endif // ! SOQT_DEVICE_H
