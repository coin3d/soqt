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

#ifndef SOQT_SLIDERSETBASE_H
#define SOQT_SLIDERSETBASE_H

#include <Inventor/Qt/SoQtComponent.h>

class SoNode;

// *************************************************************************

class SOQT_DLL_API SoQtSliderSetBase : public SoQtComponent {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtSliderSetBase, SoQtComponent);
  Q_OBJECT

public:
  virtual void setNode(SoNode * newNode);
  SoNode * getNode(void) const;

protected:
  SoQtSliderSetBase(QWidget * parent = NULL,
                    const char * name = NULL,
                    SbBool embed = TRUE,
                    SoNode * editnode = NULL);
  ~SoQtSliderSetBase();

private:
  SoNode * node;

}; // class SoQtSliderSetBase

// *************************************************************************

#endif // ! SOQT_SLIDERSETBASE_H
