#ifndef COIN_SOGUIVIEWPOINTWRAPPER_H
#define COIN_SOGUIVIEWPOINTWRAPPER_H

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

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/SoLists.h>

class SoPath;
class SoFullPath;
class SoPathSensor;
class SoSensor;
class SoFieldSensor;
class SoGetMatrixAction;

class SoGuiViewpointWrapper : public SoPerspectiveCamera {
  typedef SoPerspectiveCamera inherited;
  SO_NODE_HEADER(SoGuiViewpointWrapper);
public:
  static void initClass(void);
  SoGuiViewpointWrapper(void);
  
  void setSceneGraph(SoNode * root);
  
  static SbBool hasViewpoints(SoNode * root);

protected:
  ~SoGuiViewpointWrapper();
  
private:
  void setViewpoint(SoPath * path);
  
  static void fieldsensor_cb(void * data, SoSensor * sensor);
  static void pathsensor_cb(void * data, SoSensor * sensor);
  static void set_bind_cb(void * data, SoSensor * sensor);

  void updateCamera(void);
  void updateViewpoint(void);
  
  void attachFieldSensors(void);
  void detachFieldSensors(void);
  
  SoFullPath * pathtoviewpoint;
  SoPathSensor * pathsensor;
  SoFieldSensor * positionsensor;
  SoFieldSensor * orientationsensor;
  SoFieldSensor * heightanglesensor;
  SoGetMatrixAction * gmaction;

  void truncateLists(void);
  
  SoNodeList nodelist;
  SbPList set_bind_sensorlist;
  SoSearchAction sa;
  SoNode * scenegraph;

  void attachSetBindSensors(void);
  void detachSetBindSensors(void);

  void sendBindEvents(SoNode * node, const SbBool onoff);
  void bindTopOfStack(void);

};

#endif //  COIN_SOGUIVIEWPOINTWRAPPER_H
