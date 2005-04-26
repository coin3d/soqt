/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

// Pulls in __COIN_SOQT__ define used below.
#include <Inventor/Qt/SoQtBasic.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtObject.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/Qt/SoQtComponent.h>

/*!
  \class SoQtObject Inventor/Qt/SoQtObject.h
  \brief The SoQtObject class is the common superclass for all SoQt component classes.
  \ingroup misc

  The purpose of making this class the superclass of all SoQt
  device, component and viewer classes is to be able to do run-time
  type checking of the SoQt objects.


  You can place the macro SOQT_OBJECT_HEADER(classname,parentname)
  within a class definition header for SoQt extension components to
  automatically make the necessary definitions for setting up a
  run-time type system for your extension classes:

  \code
  #ifndef MYSPECIALVIEWER_H
  #define MYSPECIALVIEWER_H

  class MySpecialViewer : public SoQtExaminerViewer {
    SOQT_OBJECT_HEADER(MySpecialViewer, SoQtExaminerViewer);
    // [rest of class definition follows]
  };

  #endif // !MYSPECIALVIEWER_H
  \endcode

  Then put the SOQT_OBJECT_SOURCE(classname) macro within the
  actual implementation sourcecode file to include the necessary
  code for the run-time type system:

  \code
  #include <MySpecialViewer.h>

  SOQT_OBJECT_SOURCE(MySpecialViewer);

  // [rest of class implementation]
  \endcode


  See also the documentation of the SoType class in Coin or Inventor.
 */

// *************************************************************************

/*!
  \fn SoType SoQtObject::getTypeId

  Returns the type identification of an object derived from a class
  inheriting SoQtObject.  This is used for run-time type checking
  and "downward" casting.

  Usage example:

  \code
  void foo(SoQtViewer * comp)
  {
    if (comp->getTypeId() == SoQtExaminerViewer::getClassTypeId()) {
      // safe downward cast, knows the type
      SoQtExaminerViewer * exviewer = (SoQtExaminerViewer *)comp;
      /// [then something] ///
    }
    else if (comp->getTypeId().isOfType(SoQtFlyViewer::getClassTypeId())) {
      // safe downward cast, knows the type
      SoQtFlyViewer * flyviewer = (SoQtFlyViewer *)comp;
      // then something else
    }
  }
  \endcode
*/
// FIXME: add doc above to explain how external developers can use the
// type system for their own extension classes. 20020502 mortene.

// This is a private variable.
SoType SoQtObject::classTypeId SOQT_STATIC_SOTYPE_INIT;

/*!
  Sets up initialization for data common to all instances of this
  class, submitting necessary information to the internal SoQt type
  system.
*/
void
SoQtObject::initClass(void)
{
  assert(SoQtObject::classTypeId == SoType::badType());
  SoQtObject::classTypeId =
    SoType::createType(SoType::badType(), "SoQtObject");
}

/*!
  Returns \c TRUE if the type of this object is either of the same
  type or inherited from \a type.
*/
SbBool
SoQtObject::isOfType(SoType type) const
{
  return this->getTypeId().isDerivedFrom(type);
}

/*!
  This static method returns the SoType object associated with
  objects of this class.
*/
SoType
SoQtObject::getClassTypeId(void)
{
  return SoQtObject::classTypeId;
}

/*!
  Initialize the type system of SoQtObject, all SoQt device
  classes and all SoQt components (including viewers).
*/
void
SoQtObject::init(void)
{
  SoQtObject::initClass();
  SoQtDevice::initClasses();
  SoQtComponent::initClasses();
}
