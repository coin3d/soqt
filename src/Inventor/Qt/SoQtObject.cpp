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
#endif

#include <Inventor/Qt/SoQtObject.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/Qt/SoQtComponent.h>

/*!
  \class SoQtObject Inventor/Qt/SoQtObject.h
  \brief The SoQtObject class is for run-time type checking of the SoQt
  objects.
*/

// *************************************************************************

SoType SoQtObject::classTypeId; // static

void
SoQtObject::init( // static
  void )
{
  SoQtObject::initClass();
  SoQtDevice::initClasses();
  SoQtComponent::initClasses();
} // init()

void
SoQtObject::initClass( // static
  void )
{
  assert( SoQtObject::classTypeId == SoType::badType() );
  SoQtObject::classTypeId =
    SoType::createType( SoType::badType(), "SoQtObject");
} // initClass()

SbBool
SoQtObject::isOfType(
  SoType type ) const
{
  return this->getTypeId().isDerivedFrom(type);
} // isOfType()

SoType
SoQtObject::getClassTypeId( // static
  void ) 
{
  return SoQtObject::classTypeId;
} // getClassTypeId()

// *************************************************************************
