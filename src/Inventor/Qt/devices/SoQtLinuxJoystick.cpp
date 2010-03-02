/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

/*!
  \class SoQtLinuxJoystick Inventor/Qt/devices/SoQtLinuxJoystick.h
  \brief The SoQtLinuxJoystick class is for enabling use of joysticks with
  SoQt through the Linux Joystick driver.
  \ingroup devices

  This class is not included with Open Inventor, but is an SoQt-specific
  extension.
*/

// FIXME: joystick support has been temporary disabled.
//
// This should implement support for the Linux Joystick driver, which
// means you can connect e.g. a Spaceball 4000 FLX to your serial port
// and get Motion3/SpaceballButton events sent into the scene graph.
// See http://www.suse.cz/development/joystick/ for information on the
// driver.
//
// 20020703 mortene.

#include <unistd.h>
#include <stdlib.h>

#include <qsocketnotifier.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SbPList.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>
#include <Inventor/events/SoMotion3Event.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>

#include <Inventor/Qt/devices/SoQtLinuxJoystick.h>
#include <Inventor/Qt/devices/SoQtLinuxJoystickP.h>
#include <qmetaobject.h>
#include <Inventor/Qt/devices/moc_SoQtLinuxJoystickP.icc>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#ifndef HAVE_JOYSTICK_LINUX
#error Trying to compile unsupported device.
#endif // HAVE_JOYSTICK_LINUX

#ifdef HAVE_JOYSTICK_LINUX
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#endif

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtLinuxJoystick);

// *************************************************************************

SbBool SoQtLinuxJoystick::enabled = FALSE;

// *************************************************************************

/*!
  \enum SoQtLinuxJoystick::Events
  FIXME: write doc
*/

/*!
  \var SoQtLinuxJoystick::Events SoQtLinuxJoystick::ALL_EVENTS
  FIXME: write doc
*/

// *************************************************************************

/*!
  FIXME: write doc
*/

SoQtLinuxJoystick::SoQtLinuxJoystick(int events)
{
  this->events = events;
  this->notifier = NULL;
  this->focusToWindow = FALSE;
  this->joydev = 0;
//  this->joyid = (XtInputId) 0;
  this->numaxes = 0;
  this->axisvalues = NULL;
  this->numbuttons = 0;
  this->buttonvalues = NULL;
  this->name = NULL;
  this->rotationScaleFactor = M_PI / float(3*0x10000);
  this->translationScaleFactor = M_PI / float(0x10000);
  this->motion3Event = NULL;
  this->buttonEvent = NULL;
}

/*!
  FIXME: write doc
*/

SoQtLinuxJoystick::~SoQtLinuxJoystick()
{
  delete this->notifier;
  if (this->joydev != 0)
    close(this->joydev);

  delete [] this->name;
  delete [] this->axisvalues;
  delete [] this->buttonvalues;

  delete this->motion3Event;
  delete this->buttonEvent;
}

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtLinuxJoystick::enable(QWidget * widget,
                          SoQtEventHandler * handler,
                          void * closure)
{
  if (! SoQtLinuxJoystick::enabled) {
    const char * devpathname = SoQtLinuxJoystickP::getDevicePathName();
    this->joydev = open(devpathname, O_RDONLY | O_NONBLOCK);
    if (joydev <= 0) {
      SoDebugError::post("SoQtLinuxJoystick::enable",
        "failed to open device '%s'...", devpathname);
      this->joydev = 0;
      return;
    }
    char char_return;
    int int_return;

    if (ioctl(this->joydev, JSIOCGAXES, &char_return) >= 0) {
      this->numaxes = char_return;
    } else {
      SoDebugError::post("SoQtLinuxJoystick::enable",
        "ioctl(JSIOCGAXES) failed");
    }

    if (ioctl(this->joydev, JSIOCGBUTTONS, &char_return) >= 0) {
      this->numbuttons = char_return;
    } else {
      SoDebugError::post("SoQtLinuxJoystick::enable",
        "ioctl(JSIOCGBUTTONS) failed");
    }

    char name[128];
    if (ioctl(this->joydev, JSIOCGNAME(sizeof(name)), name) >= 0) {
      this->name = strcpy(new char [strlen(name)+1], name);
    } else {
      SoDebugError::post("SoQtLinuxJoystick::enable",
        "ioctl(JSIOCGNAME) failed");
      this->name = strcpy(new char [sizeof("Unknown")+1], "Unknown");
    }

#if SOQT_DEBUG && 0
    SoDebugError::post("SoQtLinuxJoystick::enable",
                       "successfully opened \"%s\" device with %d axes and %d buttons",
                       this->name, this->numaxes, this->numbuttons);
#endif // SOQT_DEBUG

    int i;
    this->axisvalues = new int32_t [this->numaxes];
    for (i = 0; i < this->numaxes; i++)
      this->axisvalues[i] = 0;

    this->buttonvalues = new int32_t [this->numbuttons];
    for (i = 0; i < this->numbuttons; i++)
      this->buttonvalues[i] = FALSE;

    this->notifier = new QSocketNotifier(this->joydev, QSocketNotifier::Read);
    QObject::connect(this->notifier, SIGNAL(activated(int)),
                     this, SLOT(device_event(int)));
  }
  this->addEventHandler(widget, handler, closure);
}

/*!
  FIXME: write doc
*/

void
SoQtLinuxJoystick::disable(QWidget * widget,
                           SoQtEventHandler * handler,
                           void * closure)
{
  this->removeEventHandler(widget, handler, closure);
}

// *************************************************************************

/*!
  This method translates X events into Open Inventor events suitable for
  propagating into the scene graph.  NULL is returned if the event can't
  be translated (wrong event type for this device).
*/

const SoEvent *
SoQtLinuxJoystick::translateEvent(QEvent * event)
{
  switch (event->type()) {
  case soqt6dofDeviceButtonPressedEvent:
    return this->makeButtonEvent((SoQt6dofDeviceButtonEvent *) event,
      SoButtonEvent::DOWN);
  case soqt6dofDeviceButtonReleasedEvent:
    return this->makeButtonEvent((SoQt6dofDeviceButtonEvent *) event,
      SoButtonEvent::UP);
  case soqt6dofDevicePressureEvent:
    return this->makeMotion3Event((SoQt6dofDevicePressureEvent *) event);
  default:
    break;
  }
  return (SoEvent *) NULL;
}

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtLinuxJoystick::setRotationScaleFactor(const float factor)
{
  this->rotationScaleFactor = factor;
}

/*!
  FIXME: write doc
*/

float
SoQtLinuxJoystick::getRotationScaleFactor(void) const
{
  return this->rotationScaleFactor;
}

/*!
  FIXME: write doc
*/

void
SoQtLinuxJoystick::setTranslationScaleFactor(const float factor)
{
  this->translationScaleFactor = factor;
}

/*!
  FIXME: write doc
*/

float
SoQtLinuxJoystick::getTranslationScaleFactor(void) const
{
  return this->translationScaleFactor;
}

// *************************************************************************

/*!
  This method returns wether there is a Joystick device on the given
  display or not.  A NULL \a display argument means the default display,
  of course.
*/

SbBool
SoQtLinuxJoystick::exists(void)
{
  if (SoQtLinuxJoystick::enabled)
    return TRUE;
  const char * jsdevicepath = SoQtLinuxJoystickP::getDevicePathName();
  int joydev = open(jsdevicepath, O_RDONLY);
  if (joydev <= 0)
    return FALSE;
  close(joydev);
  return TRUE;
}

// *************************************************************************

const char *
SoQtLinuxJoystickP::getDevicePathName(void)
{
  const char * devicepath = SoAny::getenv("SOQT_JOYSTICK_DEVICE");
#ifdef SOQT_JOYSTICK_LINUX_DEVICE
  static const char configured[] = SOQT_JOYSTICK_LINUX_DEVICE;
  if (devicepath == NULL)
    devicepath = configured;
#endif // SOQT_JOYSTICK_LINUX_DEVICE
  static const char hardcoded[] = "/dev/js0";
  if (devicepath == NULL)
    devicepath = hardcoded;
  return devicepath;
}

// *************************************************************************

/*!
  FIXME: write doc
*/

int
SoQtLinuxJoystick::getNumButtons(void) const
{
  return this->numbuttons;
}

/*!
  FIXME: write doc
*/

SbBool
SoQtLinuxJoystick::getButtonValue(const int button) const
{
  if (button < 0 || button >= this->numbuttons) {
#if SOQT_DEBUG
    SoDebugError::post("SoQtLinuxJoystick::getButtonValue",
      "invalid button %d", button);
#endif // SOQT_DEBUG
    return FALSE;
  }
  return this->buttonvalues[button];
}

/*!
  FIXME: write doc
*/

int
SoQtLinuxJoystick::getNumAxes(void) const
{
  return this->numaxes;
}

/*!
  FIXME: write doc
*/

float
SoQtLinuxJoystick::getAxisValue(const int axis) const
{
  if (axis < 0 || axis >= this->numaxes) {
#if SOQT_DEBUG
    SoDebugError::post("SoQtLinuxJoystick::getButtonValue",
      "invalid axis %d", axis);
#endif // SOQT_DEBUG
    return 0.0f;
  }
  return float(this->axisvalues[axis]) * this->translationScaleFactor;
}

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtLinuxJoystick::setFocusToWindow(SbBool enable)
{
  this->focusToWindow = enable;
  SOQT_STUB();
}

/*!
  FIXME: write doc
*/

SbBool
SoQtLinuxJoystick::isFocusToWindow(void) const
{
  return this->focusToWindow;
}

// *************************************************************************

SoMotion3Event *
SoQtLinuxJoystickP::makeMotion3Event(SoQt6dofDevicePressureEvent * event)
{
  if (this->motion3Event == NULL)
    this->motion3Event = new SoMotion3Event;

  float x, y, z;

  event->getTranslation(x, y, z);
  this->motion3Event->setTranslation(SbVec3f(x, y, 0 - z));

  event->getRotation(x, y, z);
  SbRotation xrot(SbVec3f(1, 0, 0), x);
  SbRotation yrot(SbVec3f(0, 1, 0), y);
  SbRotation zrot(SbVec3f(0, 0, 1), 0 - z);

  this->motion3Event->setRotation(xrot * yrot * zrot);

  return this->motion3Event;
}

SoSpaceballButtonEvent *
SoQtLinuxJoystickP::makeButtonEvent(SoQt6dofDeviceButtonEvent * event,
                                    SoButtonEvent::State state)
{
  if (this->buttonEvent == NULL)
    this->buttonEvent = new SoSpaceballButtonEvent;

  this->buttonEvent->setButton(SoSpaceballButtonEvent::ANY);

  switch (event->getButton()) {
  case 0:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON1);
    break;
  case 1:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON2);
    break;
  case 2:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON3);
    break;
  case 3:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON4);
    break;
  case 4:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON5);
    break;
  case 5:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON6);
    break;
  case 6:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON7);
    break;
  case 7:
    this->buttonEvent->setButton(SoSpaceballButtonEvent::BUTTON8);
    break;

  case 8: // FIXME: which one should PICK really be?
    this->buttonEvent->setButton(SoSpaceballButtonEvent::PICK);
    break;

  default:
    break;
  }

  this->buttonEvent->setState(state);

  return this->buttonEvent;
}

// *************************************************************************

// This method is invoked when the joystick is enabled and there are
// joystick events coming in.
//
// See linux/Documentation/joystick-api.txt.
void
SoQtLinuxJoystickP::device_event(int device)
{
  struct js_event event;

  int button = -1;
  SbBool motion = FALSE;

  int bytes = read(this->joydev, &event, sizeof(struct js_event));
  while (bytes == sizeof(struct js_event)) {
    if ((event.type & JS_EVENT_INIT) != 0) {
      if ((event.type & JS_EVENT_BUTTON) != 0) {
        assert(event.number < this->numbuttons);
        this->buttonvalues[event.number] = event.value ? TRUE : FALSE;
      } else if ((event.type & JS_EVENT_AXIS) != 0) {
        assert(event.number < this->numaxes);
        long value = event.value;
        SbBool negative = FALSE;
        if (value < 0) negative = TRUE;
        value = (value * value) / 0x8000;
        if (negative) value = 0 - value;
        assert(value >= -32768 && value <= 32767);
        this->axisvalues[event.number] = value;
      } else {
        SoDebugError::post("SoQtLinuxJoystick::input",
          "event [initial] not supported");
      }
      bytes = read(this->joydev, &event, sizeof(struct js_event));
      continue;
    }

    if ((event.type & JS_EVENT_BUTTON) != 0) {
      assert(event.number < this->numbuttons);
      this->buttonvalues[event.number] = event.value ? TRUE : FALSE;
      button = event.number;
    } else if ((event.type & JS_EVENT_AXIS) != 0) {
      assert(event.number < this->numaxes);
      long value = event.value;
      SbBool negative = FALSE;
      if (value < 0) negative = TRUE;
      value = (value * value) / 0x8000;
      if (negative) value = 0 - value;
      assert(value >= -32768 && value <= 32767);
      this->axisvalues[event.number] = value;
      motion = TRUE;
    }

    bytes = read(this->joydev, &event, sizeof(struct js_event));
  }

  if (button != -1) {
    SoQt6dofDeviceButtonEvent qevent;
//    if (event.value == 0)
//      xevent.type = soqt6dofDeviceButtonReleasedEvent;
//    else
//      xevent.type = soqt6dofDeviceButtonPressedEvent;
//    xevent.serial = 0;
//    xevent.send_event = False;
//    xevent.display = SoQt::getDisplay();
//    xevent.window = (Window) NULL;
//    xevent.time = event.time;
    unsigned int state = 0;
    for (int i = 0; i < this->numbuttons; i++) {
      if (this->buttonvalues[i] != FALSE)
        state |= (1 << i);
    }
    qevent.setNumButtons(this->numbuttons);
    qevent.setState(state);
    qevent.setButton(button);

    this->invokeHandlers((QEvent *) &qevent);
  }

  if (motion != FALSE) {
    SoQt6dofDevicePressureEvent qevent;
//    xevent.type = soqt6dofDevicePressureEvent;
//    xevent.serial = 0;
//    xevent.send_event = False;
//    xevent.display = SoQt::getDisplay();
//    xevent.window = (Window) NULL;
//    xevent.time = event.time;

    float trans_x = 0.0f;
    float trans_y = 0.0f;
    float trans_z = 0.0f;
    float rot_x = 0.0f;
    float rot_y = 0.0f;
    float rot_z = 0.0f;

    do {
      if (this->numaxes < 1) break;
      trans_x = this->translationScaleFactor * float(this->axisvalues[0]);
      if (this->numaxes < 2) break;
      trans_y = this->translationScaleFactor * float(this->axisvalues[1]);
      if (this->numaxes < 3) break;
      trans_z = this->translationScaleFactor * float(this->axisvalues[2]);
      if (this->numaxes < 4) break;
      rot_x = this->rotationScaleFactor * float(this->axisvalues[3]);
      if (this->numaxes < 5) break;
      rot_y = this->rotationScaleFactor * float(this->axisvalues[4]);
      if (this->numaxes < 6) break;
      rot_z = this->rotationScaleFactor * float(this->axisvalues[5]);
    } while (FALSE);

    qevent.setTranslation(trans_x, trans_y, trans_z);
    qevent.setRotation(rot_x, rot_y, rot_z);

    this->invokeHandlers((QEvent *) &qevent);
  }
}

// *************************************************************************
