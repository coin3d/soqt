/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

//  $Id$

#ifndef SOQT_OBJECT_H
#define SOQT_OBJECT_H

#include <assert.h>

#include <qobject.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

#include <Inventor/Qt/SoQtBasic.h>

// *************************************************************************

class SOQT_DLL_EXPORT SoQtObject : public QObject {
  static SoType classTypeId;
  Q_OBJECT

public:
  static void initClass(void);
  static SoType getClassTypeId(void);
  virtual SoType getTypeId(void) const = 0;
  SbBool isOfType( SoType type ) const;

  static void init(void);

}; // SoQtObject

// *************************************************************************

// The getTypeId() method should be abstract for abstract objects, but doing
// that would cause custom components derived from abstract components to
// have to include the typed object header / source, which could be a
// problem if the custom component wasn't written for Coin in the first
// place.

#define SOQT_OBJECT_ABSTRACT_HEADER(classname, parentname)                 \
public:                                                                    \
  static void initClass(void);                                             \
  static SoType getClassTypeId(void);                                      \
  virtual SoType getTypeId(void) const /* = 0 */;                          \
private:                                                                   \
  typedef parentname inherited;                                            \
  static SoType classTypeId

#define SOQT_OBJECT_HEADER(classname, parentname)                          \
public:                                                                    \
  static void initClass(void);                                             \
  static SoType getClassTypeId(void);                                      \
  virtual SoType getTypeId(void) const;                                    \
  static void * createInstance(void);                                      \
private:                                                                   \
  typedef parentname inherited;                                            \
  static SoType classTypeId

#define SOQT_OBJECT_ABSTRACT_SOURCE(classname)                             \
void classname::initClass(void) {                                          \
  assert( classname::classTypeId == SoType::badType() );                   \
  classname::classTypeId =                                                 \
    SoType::createType( inherited::getClassTypeId(),                       \
                        SO__QUOTE(classname) );                            \
}                                                                          \
SoType classname::getClassTypeId(void) {                                   \
  return classname::classTypeId;                                           \
}                                                                          \
SoType classname::getTypeId(void) const {                                  \
  return classname::classTypeId;                                           \
}                                                                          \
SoType classname::classTypeId

#define SOQT_OBJECT_SOURCE(classname)                                      \
void classname::initClass(void) {                                          \
  assert( classname::classTypeId == SoType::badType() );                   \
  classname::classTypeId =                                                 \
    SoType::createType( inherited::getClassTypeId(),                       \
                        SO__QUOTE(classname),                              \
                        classname::createInstance );                       \
}                                                                          \
SoType classname::getClassTypeId(void) {                                   \
  return classname::classTypeId;                                           \
}                                                                          \
SoType classname::getTypeId(void) const {                                  \
  return classname::classTypeId;                                           \
}                                                                          \
void * classname::createInstance(void) {                                   \
  return (void *) new classname;                                           \
}                                                                          \
SoType classname::classTypeId

// *************************************************************************

#endif // ! SOQT_OBJECT_H
